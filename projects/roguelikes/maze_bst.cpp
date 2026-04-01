// maze_bst.cpp
// Binary Tree ("coin flip") maze generator & explorer — ncurses demo
//
// Build (GitHub Codespaces / Ubuntu):
//   sudo apt-get install -y libncurses-dev
//   g++ -std=c++17 -Wall -o maze maze_bst.cpp -lncurses
//   ./maze
//
// Controls:
//   G / SPACE      – generate a new maze
//   Arrow keys     – walk through the maze
//   S              – toggle solution path
//   +/- (or =/-)   – increase / decrease maze size
//   R              – enter a custom seed
//   Q              – quit
//
// Algorithm:
//   Binary Tree maze generation. For each cell, flip a coin:
//     Heads → carve a passage NORTH
//     Tails → carve a passage EAST
//   Cells on the north edge can only go east; cells on the east edge
//   can only go north. The northeast corner cell stays closed.
//   This produces a maze with a distinctive diagonal texture and
//   guaranteed perfect (no loops, no isolated cells) connectivity.
//
// Minimum terminal: 80 × 24

#include <ncurses.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <queue>
#include <utility>

// ── Color pair IDs (matching Wizardry wireframe) ─────────────────────────
enum CP {
    CP_BORDER  = 1,   // cyan on black   – box frames
    CP_TITLE   = 2,   // yellow on black  – headings
    CP_NORMAL  = 3,   // white on black   – body text
    CP_HP_OK   = 4,   // green on black   – success / path
    CP_HP_HURT = 5,   // yellow on black  – warning
    CP_HP_DEAD = 6,   // red on black     – walls highlighted
    CP_MSG     = 7,   // yellow on black  – messages
    CP_SEL     = 8,   // black on cyan    – highlighted / nav bar
    CP_GOLD    = 9,   // yellow on black  – gold / rewards
    CP_DIM     = 10,  // white on black   – faint text
    CP_HEADER  = 11,  // cyan on black    – column headers
    CP_PLAYER  = 12,  // black on green   – player position
    CP_GOAL    = 13,  // black on yellow  – goal position
    CP_PATH    = 14,  // green on black   – solution path
};

static int scrH = 24, scrW = 80;   // screen dimensions (avoid ncurses scrW)

// ── Init ─────────────────────────────────────────────────────────────────
static void initColors() {
    start_color();
    init_pair(CP_BORDER,  COLOR_CYAN,    COLOR_BLACK);
    init_pair(CP_TITLE,   COLOR_YELLOW,  COLOR_BLACK);
    init_pair(CP_NORMAL,  COLOR_WHITE,   COLOR_BLACK);
    init_pair(CP_HP_OK,   COLOR_GREEN,   COLOR_BLACK);
    init_pair(CP_HP_HURT, COLOR_YELLOW,  COLOR_BLACK);
    init_pair(CP_HP_DEAD, COLOR_RED,     COLOR_BLACK);
    init_pair(CP_MSG,     COLOR_YELLOW,  COLOR_BLACK);
    init_pair(CP_SEL,     COLOR_BLACK,   COLOR_CYAN);
    init_pair(CP_GOLD,    COLOR_YELLOW,  COLOR_BLACK);
    init_pair(CP_DIM,     COLOR_WHITE,   COLOR_BLACK);
    init_pair(CP_HEADER,  COLOR_CYAN,    COLOR_BLACK);
    init_pair(CP_PLAYER,  COLOR_BLACK,   COLOR_GREEN);
    init_pair(CP_GOAL,    COLOR_BLACK,   COLOR_YELLOW);
    init_pair(CP_PATH,    COLOR_GREEN,   COLOR_BLACK);
}

// ── Drawing helpers (from Wizardry wireframe) ────────────────────────────

// Colorized mvaddstr shorthand
static void cs(int y, int x, int cp, int attr, const char* s) {
    if (!s) return;
    attron(COLOR_PAIR(cp) | attr);
    mvaddstr(y, x, s);
    attroff(COLOR_PAIR(cp) | attr);
}

// Horizontally centered string
static void ctr(int y, const char* s, int cp = CP_NORMAL, int attr = 0) {
    if (!s) return;
    int x = (scrW - (int)strlen(s)) / 2;
    cs(y, (x > 0 ? x : 0), cp, attr, s);
}

// Draw a box with optional centered title on top border
static void drawBox(int y, int x, int h, int w,
                    int cp = CP_BORDER, const char* title = nullptr) {
    attron(COLOR_PAIR(cp));
    mvaddch(y,     x,     ACS_ULCORNER);
    mvaddch(y,     x+w-1, ACS_URCORNER);
    mvaddch(y+h-1, x,     ACS_LLCORNER);
    mvaddch(y+h-1, x+w-1, ACS_LRCORNER);
    for (int i = 1; i < w-1; i++) {
        mvaddch(y,     x+i, ACS_HLINE);
        mvaddch(y+h-1, x+i, ACS_HLINE);
    }
    for (int i = 1; i < h-1; i++) {
        mvaddch(y+i, x,     ACS_VLINE);
        mvaddch(y+i, x+w-1, ACS_VLINE);
    }
    attroff(COLOR_PAIR(cp));
    if (title) {
        char buf[128];
        snprintf(buf, sizeof(buf), " %s ", title);
        int tx = x + (w - (int)strlen(buf)) / 2;
        cs(y, tx, CP_TITLE, A_BOLD, buf);
    }
}

// Navigation bar at bottom row
static void navBar(const char* text) {
    attron(COLOR_PAIR(CP_SEL));
    char bar[256];
    snprintf(bar, sizeof(bar), "%-*s", scrW, "");
    mvaddstr(scrH-1, 0, bar);
    int x = (scrW - (int)strlen(text)) / 2;
    mvaddstr(scrH-1, (x > 0 ? x : 0), text);
    attroff(COLOR_PAIR(CP_SEL));
}

// ── Maze data ────────────────────────────────────────────────────────────
static const int MAXSZ = 50;

static int  mW = 18, mH = 8;          // maze dimensions (cells)
static bool passN[MAXSZ][MAXSZ];      // passage north from (r,c) to (r-1,c)
static bool passE[MAXSZ][MAXSZ];      // passage east  from (r,c) to (r,c+1)
static bool onPath[MAXSZ][MAXSZ];     // solution path overlay
static int  pR = 0, pC = 0;           // player position
static int  steps = 0;                // step counter
static bool showSol = false;          // show solution?
static bool won = false;              // reached the exit?
static unsigned int seed = 0;         // RNG seed for reproducibility

// ── Movement check ───────────────────────────────────────────────────────
// dir: 0=north, 1=south, 2=east, 3=west
static bool canMove(int r, int c, int dir) {
    switch (dir) {
        case 0: return r > 0      && passN[r][c];
        case 1: return r < mH - 1 && passN[r + 1][c];
        case 2: return c < mW - 1 && passE[r][c];
        case 3: return c > 0      && passE[r][c - 1];
    }
    return false;
}

// ── Generate maze (Binary Tree algorithm) ────────────────────────────────
static void generateMaze() {
    memset(passN,  false, sizeof(passN));
    memset(passE,  false, sizeof(passE));
    memset(onPath, false, sizeof(onPath));
    pR = 0;  pC = 0;
    steps = 0;
    won = false;

    srand(seed);

    for (int r = 0; r < mH; r++) {
        for (int c = 0; c < mW; c++) {
            bool canN = (r > 0);
            bool canE = (c < mW - 1);

            if (canN && canE) {
                // ── The coin flip ──
                if (rand() % 2 == 0)
                    passN[r][c] = true;     // carve north
                else
                    passE[r][c] = true;     // carve east
            }
            else if (canN) {
                passN[r][c] = true;         // east edge → must go north
            }
            else if (canE) {
                passE[r][c] = true;         // north edge → must go east
            }
            // NE corner: no carve needed
        }
    }
}

// ── Solve maze (BFS from start to goal) ──────────────────────────────────
static void solveMaze() {
    memset(onPath, false, sizeof(onPath));

    bool visited[MAXSZ][MAXSZ] = {};
    int  prevR[MAXSZ][MAXSZ];
    int  prevC[MAXSZ][MAXSZ];
    memset(prevR, -1, sizeof(prevR));
    memset(prevC, -1, sizeof(prevC));

    std::queue<std::pair<int,int>> q;
    q.push({0, 0});
    visited[0][0] = true;

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        if (r == mH - 1 && c == mW - 1) break;

        for (int d = 0; d < 4; d++) {
            static const int dr[] = {-1, 1, 0, 0};
            static const int dc[] = {0, 0, 1, -1};
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= mH || nc < 0 || nc >= mW) continue;
            if (visited[nr][nc]) continue;
            if (!canMove(r, c, d)) continue;
            visited[nr][nc] = true;
            prevR[nr][nc] = r;
            prevC[nr][nc] = c;
            q.push({nr, nc});
        }
    }

    // Trace path from goal back to start
    int r = mH - 1, c = mW - 1;
    while (r >= 0 && c >= 0) {
        onPath[r][c] = true;
        int pr = prevR[r][c], pc = prevC[r][c];
        r = pr;
        c = pc;
    }
}

// ── Maze rendering ───────────────────────────────────────────────────────

// Determine wall presence for rendering:
//   wallH(r, c) — horizontal wall at wall-row r, cell-col c
//   wallV(r, c) — vertical wall at cell-row r, wall-col c
static bool wallH(int wr, int cc) {
    // Top and bottom boundary walls always exist
    if (wr == 0 || wr == mH) return true;
    // Interior: wall exists if no northward passage from cell (wr, cc)
    return !passN[wr][cc];
}

static bool wallV(int cr, int wc) {
    // Left and right boundary walls always exist
    if (wc == 0 || wc == mW) return true;
    // Interior: wall exists if no eastward passage from cell (cr, wc-1)
    return !passE[cr][wc - 1];
}

// Pick the right ACS character for a wall intersection
static chtype intersectionCh(bool up, bool dn, bool lt, bool rt) {
    int m = (up ? 8 : 0) | (dn ? 4 : 0) | (lt ? 2 : 0) | (rt ? 1 : 0);
    switch (m) {
        case 0b1111: return ACS_PLUS;
        case 0b1110: return ACS_RTEE;     // up+down+left  ┤
        case 0b1101: return ACS_LTEE;     // up+down+right ├
        case 0b1100: return ACS_VLINE;    // up+down       │
        case 0b1011: return ACS_BTEE;     // up+left+right ┴
        case 0b1010: return ACS_LRCORNER; // up+left       ┘
        case 0b1001: return ACS_LLCORNER; // up+right      └
        case 0b0111: return ACS_TTEE;     // down+left+right ┬
        case 0b0110: return ACS_URCORNER; // down+left     ┐
        case 0b0101: return ACS_ULCORNER; // down+right    ┌
        case 0b0100: // down only
        case 0b1000: // up only
            return ACS_VLINE;
        case 0b0010: // left only
        case 0b0001: // right only
        case 0b0011: // left+right
            return ACS_HLINE;
        default:     return ' ';
    }
}

// Draw the maze at the given screen offset, centered in the maze box.
// Each cell: 3 chars wide × 1 char tall.
// Display grid: (2*mH + 1) rows × (4*mW + 1) cols.
static void drawMaze(int offy, int offx) {
    int cp_wall = CP_BORDER;

    for (int wr = 0; wr <= mH; wr++) {
        int sy = offy + wr * 2;  // screen y for this wall row

        // ── Draw wall row ────────────────────────────────────────────
        for (int wc = 0; wc <= mW; wc++) {
            int sx = offx + wc * 4;

            // Intersection character
            bool up = (wr > 0)  && wallV(wr - 1, wc);
            bool dn = (wr < mH) && wallV(wr, wc);
            bool lt = (wc > 0)  && wallH(wr, wc - 1);
            bool rt = (wc < mW) && wallH(wr, wc);

            attron(COLOR_PAIR(cp_wall) | A_BOLD);
            mvaddch(sy, sx, intersectionCh(up, dn, lt, rt));
            attroff(COLOR_PAIR(cp_wall) | A_BOLD);

            // Horizontal wall segment to the right (3 chars)
            if (wc < mW) {
                if (wallH(wr, wc)) {
                    attron(COLOR_PAIR(cp_wall) | A_BOLD);
                    mvaddch(sy, sx + 1, ACS_HLINE);
                    mvaddch(sy, sx + 2, ACS_HLINE);
                    mvaddch(sy, sx + 3, ACS_HLINE);
                    attroff(COLOR_PAIR(cp_wall) | A_BOLD);
                } else {
                    mvaddch(sy, sx + 1, ' ');
                    mvaddch(sy, sx + 2, ' ');
                    mvaddch(sy, sx + 3, ' ');
                }
            }
        }

        // ── Draw cell row below this wall row ────────────────────────
        if (wr < mH) {
            int cy = offy + wr * 2 + 1;  // screen y for this cell row

            for (int wc = 0; wc <= mW; wc++) {
                int sx = offx + wc * 4;

                // Vertical wall segment
                if (wallV(wr, wc)) {
                    attron(COLOR_PAIR(cp_wall) | A_BOLD);
                    mvaddch(cy, sx, ACS_VLINE);
                    attroff(COLOR_PAIR(cp_wall) | A_BOLD);
                } else {
                    mvaddch(cy, sx, ' ');
                }

                // Cell interior (3 chars)
                if (wc < mW) {
                    char ch = ' ';
                    int  cell_cp   = CP_NORMAL;
                    int  cell_attr = 0;

                    // Layer 1: solution path
                    if (showSol && onPath[wr][wc]) {
                        ch = '.';
                        cell_cp = CP_PATH;
                        cell_attr = A_BOLD;
                    }

                    // Layer 2: goal marker (bottom-right)
                    if (wr == mH - 1 && wc == mW - 1) {
                        ch = '$';
                        cell_cp = CP_GOAL;
                        cell_attr = A_BOLD;
                    }

                    // Layer 3: player (drawn on top of everything)
                    if (wr == pR && wc == pC) {
                        ch = '@';
                        cell_cp = CP_PLAYER;
                        cell_attr = A_BOLD;
                    }

                    // Draw the cell: 3 chars, marker centered
                    attron(COLOR_PAIR(cell_cp) | cell_attr);
                    mvaddch(cy, sx + 1, ' ');
                    mvaddch(cy, sx + 2, ch);
                    mvaddch(cy, sx + 3, ' ');
                    attroff(COLOR_PAIR(cell_cp) | cell_attr);
                }
            }
        }
    }
}

// ── Full screen draw ─────────────────────────────────────────────────────
static void drawScreen() {
    clear();

    // Outer border
    drawBox(0, 0, scrH - 1, scrW);
    ctr(0, " BINARY TREE MAZE ", CP_TITLE, A_BOLD);

    // ── Maze box ─────────────────────────────────────────────────────
    int maze_box_y = 1;
    int maze_box_x = 1;
    int maze_box_w = scrW - 2;
    int maze_box_h = scrH - 6;  // leave room for info strip + nav bar

    char mtitle[64];
    snprintf(mtitle, sizeof(mtitle), "DUNGEON MAP  %d x %d", mW, mH);
    drawBox(maze_box_y, maze_box_x, maze_box_h, maze_box_w, CP_BORDER, mtitle);

    // Compute maze display size and center it inside the box
    int disp_w = 4 * mW + 1;
    int disp_h = 2 * mH + 1;

    int inner_w = maze_box_w - 2;  // usable cols inside box
    int inner_h = maze_box_h - 2;  // usable rows inside box

    int offy = maze_box_y + 1 + (inner_h - disp_h) / 2;
    int offx = maze_box_x + 1 + (inner_w - disp_w) / 2;

    drawMaze(offy, offx);

    // ── Info strip ───────────────────────────────────────────────────
    int info_y = maze_box_y + maze_box_h;
    drawBox(info_y, 1, 3, scrW - 2, CP_BORDER, "STATUS");

    // Left: seed and stats
    char info[128];
    snprintf(info, sizeof(info), "Seed: %-10u  Size: %dx%d  Steps: %d",
             seed, mW, mH, steps);
    cs(info_y + 1, 3, CP_HEADER, 0, info);

    // Right: status message
    if (won) {
        const char* vmsg = "** MAZE COMPLETE! **";
        cs(info_y + 1, scrW - 3 - (int)strlen(vmsg), CP_GOLD, A_BOLD, vmsg);
    } else {
        const char* hmsg = "Reach the $ to win!";
        cs(info_y + 1, scrW - 3 - (int)strlen(hmsg), CP_MSG, 0, hmsg);
    }

    // ── Nav bar ──────────────────────────────────────────────────────
    navBar(" [G/SPACE] Generate  [ARROWS] Move  [S] Solution  [+/-] Size  [R] Seed  [Q] Quit ");

    refresh();
}

// ── Clamp maze dimensions to fit the display ─────────────────────────────
static void clampDimensions() {
    int maze_box_w = scrW - 2;
    int maze_box_h = scrH - 6;
    int inner_w = maze_box_w - 2;
    int inner_h = maze_box_h - 2;

    // Display grid: (2*mH+1) rows × (4*mW+1) cols
    int max_w = (inner_w - 1) / 4;
    int max_h = (inner_h - 1) / 2;

    if (max_w < 3) max_w = 3;
    if (max_h < 3) max_h = 3;

    if (mW > max_w) mW = max_w;
    if (mH > max_h) mH = max_h;
    if (mW < 3) mW = 3;
    if (mH < 3) mH = 3;
}

// ── Seed input mode ──────────────────────────────────────────────────────
static void inputSeed() {
    // Show input prompt in the info strip area
    int info_y = scrH - 5;
    cs(info_y + 1, 3, CP_MSG, A_BOLD, "Enter seed (number): ");
    clrtoeol();
    refresh();

    echo();
    curs_set(1);

    char buf[32] = {};
    mvgetnstr(info_y + 1, 24, buf, 20);

    noecho();
    curs_set(0);

    // Parse the seed; if invalid, use current time
    unsigned int val = 0;
    if (sscanf(buf, "%u", &val) == 1) {
        seed = val;
    }
    // else keep old seed
}

// ── Main ─────────────────────────────────────────────────────────────────
int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    getmaxyx(stdscr, scrH, scrW);

    if (!has_colors()) {
        endwin();
        fputs("Error: terminal does not support color.\n", stderr);
        return 1;
    }
    initColors();

    if (scrH < 24 || scrW < 80) {
        clear();
        char msg[80];
        snprintf(msg, sizeof(msg),
            "Terminal too small! Need 80x24 minimum; got %dx%d.", scrW, scrH);
        mvaddstr(scrH / 2, 0, msg);
        refresh();
        getch();
        endwin();
        return 1;
    }

    // Initial maze
    seed = (unsigned int)time(nullptr);
    clampDimensions();
    generateMaze();
    solveMaze();
    drawScreen();

    bool running = true;
    while (running) {
        int ch = getch();

        switch (ch) {
            // ── Quit ─────────────────────────────────────────────────
            case 'q': case 'Q':
                running = false;
                break;

            // ── Generate new maze ────────────────────────────────────
            case 'g': case 'G': case ' ':
                seed = (unsigned int)time(nullptr) ^ (seed * 2654435761u);
                clampDimensions();
                generateMaze();
                solveMaze();
                break;

            // ── Toggle solution ──────────────────────────────────────
            case 's': case 'S':
                showSol = !showSol;
                break;

            // ── Resize maze ──────────────────────────────────────────
            case '+': case '=':
                mW += 2;
                mH += 1;
                clampDimensions();
                generateMaze();
                solveMaze();
                break;
            case '-': case '_':
                mW -= 2;
                mH -= 1;
                clampDimensions();
                generateMaze();
                solveMaze();
                break;

            // ── Custom seed ──────────────────────────────────────────
            case 'r': case 'R':
                inputSeed();
                clampDimensions();
                generateMaze();
                solveMaze();
                break;

            // ── Player movement ──────────────────────────────────────
            case KEY_UP:
                if (!won && canMove(pR, pC, 0)) { pR--; steps++; }
                break;
            case KEY_DOWN:
                if (!won && canMove(pR, pC, 1)) { pR++; steps++; }
                break;
            case KEY_RIGHT:
                if (!won && canMove(pR, pC, 2)) { pC++; steps++; }
                break;
            case KEY_LEFT:
                if (!won && canMove(pR, pC, 3)) { pC--; steps++; }
                break;
        }

        // Check win condition
        if (pR == mH - 1 && pC == mW - 1 && !won) {
            won = true;
        }

        if (running) drawScreen();
    }

    endwin();
    return 0;
}
