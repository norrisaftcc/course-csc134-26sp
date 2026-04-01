#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

// --- CONSTANTS ---
const int MAP_HEIGHT = 15;
const int MAP_WIDTH = 30;
const char WALL = '#';
const char FLOOR = '.';
const char PLAYER = '@';
const char MONSTER = 'M';

// --- DATA STRUCTURES ---
struct Entity {
    int x, y;
    int hp;
    int attack;
    char symbol;
    bool alive;
};

// --- GLOBAL GAME STATE ---
char dungeonMap[MAP_HEIGHT][MAP_WIDTH];
Entity player = {1, 1, 100, 10, PLAYER, true};
Entity enemy = {10, 5, 30, 5, MONSTER, true};
bool gameRunning = true;

// --- UTILITY FUNCTIONS ---

// Simple cross-platform screen clear (emulated with newlines for standard C++)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Simple delay function for "cutscenes"
void sleepMs(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

// --- GAME PHASES ---

void playIntro() {
    clearScreen();
    cout << "========================================" << endl;
    cout << "          ECHOES OF THE GRID           " << endl;
    cout << "========================================" << endl;
    sleepMs(500);
    cout << "\n       Initializing Matrix..." << endl;
    sleepMs(800);
    cout << "       Loading Entities..." << endl;
    sleepMs(800);
    cout << "\n   Press ENTER to enter the dungeon..." << endl;
    cin.get(); 
}

void initMap() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (i == 0 || i == MAP_HEIGHT - 1 || j == 0 || j == MAP_WIDTH - 1) {
                dungeonMap[i][j] = WALL;
            } else {
                dungeonMap[i][j] = FLOOR;
            }
        }
    }
}

void draw() {
    clearScreen();
    // Render the map and entities
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (player.x == j && player.y == i) {
                cout << player.symbol;
            } else if (enemy.alive && enemy.x == j && enemy.y == i) {
                cout << enemy.symbol;
            } else {
                cout << dungeonMap[i][j];
            }
        }
        cout << endl;
    }

    // Status UI
    cout << "\n[HP: " << player.hp << "] | [Player: (" << player.x << "," << player.y << ")]" << endl;
    if (enemy.alive) {
        cout << "[Enemy HP: " << enemy.hp << "]" << endl;
    } else {
        cout << "[Enemy Defeated!]" << endl;
    }
    cout << "Controls: W (Up), A (Left), S (Down), D (Right), Q (Quit)" << endl;
    cout << "Enter move: ";
}

void handleInput() {
    char input;
    cin >> input;
    input = tolower(input);

    int nextX = player.x;
    int nextY = player.y;

    if (input == 'w') nextY--;
    else if (input == 's') nextY++;
    else if (input == 'a') nextX--;
    else if (input == 'd') nextX++;
    else if (input == 'q') {
        gameRunning = false;
        return;
    }

    // Collision Detection: Wall
    if (dungeonMap[nextY][nextX] == WALL) {
        return; // Don't move
    }

    // Collision Detection: Enemy (Combat)
    if (enemy.alive && nextX == enemy.x && nextY == enemy.y) {
        enemy.hp -= player.attack;
        if (enemy.hp <= 0) enemy.alive = false;
        
        // Simple counter-attack
        if (enemy.alive) {
            player.hp -= enemy.attack;
        }
        return; // Don't move into the enemy's space
    }

    // Update position
    player.x = nextX;
    player.y = nextY;
}

int main() {
    playIntro();
    initMap();

    while (gameRunning && player.hp > 0) {
        draw();
        handleInput();

        if (player.hp <= 0) {
            clearScreen();
            cout << "YOU HAVE BEEN DEFEATED." << endl;
            sleepMs(2000);
        }
    }

    clearScreen();
    cout << "Thanks for playing Echoes of the Grid!" << endl;
    return 0;
}