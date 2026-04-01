// dungeon_wireframe.cpp
// Wizardry I-style roguelike UI wireframe demo (5 screens, ncurses)
//
// Build (GitHub Codespaces / Ubuntu):
//   sudo apt-get install -y libncurses-dev
//   g++ -std=c++17 -Wall -o dungeon dungeon_wireframe.cpp -lncurses
//   ./dungeon
//
// Navigate:
//   SPACE / ENTER / → / ↓  – next screen
//   B / ← / ↑              – previous screen
//   1-5                     – jump to screen
//   Q                       – quit
//
// Minimum terminal: 80 × 24

#include <ncurses.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

// ── Color pair IDs ─────────────────────────────────────────────────────────
enum CP {
    CP_BORDER  = 1,  // cyan on black   – box frames
    CP_TITLE   = 2,  // yellow on black – headings / victory
    CP_NORMAL  = 3,  // white on black  – body text
    CP_HP_OK   = 4,  // green on black  – full health / success
    CP_HP_HURT = 5,  // yellow on black – damaged / warning
    CP_HP_DEAD = 6,  // red on black    – critical / dead / enemy
    CP_MSG     = 7,  // yellow on black – event messages / door labels
    CP_SEL     = 8,  // black on cyan   – highlighted / selected
    CP_GOLD    = 9,  // yellow on black – gold / rewards
    CP_DIM     = 10, // white on black  – use with A_DIM for faint text
    CP_HEADER  = 11, // cyan on black   – column headers
};

int ROWS = 24, COLS = 80;   // updated in main(); used throughout

// ── Init ───────────────────────────────────────────────────────────────────
void initColors() {
    start_color();
    init_pair(CP_BORDER,  COLOR_CYAN,   COLOR_BLACK);
    init_pair(CP_TITLE,   COLOR_YELLOW, COLOR_BLACK);
    init_pair(CP_NORMAL,  COLOR_WHITE,  COLOR_BLACK);
    init_pair(CP_HP_OK,   COLOR_GREEN,  COLOR_BLACK);
    init_pair(CP_HP_HURT, COLOR_YELLOW, COLOR_BLACK);
    init_pair(CP_HP_DEAD, COLOR_RED,    COLOR_BLACK);
    init_pair(CP_MSG,     COLOR_YELLOW, COLOR_BLACK);
    init_pair(CP_SEL,     COLOR_BLACK,  COLOR_CYAN);
    init_pair(CP_GOLD,    COLOR_YELLOW, COLOR_BLACK);
    init_pair(CP_DIM,     COLOR_WHITE,  COLOR_BLACK);
    init_pair(CP_HEADER,  COLOR_CYAN,   COLOR_BLACK);
}

// ── Drawing helpers ────────────────────────────────────────────────────────

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
    int x = (COLS - (int)strlen(s)) / 2;
    cs(y, std::max(0, x), cp, attr, s);
}

// Draw a box; optional title centered on top border
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

// Horizontal rule inside an existing box (tee chars on sides)
static void hRule(int y, int x1, int x2, int cp = CP_BORDER) {
    attron(COLOR_PAIR(cp));
    mvaddch(y, x1,   ACS_LTEE);
    for (int x = x1+1; x < x2; x++) mvaddch(y, x, ACS_HLINE);
    mvaddch(y, x2,   ACS_RTEE);
    attroff(COLOR_PAIR(cp));
}

// Navigation bar at bottom row
static void navBar() {
    const char* s = " SPACE/ENTER: next   B/LEFT: prev   1-5: jump   Q: quit ";
    attron(COLOR_PAIR(CP_SEL));
    char bar[256];
    snprintf(bar, sizeof(bar), "%-*s", COLS, "");
    mvaddstr(ROWS-1, 0, bar);
    int x = (COLS - (int)strlen(s)) / 2;
    mvaddstr(ROWS-1, std::max(0, x), s);
    attroff(COLOR_PAIR(CP_SEL));
}

// Small badge in top-left of border
static void screenBadge(const char* label) {
    char buf[64];
    snprintf(buf, sizeof(buf), " %s ", label);
    cs(0, 1, CP_TITLE, A_BOLD, buf);
}

// HP color helper
static int hpColor(int hp, int mhp) {
    if (mhp <= 0) return CP_HP_DEAD;
    int pct = hp * 100 / mhp;
    return (pct > 60) ? CP_HP_OK : (pct > 25) ? CP_HP_HURT : CP_HP_DEAD;
}

// ── SCREEN 1: Main Menu ────────────────────────────────────────────────────
void screenMainMenu() {
    clear();
    drawBox(0, 0, ROWS-1, COLS);

    // Title art
    const char* art[] = {
        " ____  ___  _  _  ___  ____  ___  _  _    ___  ____    ____  ___  ___  __  __ ",
        "|    \\|   || || ||    ||    \\|   || \\| |  / _ \\ |    \\  |    \\|   ||   ||  \\/  |",
        "|  D  | | || || | |--| |  D  | | ||    | | | | ||  D  | |  D  | | | | | ||  ||  |",
        "|    /| | || || | |  | |    /| | || |\\  | | | | ||    /  |    /| | | | | ||      |",
        "|  D  | |_|| \\/ | |  | |  D  | |_|| |  | | |_| ||  D  | |  D  | |_| |_| ||  ||  |",
        "|____/|___| \\__/ |____||____/|___||_|\\_|  \\___/ |____/  |____/|___||___||__|  |_|",
        nullptr,
    };
    int row = 2;
    for (int i = 0; art[i]; i++)
        ctr(row++, art[i], CP_TITLE, A_BOLD);
    row++;
    ctr(row++, "Proving Grounds of the Mad Overlord", CP_HEADER, A_BOLD);
    ctr(row++, "~ v1.0 ~", CP_DIM, A_DIM);
    row++;

    // Menu box
    struct MI { int key; const char* lbl; bool sel; };
    MI items[] = {
        {1, "New Expedition",    true},
        {2, "Resume Journey",    false},
        {3, "Hall of Champions", false},
        {4, "Options",           false},
        {5, "Quit",              false},
        {0, nullptr,             false},
    };
    int mw = 30, mh = 7;
    int mx = (COLS - mw) / 2;
    drawBox(row, mx, mh, mw, CP_BORDER, "MAIN MENU");
    for (int i = 0; items[i].lbl; i++) {
        char buf[32];
        snprintf(buf, sizeof(buf), "  %d.  %-18s", items[i].key, items[i].lbl);
        char padded[36];
        snprintf(padded, sizeof(padded), "%-*s", mw-2, buf);
        if (items[i].sel) cs(row+1+i, mx+1, CP_SEL,    A_BOLD, padded);
        else               cs(row+1+i, mx+1, CP_NORMAL, 0,      padded);
    }
    row += mh + 2;

    ctr(row, "\"Beware, brave soul — many have entered... few return.\"", CP_DIM, A_DIM);

    screenBadge("1/5  MAIN MENU");
    navBar();
    refresh();
}

// ── SCREEN 2: Character Creation ──────────────────────────────────────────
void screenCharCreation() {
    clear();
    drawBox(0, 0, ROWS-1, COLS);
    ctr(0, " CHARACTER CREATION ", CP_TITLE, A_BOLD);

    // ── Left panel: name / race / alignment / stats (cols 1-33) ──────────
    int lw = 33;
    drawBox(1, 1, ROWS-2, lw, CP_BORDER, "YOUR HERO");

    // Name
    cs(3, 3, CP_HEADER, A_BOLD, "NAME:");
    cs(3, 9, CP_MSG,    A_BOLD, "THORIN");
    cs(3, 15, CP_DIM,   A_DIM,  "_________");

    // Race
    cs(5, 3, CP_HEADER, A_BOLD, "RACE:");
    const char* races[] = {"Human","Elf","Dwarf","Gnome","Hobbit",nullptr};
    for (int i = 0; races[i]; i++) {
        char buf[20];
        snprintf(buf, sizeof(buf), "%s %-8s", (i==0)?">":" ", races[i]);
        cs(6+i, 5, (i==0)?CP_SEL:CP_NORMAL, (i==0)?A_BOLD:0, buf);
    }

    // Alignment
    cs(12, 3, CP_HEADER, A_BOLD, "ALIGNMENT:");
    const char* aligns[] = {"Good","Neutral","Evil",nullptr};
    for (int i = 0; aligns[i]; i++) {
        char buf[16];
        snprintf(buf, sizeof(buf), "%s %-8s", (i==0)?">":" ", aligns[i]);
        cs(13+i, 5, (i==0)?CP_SEL:CP_NORMAL, (i==0)?A_BOLD:0, buf);
    }

    // Attributes
    cs(17, 3, CP_HEADER, A_BOLD, "ATTRIBUTES:");
    hRule(18, 1, lw);
    struct Stat { const char* name; int val; };
    Stat stats[] = {{"STR",15},{"IQ ",9},{"PIE",11},{"VIT",14},{"AGI",12},{"LCK",8},{nullptr,0}};
    for (int i = 0; stats[i].name; i++) {
        int cp = (stats[i].val>=13)?CP_HP_OK:(stats[i].val>=8)?CP_HP_HURT:CP_HP_DEAD;
        char buf[12];
        snprintf(buf, sizeof(buf), "%s: %2d", stats[i].name, stats[i].val);
        cs(19+i, 5, cp, A_BOLD, buf);
        attron(COLOR_PAIR(cp));
        for (int b = 0; b < stats[i].val/2; b++) mvaddch(19+i, 14+b, ACS_BLOCK);
        attroff(COLOR_PAIR(cp));
    }
    cs(ROWS-3, 3, CP_MSG, A_BOLD, "[R]oll  [A]ccept  [B]ack");

    // ── Right panel: class list + info (cols 35 to COLS-2) ───────────────
    int rx = lw + 2;
    int rw = COLS - rx - 1;
    drawBox(1, rx, ROWS-2, rw, CP_BORDER, "CLASS");

    struct Cls { const char* abbr; const char* name; const char* req; bool avail; };
    Cls cls[] = {
        {"FT","Fighter",  "STR 11",true},
        {"MA","Mage",     "IQ  12",true},
        {"PR","Priest",   "PIE 12",true},
        {"TH","Thief",    "AGI 11",true},
        {"BI","Bishop",   "IQ+PIE",false},
        {"SA","Samurai",  "STR+IQ",false},
        {"LO","Lord",     "ALL 12",false},
        {"NI","Ninja",    "ALL 15",false},
        {nullptr,nullptr,nullptr,false},
    };
    cs(2, rx+1, CP_HEADER, A_BOLD, "  CL  Class        Req     OK?");
    hRule(3, rx, rx+rw);

    for (int i = 0; cls[i].abbr; i++) {
        char row_buf[64];
        snprintf(row_buf, sizeof(row_buf), "  %s  %-10s %-7s", cls[i].abbr, cls[i].name, cls[i].req);
        const char* avail_str = cls[i].avail ? " YES" : " -- ";
        int avail_cp = cls[i].avail ? CP_HP_OK : CP_DIM;
        if (i == 0) {
            // selected class – highlight full row
            char bar[64];
            snprintf(bar, sizeof(bar), "%-*s", rw-2, row_buf);
            cs(4+i, rx+1, CP_SEL, A_BOLD, bar);
        } else {
            int cp = cls[i].avail ? CP_NORMAL : CP_DIM;
            cs(4+i, rx+1, cp, cls[i].avail?0:A_DIM, row_buf);
        }
        cs(4+i, rx+rw-5, avail_cp, A_BOLD, avail_str);
    }

    // Class info
    hRule(13, rx, rx+rw);
    cs(14, rx+2, CP_HEADER, A_BOLD, "FIGHTER");
    cs(15, rx+2, CP_NORMAL, 0, "Front-line melee specialist.");
    cs(16, rx+2, CP_NORMAL, 0, "High HP pool, equips all armor.");
    cs(17, rx+2, CP_HP_HURT,0, "Cannot cast spells.");

    // Level-up bonuses
    drawBox(18, rx, 4, rw, CP_BORDER, "LV UP BONUSES");
    cs(19, rx+2, CP_HP_OK, 0, "HP: d10+VIT    Attacks: 1-2/rd");
    cs(20, rx+2, CP_NORMAL,0, "Crit: 10%      Parry AC bonus: +2");

    screenBadge("2/5  CHARACTER CREATION");
    navBar();
    refresh();
}

// ── SCREEN 3: Exploration ─────────────────────────────────────────────────
//
//  Layout (80×24):
//   row 0        : outer border + header title
//   rows 1-15    : dungeon 3D view box (h=15, w=54)
//   rows 16-18   : message box (h=3, w=54)
//   rows 19-21   : command box (h=3, w=54)
//   rows 1-21    : party panel (h=21, cols 55-78)
//   row 22       : outer border bottom
//   row 23       : nav bar
//
void screenExploration() {
    clear();
    drawBox(0, 0, ROWS-1, COLS);
    ctr(0, " B1F  |  FACING: NORTH  |  POS: (5,7)  |  STEPS: 47 ", CP_HEADER, A_BOLD);

    // ── Dungeon 3D view box ───────────────────────────────────────────────
    int dw = 54, dh = 15;
    drawBox(1, 1, dh, dw, CP_BORDER, "3D VIEW");

    // Viewport interior: vy=2, vx=2, vh=13, vw=52
    int vx = 2, vy = 2, vw = 52, vh = 13;

    // Clear interior to space
    for (int r = 0; r < vh; r++)
        for (int c = 0; c < vw; c++) mvaddch(vy+r, vx+c, ' ');

    // ── Solid wall blocks (4 wide, full height) ───────────────────────────
    attron(COLOR_PAIR(CP_BORDER) | A_BOLD);
    for (int r = 0; r < vh; r++) {
        for (int c = 0; c < 4; c++) {
            mvaddch(vy+r, vx+c,       ACS_BLOCK);
            mvaddch(vy+r, vx+vw-1-c,  ACS_BLOCK);
        }
    }
    // Solid ceiling (top 2 rows, between side walls)
    for (int r = 0; r < 2; r++)
        for (int c = 4; c < vw-4; c++) mvaddch(vy+r, vx+c, ACS_BLOCK);
    // Solid floor (bottom 2 rows, between side walls)
    for (int r = vh-2; r < vh; r++)
        for (int c = 4; c < vw-4; c++) mvaddch(vy+r, vx+c, ACS_BLOCK);
    attroff(COLOR_PAIR(CP_BORDER) | A_BOLD);

    // ── Perspective frames (nested boxes showing corridor depth) ──────────
    attron(COLOR_PAIR(CP_NORMAL) | A_BOLD);

    // Frame 1 – near (rows 2-10, cols 5-46)
    {
        int t=2,b=10,l=5,r=46;
        for (int c=l;c<=r;c++) { mvaddch(vy+t,vx+c,ACS_HLINE); mvaddch(vy+b,vx+c,ACS_HLINE); }
        for (int row=t+1;row<b;row++) { mvaddch(vy+row,vx+l,ACS_VLINE); mvaddch(vy+row,vx+r,ACS_VLINE); }
        mvaddch(vy+t,vx+l,ACS_ULCORNER); mvaddch(vy+t,vx+r,ACS_URCORNER);
        mvaddch(vy+b,vx+l,ACS_LLCORNER); mvaddch(vy+b,vx+r,ACS_LRCORNER);
    }

    // Frame 2 – mid depth (rows 3-9, cols 12-39)
    {
        int t=3,b=9,l=12,r=39;
        for (int c=l;c<=r;c++) { mvaddch(vy+t,vx+c,ACS_HLINE); mvaddch(vy+b,vx+c,ACS_HLINE); }
        for (int row=t+1;row<b;row++) { mvaddch(vy+row,vx+l,ACS_VLINE); mvaddch(vy+row,vx+r,ACS_VLINE); }
        mvaddch(vy+t,vx+l,ACS_ULCORNER); mvaddch(vy+t,vx+r,ACS_URCORNER);
        mvaddch(vy+b,vx+l,ACS_LLCORNER); mvaddch(vy+b,vx+r,ACS_LRCORNER);
    }

    attroff(COLOR_PAIR(CP_NORMAL) | A_BOLD);

    // Frame 3 – far wall solid fill (rows 4-8, cols 18-33)
    {
        int t=4,b=8,l=18,r=33;
        attron(COLOR_PAIR(CP_DIM) | A_DIM);
        for (int row=t;row<=b;row++)
            for (int c=l;c<=r;c++) mvaddch(vy+row,vx+c,ACS_CKBOARD);
        attroff(COLOR_PAIR(CP_DIM) | A_DIM);

        // Door opening cut through center of far wall (cols 22-29)
        int dl=22,dr=29;
        for (int row=t;row<=b;row++)
            for (int c=dl;c<=dr;c++) mvaddch(vy+row,vx+c,' ');

        // Door frame
        attron(COLOR_PAIR(CP_NORMAL) | A_BOLD);
        for (int c=dl;c<=dr;c++) { mvaddch(vy+t,vx+c,'='); mvaddch(vy+b,vx+c,'='); }
        for (int row=t+1;row<b;row++) { mvaddch(vy+row,vx+dl,'|'); mvaddch(vy+row,vx+dr,'|'); }
        attroff(COLOR_PAIR(CP_NORMAL) | A_BOLD);

        // "NORTH" label inside door
        cs(vy+t+1, vx+dl+1, CP_MSG, A_BOLD, " NORTH ");
    }

    // ── Mini-map (top-left of viewport) ──────────────────────────────────
    cs(vy+1, vx+5, CP_MSG, A_BOLD, "MAP:");
    const char* mm[] = {"##.##","#...#","..@..","#...#","##.##",nullptr};
    for (int r = 0; mm[r]; r++) {
        for (int c = 0; mm[r][c]; c++) {
            char ch = mm[r][c];
            if      (ch=='@') cs(vy+2+r, vx+5+c, CP_MSG,    A_BOLD, "@");
            else if (ch=='#') { attron(COLOR_PAIR(CP_DIM)|A_DIM); mvaddch(vy+2+r, vx+5+c, ACS_CKBOARD); attroff(COLOR_PAIR(CP_DIM)|A_DIM); }
            else              { attron(COLOR_PAIR(CP_DIM)|A_DIM); mvaddch(vy+2+r, vx+5+c, '.'); attroff(COLOR_PAIR(CP_DIM)|A_DIM); }
        }
    }

    // ── Message box ───────────────────────────────────────────────────────
    drawBox(16, 1, 3, dw, CP_BORDER, "MESSAGE");
    cs(17, 3, CP_MSG, 0, "You see a torch-lit corridor extending to the north.");

    // ── Command box ───────────────────────────────────────────────────────
    drawBox(19, 1, 3, dw, CP_BORDER, "MOVE");
    cs(20, 3, CP_NORMAL, 0, "[N]orth [S]outh [E]ast [W]est  [T]urn  [C]amp  [M]agic  [I]nspect");

    // ── Party panel (cols 56 to 78) ───────────────────────────────────────
    int px = dw + 2, pw = COLS - px - 1;   // x=56, w=23
    drawBox(1, px, 21, pw, CP_BORDER, "PARTY");

    cs(2, px+1, CP_HEADER, A_BOLD, "#  Name     CL  HP");
    hRule(3, px, px+pw);

    struct PM { const char* name; const char* cls; int hp, mhp; };
    PM party[] = {
        {"THORIN",  "FT", 45, 45},
        {"MERLIN",  "MA", 12, 12},
        {"ELOWEN",  "PR", 28, 28},
        {"SHADOW",  "TH", 11, 30},
        {"BRUNHLD", "FT", 38, 38},
        {"ALDRIC",  "SA", 31, 31},
        {nullptr, nullptr, 0, 0},
    };
    for (int i = 0; party[i].name; i++) {
        char buf[32];
        snprintf(buf, sizeof(buf), "%d  %-7s %s", i+1, party[i].name, party[i].cls);
        cs(4+i, px+1, CP_NORMAL, 0, buf);
        snprintf(buf, sizeof(buf), "%3d/%-3d", party[i].hp, party[i].mhp);
        cs(4+i, px+14, hpColor(party[i].hp, party[i].mhp), A_BOLD, buf);
    }

    hRule(11, px, px+pw);

    // Compass
    int cx = px + pw/2;
    cs(12, cx-2, CP_HEADER, A_BOLD, "[N]");
    cs(13, cx-4, CP_HEADER, A_BOLD, "[W] @  [E]");
    cs(14, cx-2, CP_HEADER, A_BOLD, "[S]");

    hRule(15, px, px+pw);
    cs(16, px+2, CP_GOLD,   A_BOLD, "GOLD: 2,450 gp");
    cs(17, px+2, CP_NORMAL, 0,      "Floor: B1F  Day 3");
    cs(18, px+2, CP_DIM,    A_DIM,  "T: Torches x4");

    screenBadge("3/5  EXPLORATION");
    navBar();
    refresh();
}

// ── SCREEN 4: Combat ──────────────────────────────────────────────────────
//
//  Layout (80×24):
//   rows  1-11  : enemy display (left, h=11, w=47) + party status (right)
//   rows 12-18  : combat log (full width, h=7)
//   rows 19-22  : action menu (h=4)
//
void screenCombat() {
    clear();
    drawBox(0, 0, ROWS-1, COLS);
    ctr(0, " !! COMBAT !! ", CP_HP_DEAD, A_BOLD);

    // ── Enemy display (left) ──────────────────────────────────────────────
    int ew = 47, eh = 11;
    drawBox(1, 1, eh, ew, CP_BORDER, "ENEMIES");

    // ASCII orc art
    const char* orc[] = {
        "    .---.       .---.  ",
        "   /o   o\\     /o   o\\",
        "   | -=- |     | -=- | ",
        "    \\___/       \\___/ ",
        "   /|   |\\     /|   |\\",
        "  / |   | \\   / |   | \\",
        nullptr,
    };
    for (int i = 0; orc[i]; i++)
        cs(2+i, 3, CP_HP_DEAD, A_BOLD, orc[i]);

    cs(3, 28, CP_TITLE,   A_BOLD, "ORC");
    cs(4, 28, CP_NORMAL,  0,      "WARBAND");
    cs(5, 28, CP_HP_HURT, 0,      "x3  Lv.4");
    cs(6, 28, CP_NORMAL,  0,      "TOUGH");
    cs(7, 28, CP_NORMAL,  0,      "ARMED");

    // Enemy HP bar
    cs(9, 3, CP_HEADER, A_BOLD, "HP:");
    cs(9, 7, CP_HP_HURT, A_BOLD, "[##########----]");
    cs(9, 24, CP_NORMAL, 0,      "62 / 90");

    // ── Party status (right) ──────────────────────────────────────────────
    int px = ew + 2, pw = COLS - px - 1;
    drawBox(1, px, eh, pw, CP_BORDER, "PARTY");
    cs(2, px+1, CP_HEADER, A_BOLD, "#  Name     HP      Status");
    hRule(3, px, px+pw);

    struct CF { const char* name; int hp, mhp; const char* sta; int sta_cp; };
    CF pf[] = {
        {"THORIN",   45, 45, "Ok   ", CP_HP_OK},
        {"MERLIN",   12, 12, "Ok   ", CP_HP_OK},
        {"ELOWEN",   28, 28, "Ok   ", CP_HP_OK},
        {"SHADOW",   11, 30, "HURT ", CP_HP_DEAD},
        {"BRUNHLD",  38, 38, "PRRNG", CP_MSG},
        {"ALDRIC",   31, 31, "Ok   ", CP_HP_OK},
        {nullptr,0,0,nullptr,0},
    };
    for (int i = 0; pf[i].name; i++) {
        char buf[32];
        snprintf(buf, sizeof(buf), "%d  %-7s", i+1, pf[i].name);
        cs(4+i, px+1, CP_NORMAL, 0, buf);
        snprintf(buf, sizeof(buf), "%3d/%-3d", pf[i].hp, pf[i].mhp);
        cs(4+i, px+12, hpColor(pf[i].hp, pf[i].mhp), A_BOLD, buf);
        cs(4+i, px+21, pf[i].sta_cp, A_BOLD, pf[i].sta);
    }

    // ── Combat log ───────────────────────────────────────────────────────
    drawBox(12, 1, 7, COLS-2, CP_BORDER, "COMBAT LOG  (Round 3)");

    struct LE { const char* text; int cp; };
    LE log[] = {
        {"  Orc #1 attacks SHADOW for 11 damage.  SHADOW is HURT!",    CP_HP_DEAD},
        {"  Orc #2 attacks THORIN... Miss!",                           CP_DIM},
        {"  THORIN strikes Orc #1 — Critical Hit!  18 damage.",        CP_HP_OK},
        {"  MERLIN casts KATINO (Sleep)... Orc #3 falls asleep!",      CP_HP_OK},
        {"  ELOWEN casts DIOS (Heal) on SHADOW... +8 HP restored.",    CP_MSG},
        {nullptr, 0},
    };
    for (int i = 0; log[i].text; i++)
        cs(13+i, 3, log[i].cp, (log[i].cp==CP_DIM)?A_DIM:0, log[i].text);

    // ── Action menu ───────────────────────────────────────────────────────
    drawBox(19, 1, 4, COLS-2, CP_BORDER, "ROUND 4 — Choose Action: THORIN");

    struct Act { const char* key; const char* lbl; bool sel; };
    Act acts[] = {
        {"F","Fight",true}, {"P","Parry",false}, {"S","Spell",false},
        {"U","Use",false},  {"R","Run",false},   {nullptr,nullptr,false},
    };
    int ax = 4;
    for (int i = 0; acts[i].key; i++) {
        char btn[24];
        snprintf(btn, sizeof(btn), " [%s] %s ", acts[i].key, acts[i].lbl);
        cs(20, ax, acts[i].sel ? CP_SEL : CP_NORMAL, acts[i].sel ? A_BOLD : 0, btn);
        ax += strlen(btn) + 1;
    }
    cs(21, 3, CP_DIM, A_DIM, "Awaiting actions: MERLIN, ELOWEN, SHADOW, BRUNHILD, ALDRIC");

    screenBadge("4/5  COMBAT");
    navBar();
    refresh();
}

// ── SCREEN 5: XP & Loot ──────────────────────────────────────────────────
void screenXPLoot() {
    clear();
    drawBox(0, 0, ROWS-1, COLS);
    ctr(0, " VICTORY! ", CP_TITLE, A_BOLD);

    // Battle report
    drawBox(1, 1, 3, COLS-2, CP_BORDER, "BATTLE REPORT");
    cs(2, 3, CP_HP_OK,  A_BOLD, "The Orc Warband has been defeated!   3 orcs slain, 4 rounds.");
    cs(3, 3, CP_NORMAL, 0,      "Party damage taken: 26 HP total.     Spells used: 3.");

    // ── XP panel (left half) ──────────────────────────────────────────────
    int lw = COLS/2 - 1;
    drawBox(4, 1, 10, lw, CP_BORDER, "EXPERIENCE");
    cs(5, 3, CP_HEADER, A_BOLD, "Name       Prev     +XP    Total   Lv");
    hRule(6, 1, lw+1);

    struct XP { const char* name; int prev; int gain; int lv_old; int lv_new; };
    XP xp[] = {
        {"THORIN",   4820, 250, 4, 4},
        {"MERLIN",   2100, 250, 3, 3},
        {"ELOWEN",   3300, 250, 3, 3},
        {"SHADOW",   1800, 125, 2, 3},   // level up!
        {"BRUNHLD",  5100, 250, 4, 5},   // level up!
        {"ALDRIC",   2750, 250, 3, 3},
        {nullptr, 0, 0, 0, 0},
    };
    for (int i = 0; xp[i].name; i++) {
        bool up = xp[i].lv_new > xp[i].lv_old;
        char buf[64];
        snprintf(buf, sizeof(buf), "%-8s  %5d   +%3d   %5d   %d",
            xp[i].name, xp[i].prev, xp[i].gain, xp[i].prev+xp[i].gain, xp[i].lv_new);
        cs(7+i, 3, up?CP_TITLE:CP_NORMAL, up?A_BOLD:0, buf);
        if (up) cs(7+i, 3+38, CP_TITLE, A_BOLD, "***UP");
    }

    // ── Right column: gold + loot ──────────────────────────────────────────
    int rx = lw + 2, rw = COLS - rx - 1;

    drawBox(4, rx, 4, rw, CP_BORDER, "GOLD");
    cs(5, rx+2, CP_GOLD, A_BOLD, "Found:       120 gp");
    cs(6, rx+2, CP_GOLD, 0,      "Each share:   20 gp");
    cs(7, rx+2, CP_GOLD, 0,      "Total pool: 2,570 gp");

    drawBox(8, rx, 7, rw, CP_BORDER, "ITEMS FOUND");
    cs( 9, rx+2, CP_MSG,    A_BOLD, "Orc Armor +1     [UNCOMMON]");
    cs(10, rx+2, CP_HP_OK,  0,      "Healing Potion   [COMMON]  ");
    cs(11, rx+2, CP_NORMAL, 0,      "Rusty Shortsword [COMMON]  ");
    cs(12, rx+2, CP_DIM,    A_DIM,  "Orc Token x3     [JUNK]    ");
    cs(13, rx+2, CP_DIM,    A_DIM,  "Broken Shield    [JUNK]    ");

    // ── Level-up details ──────────────────────────────────────────────────
    drawBox(14, 1, 7, COLS-2, CP_BORDER, "LEVEL UP!");

    cs(15, 3, CP_TITLE, A_BOLD, "SHADOW  -->  Level 3  (Thief)");
    cs(16, 5, CP_HP_OK, 0,      "HP: +8  (22 -> 30)    New skill: Backstab II  (+2d6 bonus dmg)");

    cs(17, 3, CP_TITLE, A_BOLD, "BRUNHILD  -->  Level 5  (Fighter)");
    cs(18, 5, CP_HP_OK, 0,      "HP: +12 (38 -> 50)    New skill: Extra Attack (+1 attack/round)");

    hRule(19, 1, COLS-1);
    cs(20, 3, CP_GOLD, A_BOLD,  "BRUNHILD may now change class to SAMURAI — requirements met.");

    ctr(ROWS-2, "[ ENTER to distribute loot and continue exploration ]", CP_SEL, A_BOLD);

    screenBadge("5/5  XP & LOOT");
    navBar();
    refresh();
}

// ── Main ──────────────────────────────────────────────────────────────────
int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    getmaxyx(stdscr, ROWS, COLS);

    if (!has_colors()) {
        endwin();
        fputs("Error: terminal does not support color.\n", stderr);
        return 1;
    }
    initColors();

    if (ROWS < 24 || COLS < 80) {
        clear();
        char msg[80];
        snprintf(msg, sizeof(msg),
            "Terminal too small! Need 80x24 minimum; got %dx%d.", COLS, ROWS);
        mvaddstr(ROWS/2, 0, msg);
        refresh(); getch(); endwin(); return 1;
    }

    using ScreenFn = void(*)();
    ScreenFn screens[] = {
        screenMainMenu,
        screenCharCreation,
        screenExploration,
        screenCombat,
        screenXPLoot,
    };
    const int N = 5;
    int cur = 0;

    screens[cur]();

    bool running = true;
    while (running) {
        int ch = getch();
        switch (ch) {
            case 'q': case 'Q':
                running = false; break;
            case ' ': case '\n': case '\r': case KEY_RIGHT: case KEY_DOWN:
                cur = (cur + 1) % N; break;
            case 'b': case 'B': case KEY_LEFT: case KEY_UP:
                cur = (cur - 1 + N) % N; break;
            case '1': cur = 0; break;
            case '2': cur = 1; break;
            case '3': cur = 2; break;
            case '4': cur = 3; break;
            case '5': cur = 4; break;
        }
        if (running) screens[cur]();
    }

    endwin();
    return 0;
}
