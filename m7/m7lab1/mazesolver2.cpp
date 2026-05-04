// ============================================================
// CSC 134 - M7LAB1: MazeBuilder (Merged + Annotated)
// Original source: https://github.com/norrisaftcc/MazeBuilder
// Porting history: Ruby -> C# -> C++ (see README)
//
// This file merges maze_builder.cpp and the Dijkstra extension
// into one compilable program.
//
// HEADS UP: This code uses classes, vectors, and priority queues --
// things you'll cover in CSC 246. You don't need to understand
// how they're built to use them. Read the comments for the "what"
// and the "why"; trust the implementation for now.
//
// Compile: g++ -std=c++17 -Wall -Wextra -o maze maze_builder.cpp
// Run:     ./maze
//          ./maze 15 20
//          ./maze --help
// ============================================================

#include <iostream>
#include <vector>       // std::vector -- like a resizable array
#include <random>       // mt19937 -- a high-quality random number generator
#include <ctime>        // std::time -- used to seed the RNG
#include <cstring>      // strcmp -- used for command-line argument parsing
#include <queue>        // std::priority_queue -- used by Dijkstra's algorithm
#include <unordered_map>// std::unordered_map -- a fast key/value lookup table
#include <limits>       // std::numeric_limits -- used to represent "infinity"
#include <utility>      // std::pair -- a struct holding two values together
#include <algorithm>    // std::reverse, std::find
#include <string>

using namespace std;

// ============================================================
// SECTION 1: DIRECTION CONSTANTS
//
// Directions are stored as powers of 2 (1, 2, 4, 8) so they
// can be combined as bit flags in a single int.
//
// Example: a cell linked NORTH and EAST has links = 1 | 4 = 5
// You can then test individual directions with bitwise AND:
//   links & NORTH  -> nonzero if linked north
//   links & EAST   -> nonzero if linked east
//
// This is an "enum" -- a named set of integer constants.
// Using names like NORTH is clearer than remembering that
// north = 1, south = 2, etc.
// ============================================================

enum Direction {
    NORTH = 1,   // binary: 0001
    SOUTH = 2,   // binary: 0010
    EAST  = 4,   // binary: 0100
    WEST  = 8    // binary: 1000
};

// ============================================================
// DIRECTION_OFFSETS: How many rows/cols to move in each direction
//
// Indexed by Direction value (1, 2, 4, 8).
// The in-between indices (0, 3, 5, 6, 7) are unused placeholders.
// Using Direction values directly as indices is the trick here:
//   DIRECTION_OFFSETS[NORTH] == DIRECTION_OFFSETS[1] == {0, -1}
//   meaning: col += 0, row += -1 (move up one row)
//
// Format: {col_delta, row_delta}
// ============================================================

const pair<int, int> DIRECTION_OFFSETS[] = {
    { 0,  0},   // [0] unused placeholder
    { 0, -1},   // [1] NORTH -- same column, one row up
    { 0,  1},   // [2] SOUTH -- same column, one row down
    { 0,  0},   // [3] unused placeholder
    { 1,  0},   // [4] EAST  -- one column right, same row
    { 0,  0},   // [5] unused placeholder
    { 0,  0},   // [6] unused placeholder
    { 0,  0},   // [7] unused placeholder
    {-1,  0}    // [8] WEST  -- one column left, same row
};

// ============================================================
// OPPOSITES: The reverse direction of each Direction value.
//
// When we carve a passage from cell A to cell B going NORTH,
// cell B must also record a passage going SOUTH back to A.
// OPPOSITES lets us look up the reverse automatically.
//
// Same indexing trick as DIRECTION_OFFSETS.
// ============================================================

const Direction OPPOSITES[] = {
    (Direction)0,   // [0] unused
    SOUTH,          // [1] opposite of NORTH is SOUTH
    NORTH,          // [2] opposite of SOUTH is NORTH
    (Direction)0,   // [3] unused
    WEST,           // [4] opposite of EAST is WEST
    (Direction)0,   // [5] unused
    (Direction)0,   // [6] unused
    (Direction)0,   // [7] unused
    EAST            // [8] opposite of WEST is EAST
};

// ============================================================
// SECTION 2: CELL CLASS
//
// A Cell represents one square in the maze grid.
// It knows its position (row, col) and which neighbors it has
// passages carved to (stored as bit flags in "links").
//
// Think of it as one room in a building:
//   - It knows where it is
//   - It knows which walls have been knocked down (links)
//   - It doesn't know anything about the building as a whole
// ============================================================

class Cell {
private:
    int row;
    int col;
    int links;  // Bit flags recording which directions have open passages
                // e.g., links = 5 means NORTH(1) and EAST(4) are open

public:
    // Constructor: creates a cell at (row, col) with all walls intact
    Cell(int row, int col) : row(row), col(col), links(0) {}

    // Simple getters -- return the stored position
    int getRow() const { return row; }
    int getCol() const { return col; }

    // Returns true if this cell has an open passage in the given direction.
    // Uses bitwise AND: if the direction's bit is set in links, the passage exists.
    bool linked(Direction direction) const {
        return (links & direction) != 0;
    }

    // Carves a passage in the given direction.
    // Uses bitwise OR to set that direction's bit without disturbing others.
    void link(Direction direction) {
        links |= direction;
    }

    // Seals a passage (closes a wall). Rarely used in generation,
    // but useful for maze editing.
    // Uses bitwise AND with NOT to clear that direction's bit.
    void unlink(Direction direction) {
        links &= ~direction;
    }

    // Returns a list of all directions that currently have open passages.
    // Used by the pathfinding algorithm to find valid moves.
    vector<Direction> getLinks() const {
        vector<Direction> result;
        if (linked(NORTH)) result.push_back(NORTH);
        if (linked(SOUTH)) result.push_back(SOUTH);
        if (linked(EAST))  result.push_back(EAST);
        if (linked(WEST))  result.push_back(WEST);
        return result;
    }
};

// ============================================================
// SECTION 3: GRID CLASS
//
// The Grid is the full maze -- a 2D collection of Cells.
// It manages:
//   - Creating and storing all the cells
//   - Carving passages between adjacent cells
//   - Providing random numbers for the generation algorithm
//   - Displaying the finished maze as ASCII art
//
// Think of it as the building that contains all the rooms (Cells).
// ============================================================

class Grid {
private:
    int rows;
    int cols;
    vector<vector<Cell>> cells;  // 2D grid: cells[row][col]
    mt19937 rng;                 // Mersenne Twister RNG (high quality random)

public:
    // Constructor: builds an empty rows x cols grid, all walls intact.
    // Seeds the random number generator from the current time so each
    // run produces a different maze.
    Grid(int rows, int cols) : rows(rows), cols(cols) {
        rng.seed(static_cast<unsigned int>(time(nullptr)));

        // Build the 2D cell grid row by row
        cells.resize(rows);
        for (int r = 0; r < rows; r++) {
            cells[r].reserve(cols);
            for (int c = 0; c < cols; c++) {
                cells[r].emplace_back(r, c);  // construct Cell(r, c) in place
            }
        }
    }

    int getRows() const { return rows; }
    int getCols() const { return cols; }

    // Bounds check -- returns true if (row, col) is inside the grid.
    // Always call this before using at(row, col) with computed coordinates.
    bool isValid(int row, int col) const {
        return row >= 0 && row < rows && col >= 0 && col < cols;
    }

    // Direct cell access by position.
    // Two versions: one for modification, one for read-only (const) contexts.
    Cell& at(int row, int col) {
        return cells[row][col];
    }

    const Cell& at(int row, int col) const {
        return cells[row][col];
    }

    // Returns a random int between min and max, inclusive.
    // Used by the maze generation algorithm to pick random directions.
    int random(int min, int max) {
        uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }

    // Carves a bidirectional passage between a cell and its neighbor
    // in the given direction.
    //
    // Why bidirectional? If cell A is linked NORTH to cell B,
    // then cell B must also be linked SOUTH to cell A, or the
    // display logic will show inconsistent walls.
    void linkCells(int row1, int col1, Direction dir) {
        if (!isValid(row1, col1)) return;

        // Calculate the neighbor's position using the direction offset
        int row2 = row1 + DIRECTION_OFFSETS[dir].second;
        int col2 = col1 + DIRECTION_OFFSETS[dir].first;

        if (!isValid(row2, col2)) return;

        // Carve the passage both ways
        at(row1, col1).link(dir);
        at(row2, col2).link(OPPOSITES[dir]);
    }

    // Renders the maze as ASCII art to stdout.
    //
    // Each cell takes up a 3-character wide space between walls.
    // Horizontal walls are "---", vertical walls are "|".
    // An open passage replaces the wall with spaces.
    //
    // Example output for a 3x3 maze:
    //   +---+---+---+
    //   |           |
    //   +   +---+   +
    //   |   |   |   |
    //   +   +   +   +
    //   |       |   |
    //   +---+---+---+
    void display() const {
        // Top border
        cout << "+";
        for (int c = 0; c < cols; c++) {
            cout << "---+";
        }
        cout << endl;

        for (int r = 0; r < rows; r++) {
            // Row interior: left wall, then each cell's east boundary
            cout << "|";
            for (int c = 0; c < cols; c++) {
                cout << "   ";  // cell interior (always 3 spaces)

                // East wall: space if passage exists, | if wall
                if (c < cols - 1 && cells[r][c].linked(EAST)) {
                    cout << " ";   // open passage east
                } else {
                    cout << "|";   // wall
                }
            }
            cout << endl;

            // Row bottom: south wall of each cell, or open passage
            cout << "+";
            for (int c = 0; c < cols; c++) {
                if (r < rows - 1 && cells[r][c].linked(SOUTH)) {
                    cout << "   +";  // open passage south
                } else {
                    cout << "---+";  // wall
                }
            }
            cout << endl;
        }
    }
};

// ============================================================
// SECTION 4: BINARY TREE MAZE GENERATOR
//
// This class contains the algorithm that carves passages through
// the blank grid to create a maze.
//
// The Binary Tree algorithm:
//   For each cell (left to right, top to bottom):
//     - Build a list of valid directions: NORTH if not top row,
//       EAST if not rightmost column
//     - Pick one direction at random and carve a passage
//     - Corner/edge cells with only one option: take it
//     - Top-right corner: no valid directions, skip it
//
// Result: a "perfect maze" -- exactly one path between any two cells.
// Bias: the top row always opens east, the right column always
// opens north. This creates a visible diagonal drift toward the
// northeast corner.
//
// "Static" means we call it as BinaryTreeMaze::on(grid) without
// creating a BinaryTreeMaze object. It's just a named container
// for the function.
// ============================================================

class BinaryTreeMaze {
public:
    static void on(Grid& grid) {
        for (int r = 0; r < grid.getRows(); r++) {
            for (int c = 0; c < grid.getCols(); c++) {

                // Build the list of valid carving directions for this cell
                vector<Direction> neighbors;

                if (r > 0)                    neighbors.push_back(NORTH);
                if (c < grid.getCols() - 1)   neighbors.push_back(EAST);

                // Pick one direction at random and carve
                if (!neighbors.empty()) {
                    int index = grid.random(0, (int)neighbors.size() - 1);
                    grid.linkCells(r, c, neighbors[index]);
                }
                // If neighbors is empty (top-right corner): do nothing
            }
        }
    }
};

// ============================================================
// SECTION 5: DISTANCES CLASS
//
// Distances tracks how many steps it takes to reach each cell
// from a chosen starting point. The pathfinding algorithm fills
// this in, then uses it to trace the shortest route.
//
// Internally it uses an unordered_map (a hash table) to map
// cell positions to their distances. The key is a string like
// "3,7" for the cell at row 3, column 7.
//
// You haven't seen unordered_map yet -- think of it as an array
// you can index with strings instead of integers.
// ============================================================

class Distances {
private:
    unordered_map<string, int> cells;  // "row,col" -> steps from start
    Cell* root;                        // the starting cell

    // Converts a (row, col) pair to a string key for the map.
    // "3,7" is easier to hash than a struct would be at this stage.
    string makeKey(int row, int col) const {
        return to_string(row) + "," + to_string(col);
    }

    string makeKey(const Cell& cell) const {
        return makeKey(cell.getRow(), cell.getCol());
    }

    // Parses "row,col" back into separate integers.
    // Returns false if the key is malformed (safety check).
    bool parseKey(const string& key, int& row, int& col) const {
        size_t comma = key.find(',');
        if (comma == string::npos) return false;
        row = stoi(key.substr(0, comma));
        col = stoi(key.substr(comma + 1));
        return true;
    }

public:
    // Start with the root cell at distance 0
    Distances(Cell& start) : root(&start) {
        cells[makeKey(start)] = 0;
    }

    // Returns the recorded distance to this cell,
    // or INT_MAX ("infinity") if we haven't reached it yet.
    int getDistance(const Cell& cell) const {
        auto it = cells.find(makeKey(cell));
        if (it != cells.end()) return it->second;
        return numeric_limits<int>::max();
    }

    // Records the distance to a cell (called as Dijkstra explores)
    void setDistance(const Cell& cell, int distance) {
        cells[makeKey(cell)] = distance;
    }

    // Returns pointers to every cell that has been assigned a distance.
    // Used for heat-map style displays (not used in this assignment, but available).
    vector<Cell*> getCells(Grid& grid) const {
        vector<Cell*> result;
        for (const auto& pair : cells) {
            int row, col;
            if (parseKey(pair.first, row, col) && grid.isValid(row, col)) {
                result.push_back(&grid.at(row, col));
            }
        }
        return result;
    }

    // Returns a pointer to the cell farthest from the starting cell.
    // Used by longestPath() to find the two ends of the hardest route.
    Cell* getMaxCell(Grid& grid) const {
        Cell* maxCell = root;
        int   maxDist = 0;

        for (const auto& pair : cells) {
            if (pair.second > maxDist) {
                int row, col;
                if (parseKey(pair.first, row, col) && grid.isValid(row, col)) {
                    maxCell = &grid.at(row, col);
                    maxDist = pair.second;
                }
            }
        }
        return maxCell;
    }

    // Returns the largest distance value stored (the "diameter" of the explored region)
    int getMaxDistance() const {
        int maxDist = 0;
        for (const auto& pair : cells) {
            maxDist = max(maxDist, pair.second);
        }
        return maxDist;
    }
};

// ============================================================
// SECTION 6: DIJKSTRA'S ALGORITHM
//
// Dijkstra's algorithm finds the shortest path from a start cell
// to every other reachable cell in the maze.
//
// How it works (conceptually):
//   1. Assign every cell a distance of "infinity" except the start (distance 0)
//   2. Keep a priority queue of cells to explore, starting with the start cell
//   3. Always process the cell with the SMALLEST known distance next
//   4. For each neighbor reachable through an open passage:
//        If (current distance + 1) < neighbor's recorded distance:
//          update the neighbor's distance and add it to the queue
//   5. Repeat until the queue is empty
//
// Because all passages have equal weight (cost 1), this is
// equivalent to BFS -- but Dijkstra generalizes to weighted graphs.
//
// After calculateDistances() runs, shortestPath() traces backward
// from the end cell to the start by always stepping to the
// neighbor with the next-smaller distance.
// ============================================================

class Dijkstra {
public:
    // Runs Dijkstra's from 'start', returns a Distances object
    // containing the shortest distance from 'start' to every reachable cell.
    static Distances calculateDistances(Grid& grid, Cell& start) {
        Distances distances(start);

        // Priority queue: processes (distance, "row,col") pairs,
        // smallest distance first (min-heap via std::greater).
        priority_queue<
            pair<int, string>,
            vector<pair<int, string>>,
            greater<pair<int, string>>
        > frontier;

        // Helper: converts a Cell to its string key
        auto cellKey = [](const Cell& cell) {
            return to_string(cell.getRow()) + "," + to_string(cell.getCol());
        };

        frontier.push({0, cellKey(start)});

        while (!frontier.empty()) {
            // Get the closest unprocessed cell
            auto [dist, key] = frontier.top();
            frontier.pop();

            // Parse the key back to row/col
            size_t comma = key.find(',');
            if (comma == string::npos) continue;
            int row = stoi(key.substr(0, comma));
            int col = stoi(key.substr(comma + 1));
            if (!grid.isValid(row, col)) continue;

            Cell& cell = grid.at(row, col);
            int cellDist = distances.getDistance(cell);

            // Explore all linked (reachable) neighbors
            for (Direction dir : cell.getLinks()) {
                int nRow = row + DIRECTION_OFFSETS[dir].second;
                int nCol = col + DIRECTION_OFFSETS[dir].first;
                if (!grid.isValid(nRow, nCol)) continue;

                Cell& neighbor = grid.at(nRow, nCol);
                int newDist = cellDist + 1;

                // If we found a shorter route to this neighbor, update it
                if (newDist < distances.getDistance(neighbor)) {
                    distances.setDistance(neighbor, newDist);
                    frontier.push({newDist, cellKey(neighbor)});
                }
            }
        }

        return distances;
    }

    // Returns the sequence of cells forming the shortest path
    // from 'start' to 'end'. Returns an empty vector if no path exists.
    //
    // Strategy: run Dijkstra from start to get all distances,
    // then walk backward from end -- at each step, move to whichever
    // linked neighbor has the next-smaller distance value.
    static vector<Cell*> shortestPath(Grid& grid, Cell& start, Cell& end) {
        Distances distances = calculateDistances(grid, start);

        // If end was never reached, return empty (no path)
        if (distances.getDistance(end) == numeric_limits<int>::max()) {
            return {};
        }

        // Trace back from end to start
        vector<Cell*> path;
        Cell* current = &end;
        path.push_back(current);

        while (current != &start) {
            int row = current->getRow();
            int col = current->getCol();
            int curDist = distances.getDistance(*current);

            Cell* next = nullptr;
            int nextDist = curDist;

            // Find the linked neighbor one step closer to start
            for (Direction dir : current->getLinks()) {
                int nRow = row + DIRECTION_OFFSETS[dir].second;
                int nCol = col + DIRECTION_OFFSETS[dir].first;
                if (!grid.isValid(nRow, nCol)) continue;

                Cell& neighbor = grid.at(nRow, nCol);
                if (distances.getDistance(neighbor) < nextDist) {
                    next = &neighbor;
                    nextDist = distances.getDistance(neighbor);
                }
            }

            if (next == nullptr) break;  // Shouldn't happen in a perfect maze
            path.push_back(next);
            current = next;
        }

        // Path was built end -> start; reverse to get start -> end
        reverse(path.begin(), path.end());
        return path;
    }

    // Finds the longest shortest path in the maze -- the "hardest" route.
    //
    // Trick: in a perfect maze, the longest path connects the two cells
    // that are farthest apart. Finding them takes two Dijkstra passes:
    //   Pass 1: From any cell (we use 0,0), find the farthest cell A
    //   Pass 2: From A, find the farthest cell B
    //   Result: shortestPath(A, B) is the longest path in the maze
    static vector<Cell*> longestPath(Grid& grid) {
        Cell& origin = grid.at(0, 0);

        Distances pass1 = calculateDistances(grid, origin);
        Cell* cellA = pass1.getMaxCell(grid);

        Distances pass2 = calculateDistances(grid, *cellA);
        Cell* cellB = pass2.getMaxCell(grid);

        return shortestPath(grid, *cellA, *cellB);
    }
};

// ============================================================
// SECTION 7: DISPLAY WITH PATH
//
// Renders the maze with the solution path highlighted.
// Same logic as Grid::display(), but cells on the path
// show 'X' instead of spaces.
//
// The 'path' parameter is a vector of Cell pointers.
// isOnPath() checks if the current cell's address matches
// any pointer in the path list.
// ============================================================

void displayWithPath(const Grid& grid, const vector<Cell*>& path) {
    // Lambda: returns true if 'cell' is on the solution path
    auto isOnPath = [&path](const Cell* cell) {
        return find(path.begin(), path.end(), cell) != path.end();
    };

    // Top border
    cout << "+";
    for (int c = 0; c < grid.getCols(); c++) cout << "---+";
    cout << endl;

    for (int r = 0; r < grid.getRows(); r++) {
        // Cell row: left wall, then each cell's content and east boundary
        cout << "|";
        for (int c = 0; c < grid.getCols(); c++) {
            // Mark path cells with X, everything else with spaces
            cout << (isOnPath(&grid.at(r, c)) ? " X " : "   ");

            // East wall or open passage
            if (c < grid.getCols() - 1 && grid.at(r, c).linked(EAST)) {
                cout << " ";
            } else {
                cout << "|";
            }
        }
        cout << endl;

        // Bottom boundary row
        cout << "+";
        for (int c = 0; c < grid.getCols(); c++) {
            if (r < grid.getRows() - 1 && grid.at(r, c).linked(SOUTH)) {
                cout << "   +";
            } else {
                cout << "---+";
            }
        }
        cout << endl;
    }
}

// ============================================================
// SECTION 8: HELP TEXT
// ============================================================

void print_help(const char* program_name) {
    cout << "MazeBuilder -- Binary Tree maze generator + Dijkstra solver\n\n";
    cout << "Usage: " << program_name << " [OPTIONS] [rows] [columns]\n\n";
    cout << "Arguments:\n";
    cout << "  rows       Number of rows    (default: 10)\n";
    cout << "  columns    Number of columns (default: 10)\n\n";
    cout << "Options:\n";
    cout << "  -h, --help   Show this message\n\n";
    cout << "Examples:\n";
    cout << "  " << program_name << "           10x10 maze\n";
    cout << "  " << program_name << " 20        20x20 maze\n";
    cout << "  " << program_name << " 15 25     15x25 maze\n\n";
    cout << "Algorithm notes:\n";
    cout << "  Generator: Binary Tree (carves north or east at each cell)\n";
    cout << "  Solver:    Dijkstra's algorithm (finds longest shortest path)\n";
    cout << "  Bias:      Northeast corner -- the algorithm's visible fingerprint\n";
}

// ============================================================
// SECTION 9: MAIN
//
// Ties everything together:
//   1. Parse optional command-line arguments (rows, cols)
//   2. Build the grid and generate the maze
//   3. Display the raw maze
//   4. Find and display the solution path
//   5. Print statistics
// ============================================================

int main(int argc, char* argv[]) {
    int rows = 10;
    int cols = 10;

    // Check for help flag before anything else
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_help(argv[0]);
            return 0;
        }
    }

    // Parse optional size arguments
    if (argc > 1) rows = atoi(argv[1]);
    if (argc > 2) cols = atoi(argv[2]);

    // Basic sanity check on dimensions
    if (rows < 2 || cols < 2 || rows > 50 || cols > 100) {
        cout << "Error: rows must be 2-50, columns must be 2-100.\n";
        return 1;
    }

    // --- Generate the maze ---
    Grid grid(rows, cols);
    BinaryTreeMaze::on(grid);

    cout << "Generated Maze (" << rows << " x " << cols << "):\n";
    grid.display();
    cout << endl;

    // --- Solve it ---
    // longestPath() finds the two cells that are farthest apart
    // and returns the shortest path between them. In a perfect maze,
    // this is always the "hardest" route from one end to the other.
    vector<Cell*> solution = Dijkstra::longestPath(grid);

    cout << "Maze Solution:\n";
    displayWithPath(grid, solution);
    cout << endl;

    // --- Statistics ---
    int steps = (int)solution.size() - 1;
    int total = rows * cols;
    double coverage = (solution.size() * 100.0) / total;

    cout << "Solution: " << solution.size() << " cells, "
         << steps << " steps\n";
    cout << "Coverage: " << coverage << "% of the maze\n";

    return 0;
}