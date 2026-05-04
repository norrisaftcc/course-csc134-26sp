#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cstring>
#include <queue>
#include <unordered_map>
#include <limits>
#include <utility>
#include <algorithm>
#include <string>

using namespace std;

// Direction constants
enum Direction {
    NORTH = 1,
    SOUTH = 2,
    EAST = 4,
    WEST = 8
};

// Mapping of direction to cell offset
const std::pair<int, int> DIRECTION_OFFSETS[] = {
    {0, 0},     // Placeholder for index 0
    {0, -1},    // NORTH
    {0, 1},     // SOUTH
    {0, 0},     // Placeholder
    {1, 0},     // EAST
    {0, 0},     // Placeholder
    {0, 0},     // Placeholder
    {0, 0},     // Placeholder
    {-1, 0}     // WEST
};

// Mapping of directions to their opposites
const Direction OPPOSITES[] = {
    (Direction)0,     // Placeholder for index 0
    SOUTH,            // Opposite of NORTH is SOUTH
    NORTH,            // Opposite of SOUTH is NORTH
    (Direction)0,     // Placeholder
    WEST,             // Opposite of EAST is WEST
    (Direction)0,     // Placeholder
    (Direction)0,     // Placeholder
    (Direction)0,     // Placeholder
    EAST              // Opposite of WEST is EAST
};

// Cell class representing a single cell in the maze
class Cell {
private:
    int row;
    int col;
    int links;  // Bit flags for linked directions

public:
    Cell(int row, int col) : row(row), col(col), links(0) {}

    int getRow() const { return row; }
    int getCol() const { return col; }

    // Check if this cell is linked to another cell in the given direction
    bool linked(Direction direction) const {
        return (links & direction) != 0;
    }

    // Link this cell to another cell in the given direction
    void link(Direction direction) {
        links |= direction;
    }

    // Unlink this cell from another cell in the given direction
    void unlink(Direction direction) {
        links &= ~direction;
    }

    // Get all directions where this cell has links
    std::vector<Direction> getLinks() const {
        std::vector<Direction> result;
        if (linked(NORTH)) result.push_back(NORTH);
        if (linked(SOUTH)) result.push_back(SOUTH);
        if (linked(EAST)) result.push_back(EAST);
        if (linked(WEST)) result.push_back(WEST);
        return result;
    }
};

// Grid class representing the entire maze
class Grid {
private:
    int rows;
    int cols;
    std::vector<std::vector<Cell>> cells;
    std::mt19937 rng;

public:
    Grid(int rows, int cols) : rows(rows), cols(cols) {
        // Initialize random number generator
        rng.seed(static_cast<unsigned int>(std::time(nullptr)));
        
        // Initialize cells
        cells.resize(rows);
        for (int r = 0; r < rows; r++) {
            cells[r].reserve(cols);
            for (int c = 0; c < cols; c++) {
                cells[r].emplace_back(r, c);
            }
        }
    }

    int getRows() const { return rows; }
    int getCols() const { return cols; }

    // Check if the given position is within the grid
    bool isValid(int row, int col) const {
        return row >= 0 && row < rows && col >= 0 && col < cols;
    }

    // Get the cell at the given position
    Cell& at(int row, int col) {
        return cells[row][col];
    }

    const Cell& at(int row, int col) const {
        return cells[row][col];
    }

    // Get a random integer between min and max (inclusive)
    int random(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }

    // Link two cells in the grid by their positions and directions
    void linkCells(int row1, int col1, Direction dir) {
        if (!isValid(row1, col1)) return;

        // Calculate the coordinates of the second cell
        int row2 = row1 + DIRECTION_OFFSETS[dir].second;
        int col2 = col1 + DIRECTION_OFFSETS[dir].first;

        if (!isValid(row2, col2)) return;

        // Link the cells in both directions
        at(row1, col1).link(dir);
        at(row2, col2).link(OPPOSITES[dir]);
    }

    // Display the maze
    void display() const {
        // Display the top border
        std::cout << "+";
        for (int c = 0; c < cols; c++) {
            std::cout << "---+";
        }
        std::cout << std::endl;

        for (int r = 0; r < rows; r++) {
            // Display the western boundary and cell contents
            std::cout << "|";
            for (int c = 0; c < cols; c++) {
                std::cout << "   ";
                if (c < cols - 1 && cells[r][c].linked(EAST)) {
                    std::cout << " ";
                } else {
                    std::cout << "|";
                }
            }
            std::cout << std::endl;

            // Display the southern boundary
            std::cout << "+";
            for (int c = 0; c < cols; c++) {
                if (r < rows - 1 && cells[r][c].linked(SOUTH)) {
                    std::cout << "   +";
                } else {
                    std::cout << "---+";
                }
            }
            std::cout << std::endl;
        }
    }
};

// BinaryTree maze generator
class BinaryTreeMaze {
public:
    // Apply the Binary Tree algorithm to generate a maze
    static void on(Grid& grid) {
        for (int r = 0; r < grid.getRows(); r++) {
            for (int c = 0; c < grid.getCols(); c++) {
                std::vector<Direction> neighbors;
                
                // Consider linking north
                if (r > 0) {
                    neighbors.push_back(NORTH);
                }
                
                // Consider linking east
                if (c < grid.getCols() - 1) {
                    neighbors.push_back(EAST);
                }
                
                // If we have neighbors to link, choose one at random
                if (!neighbors.empty()) {
                    int index = grid.random(0, neighbors.size() - 1);
                    Direction direction = neighbors[index];
                    grid.linkCells(r, c, direction);
                }
            }
        }
    }
};

// Tracks the distance of each cell from a starting point
class Distances {
private:
    std::unordered_map<std::string, int> cells;
    Cell* root;
    
    std::string key(int row, int col) const {
        return std::to_string(row) + "," + std::to_string(col);
    }
    
    std::string key(const Cell& cell) const {
        return key(cell.getRow(), cell.getCol());
    }

public:
    Distances(Cell& start) : root(&start) {
        cells[key(start)] = 0;
    }
    
    int getDistance(const Cell& cell) const {
        std::string cellKey = key(cell);
        if (cells.find(cellKey) != cells.end()) {
            return cells.at(cellKey);
        }
        return std::numeric_limits<int>::max();
    }
    
    void setDistance(const Cell& cell, int distance) {
        cells[key(cell)] = distance;
    }
    
    std::vector<Cell*> getCells(Grid& grid) const {
        std::vector<Cell*> result;
        for (const auto& pair : cells) {
            std::string cellKey = pair.first;
            size_t commaPos = cellKey.find(',');
            if (commaPos != std::string::npos) {
                int row = std::stoi(cellKey.substr(0, commaPos));
                int col = std::stoi(cellKey.substr(commaPos + 1));
                if (grid.isValid(row, col)) {
                    result.push_back(&grid.at(row, col));
                }
            }
        }
        return result;
    }
    
    Cell* getMaxCell(Grid& grid) const {
        Cell* maxCell = root;
        int maxDistance = 0;
        
        for (const auto& pair : cells) {
            if (pair.second > maxDistance) {
                std::string cellKey = pair.first;
                size_t commaPos = cellKey.find(',');
                if (commaPos != std::string::npos) {
                    int row = std::stoi(cellKey.substr(0, commaPos));
                    int col = std::stoi(cellKey.substr(commaPos + 1));
                    if (grid.isValid(row, col)) {
                        maxCell = &grid.at(row, col);
                        maxDistance = pair.second;
                    }
                }
            }
        }
        
        return maxCell;
    }
    
    int getMaxDistance() const {
        int maxDistance = 0;
        for (const auto& pair : cells) {
            maxDistance = std::max(maxDistance, pair.second);
        }
        return maxDistance;
    }
};

// Implements Dijkstra's algorithm
class Dijkstra {
public:
    static Distances calculateDistances(Grid& grid, Cell& start) {
        Distances distances(start);
        
        std::priority_queue<
            std::pair<int, std::string>,
            std::vector<std::pair<int, std::string>>,
            std::greater<std::pair<int, std::string>>
        > frontier;
        
        auto key = [](const Cell& cell) {
            return std::to_string(cell.getRow()) + "," + std::to_string(cell.getCol());
        };
        
        frontier.push(std::make_pair(0, key(start)));
        
        while (!frontier.empty()) {
            auto current = frontier.top();
            frontier.pop();
            
            std::string cellKey = current.second;
            size_t commaPos = cellKey.find(',');
            if (commaPos == std::string::npos) continue;
            
            int row = std::stoi(cellKey.substr(0, commaPos));
            int col = std::stoi(cellKey.substr(commaPos + 1));
            
            if (!grid.isValid(row, col)) continue;
            
            Cell& cell = grid.at(row, col);
            int cellDistance = distances.getDistance(cell);
            
            std::vector<Direction> links = cell.getLinks();
            for (Direction dir : links) {
                int neighborRow = row + DIRECTION_OFFSETS[dir].second;
                int neighborCol = col + DIRECTION_OFFSETS[dir].first;
                
                if (!grid.isValid(neighborRow, neighborCol)) continue;
                
                Cell& neighbor = grid.at(neighborRow, neighborCol);
                
                int newDistance = cellDistance + 1;
                int neighborDistance = distances.getDistance(neighbor);
                
                if (newDistance < neighborDistance) {
                    distances.setDistance(neighbor, newDistance);
                    frontier.push(std::make_pair(newDistance, key(neighbor)));
                }
            }
        }
        
        return distances;
    }
    
    static std::vector<Cell*> shortestPath(Grid& grid, Cell& start, Cell& end) {
        Distances distances = calculateDistances(grid, start);
        
        std::vector<Cell*> path;
        Cell* current = &end;
        path.push_back(current);
        
        if (distances.getDistance(end) == std::numeric_limits<int>::max()) {
            return std::vector<Cell*>();
        }
        
        while (current != &start) {
            int row = current->getRow();
            int col = current->getCol();
            int currentDistance = distances.getDistance(*current);
            
            Cell* nextCell = nullptr;
            int nextDistance = currentDistance;
            
            std::vector<Direction> links = current->getLinks();
            for (Direction dir : links) {
                int neighborRow = row + DIRECTION_OFFSETS[dir].second;
                int neighborCol = col + DIRECTION_OFFSETS[dir].first;
                
                if (!grid.isValid(neighborRow, neighborCol)) continue;
                
                Cell& neighbor = grid.at(neighborRow, neighborCol);
                int neighborDistance = distances.getDistance(neighbor);
                
                if (neighborDistance < nextDistance) {
                    nextCell = &neighbor;
                    nextDistance = neighborDistance;
                }
            }
            
            if (nextCell == nullptr) break;
            
            path.push_back(nextCell);
            current = nextCell;
        }
        
        std::reverse(path.begin(), path.end());
        return path;
    }
    
    static std::vector<Cell*> longestPath(Grid& grid) {
        Cell& start = grid.at(0, 0);
        
        Distances distances = calculateDistances(grid, start);
        Cell* farthest = distances.getMaxCell(grid);
        
        distances = calculateDistances(grid, *farthest);
        Cell* end = distances.getMaxCell(grid);
        
        return shortestPath(grid, *farthest, *end);
    }
};

// Display maze with the path highlighted
void displayWithPath(const Grid& grid, const std::vector<Cell*>& path) {
    auto isOnPath = [&path](const Cell* cell) {
        return std::find(path.begin(), path.end(), cell) != path.end();
    };
    
    std::cout << "+";
    for (int c = 0; c < grid.getCols(); c++) {
        std::cout << "---+";
    }
    std::cout << std::endl;
    
    for (int r = 0; r < grid.getRows(); r++) {
        std::cout << "|";
        for (int c = 0; c < grid.getCols(); c++) {
            if (isOnPath(&grid.at(r, c))) {
                std::cout << " X ";
            } else {
                std::cout << "   ";
            }
            
            if (c < grid.getCols() - 1 && grid.at(r, c).linked(EAST)) {
                std::cout << " ";
            } else {
                std::cout << "|";
            }
        }
        std::cout << std::endl;
        
        std::cout << "+";
        for (int c = 0; c < grid.getCols(); c++) {
            if (r < grid.getRows() - 1 && grid.at(r, c).linked(SOUTH)) {
                std::cout << "   +";
            } else {
                std::cout << "---+";
            }
        }
        std::cout << std::endl;
    }
}

void print_help(const char* program_name) {
    cout << "MazeBuilder - A maze generation tool using the Binary Tree algorithm\n\n";
    cout << "Usage: " << program_name << " [OPTIONS] [rows] [columns]\n\n";
    cout << "Arguments:\n";
    cout << "  rows          Number of rows in the maze (default: 10)\n";
    cout << "  columns       Number of columns in the maze (default: 10)\n\n";
    cout << "Options:\n";
    cout << "  -h, --help    Show this help message and exit\n\n";
    cout << "Examples:\n";
    cout << "  " << program_name << "                    Generate and solve a 10x10 maze\n";
    cout << "  " << program_name << " 20                 Generate and solve a 20x20 maze\n";
    cout << "  " << program_name << " 15 25              Generate and solve a 15x25 maze\n";
    cout << "  " << program_name << " --help             Show this help message\n\n";
    cout << "Algorithms:\n";
    cout << "  Generation: Binary Tree (Creates a perfect maze with exactly one path between any two points).\n";
    cout << "  Pathfinding: Dijkstra's Algorithm (Finds the longest shortest path through the maze).\n";
}

int main(int argc, char* argv[]) {
    int rows = 10;
    int cols = 10;
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_help(argv[0]);
            return 0;
        }
    }
    
    // Parse positional command line arguments
    if (argc > 1 && argv[1][0] != '-') {
        rows = std::atoi(argv[1]);
    }
    if (argc > 2 && argv[2][0] != '-') {
        cols = std::atoi(argv[2]);
    }
    
    // Create grid and generate maze
    Grid grid(rows, cols);
    BinaryTreeMaze::on(grid);
    
    // Display the original maze
    std::cout << "Generated Maze:" << std::endl;
    grid.display();
    std::cout << std::endl;
    
    // Find the longest path through the maze
    std::vector<Cell*> solution = Dijkstra::longestPath(grid);
    
    // Display maze with the solution path
    std::cout << "Maze Solution:" << std::endl;
    displayWithPath(grid, solution);
    
    // Show some statistics
    std::cout << std::endl;
    std::cout << "Solution path length: " << solution.size() << " cells" << std::endl;
    std::cout << "Solution path steps: " << solution.size() - 1 << " steps" << std::endl;
    
    return 0;
}