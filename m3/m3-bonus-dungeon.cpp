#include <iostream>
#include <cstdlib>   // for rand() and srand()
#include <ctime>     // for time(), used to seed randomness

using namespace std;

// ── FUNCTION DECLARATIONS (prototypes) ──────────────────────────────────────
void displayStatus(int health, int weapon);
void chooseWeapon(int &weapon);
void roomOne(int &health, int weapon);
void roomTwo(int &health, int weapon);
void roomThree(int &health, int weapon);
// ────────────────────────────────────────────────────────────────────────────

int main() {
    srand(time(0));   // seed the random number generator once, at startup

    int health = 100;
    int weapon = 0;   // 1 = sword, 2 = bow, 3 = magic

    cout << "=== DUNGEON ESCAPE ===\n\n";
    cout << "You wake up in a dark dungeon. Three doors stand between you and freedom.\n\n";

    chooseWeapon(weapon);

    roomOne(health, weapon);
    if (health <= 0) {
        cout << "\nYou died. Better luck next run.\n";
        return 0;
    }

    roomTwo(health, weapon);
    if (health <= 0) {
        cout << "\nYou died. Better luck next run.\n";
        return 0;
    }

    roomThree(health, weapon);
    if (health <= 0) {
        cout << "\nYou died. Better luck next run.\n";
        return 0;
    }

    cout << "\n*** You escaped the dungeon! Final health: " << health << " ***\n";
    return 0;
}

// ── FUNCTION DEFINITIONS ─────────────────────────────────────────────────────

void displayStatus(int health, int weapon) {
    string weaponName = "Unknown";
    if (weapon == 1) weaponName = "Sword";
    else if (weapon == 2) weaponName = "Bow";
    else if (weapon == 3) weaponName = "Magic";

    cout << "\n[ HP: " << health << " | Weapon: " << weaponName << " ]\n";
}

void chooseWeapon(int &weapon) {
    cout << "Choose your weapon:\n";
    cout << "  1. Sword  (close combat, reliable)\n";
    cout << "  2. Bow    (ranged, good against fast enemies)\n";
    cout << "  3. Magic  (unpredictable but powerful)\n";
    cout << "Enter 1, 2, or 3: ";

    cin >> weapon;

    // Input safety: keep asking if they enter something invalid
    while (weapon < 1 || weapon > 3) {
        cout << "Please enter 1, 2, or 3: ";
        cin >> weapon;
    }

    switch (weapon) {
        case 1: cout << "You grab a battered sword off the wall.\n"; break;
        case 2: cout << "You find a shortbow with a few arrows.\n"; break;
        case 3: cout << "You feel magic pulse through your hands.\n"; break;
    }
}

void roomOne(int &health, int weapon) {
    cout << "\n── ROOM 1: The Rat Den ──\n";
    displayStatus(health, weapon);
    cout << "A pack of giant rats blocks the path. What do you do?\n";
    cout << "  1. Fight them directly\n";
    cout << "  2. Try to sneak past\n";
    if (weapon == 2) cout << "  3. [BOW] Pick them off from a distance\n";
    if (weapon == 3) cout << "  3. [MAGIC] Cast a flash of light to scatter them\n";

    int choice;
    cin >> choice;

    // Random event: a die roll (1–6) used to vary outcomes
    int roll = rand() % 6 + 1;

    switch (choice) {
        case 1:
            if (roll >= 3) {
                cout << "You slash through the rats! A few bites, but you push through. (-15 HP)\n";
                health -= 15;
            } else {
                cout << "The rats overwhelm you before you get your footing. (-30 HP)\n";
                health -= 30;
            }
            break;
        case 2:
            if (roll >= 4) {
                cout << "You slip past quietly. No damage taken.\n";
            } else {
                cout << "A rat spots you and alerts the pack. You run, but not unscathed. (-20 HP)\n";
                health -= 20;
            }
            break;
        case 3:
            if (weapon == 2) {
                cout << "You drop three rats before they reach you. Clean escape. (-5 HP)\n";
                health -= 5;
            } else if (weapon == 3) {
                cout << "The flash sends rats scattering in every direction. You walk through freely.\n";
            } else {
                cout << "Invalid choice. The hesitation costs you. (-20 HP)\n";
                health -= 20;
            }
            break;
        default:
            cout << "You freeze up. The rats swarm you. (-25 HP)\n";
            health -= 25;
    }
}

void roomTwo(int &health, int weapon) {
    cout << "\n── ROOM 2: The Armory ──\n";
    displayStatus(health, weapon);
    cout << "A guard is asleep at a desk. A key ring hangs on the far wall. What do you do?\n";
    cout << "  1. Sneak past and grab the keys\n";
    cout << "  2. Attack the guard directly\n";
    if (weapon == 1) cout << "  3. [SWORD] Disarm and restrain the guard quietly\n";
    if (weapon == 3) cout << "  3. [MAGIC] Cast a sleep spell to keep him under\n";

    int choice;
    cin >> choice;

    int roll = rand() % 6 + 1;

    switch (choice) {
        case 1:
            if (roll >= 3) {
                cout << "You creep across the room. Keys in hand, you're through. No damage.\n";
            } else {
                cout << "A floorboard creaks. The guard wakes and swings — you dodge, barely. (-25 HP)\n";
                health -= 25;
            }
            break;
        case 2:
            cout << "The guard is bigger than expected. You win, but not cleanly. (-30 HP)\n";
            health -= 30;
            break;
        case 3:
            if (weapon == 1) {
                cout << "You press the blade flat against his throat. He hands over the keys, trembling. (-0 HP)\n";
            } else if (weapon == 3) {
                cout << "You deepen his sleep. He won't wake for hours. You grab the keys easily.\n";
            } else {
                cout << "Invalid choice — hesitation wakes the guard. (-20 HP)\n";
                health -= 20;
            }
            break;
        default:
            cout << "You stand there too long. The guard wakes. (-25 HP)\n";
            health -= 25;
    }
}

void roomThree(int &health, int weapon) {
    cout << "\n── ROOM 3: The Final Gate ──\n";
    displayStatus(health, weapon);
    cout << "A troll guards the exit. It hasn't seen you yet.\n";
    cout << "  1. Rush it head-on\n";
    cout << "  2. Look for another way around\n";
    if (weapon == 2) cout << "  3. [BOW] Aim for its eye from the shadows\n";
    if (weapon == 3) cout << "  3. [MAGIC] Collapse the ceiling above it\n";

    int choice;
    cin >> choice;

    int roll = rand() % 6 + 1;

    switch (choice) {
        case 1:
            if (roll >= 4) {
                cout << "Pure aggression works! The troll stumbles and you bolt through. (-35 HP)\n";
                health -= 35;
            } else {
                cout << "The troll clubs you into a wall. You crawl through, barely. (-50 HP)\n";
                health -= 50;
            }
            break;
        case 2:
            if (roll >= 5) {
                cout << "You find a drainage tunnel. Tight fit, but you make it out. No damage!\n";
            } else {
                cout << "No other way. You have to go through it. (-30 HP)\n";
                health -= 30;
            }
            break;
        case 3:
            if (weapon == 2) {
                cout << "Arrow through the eye. The troll crashes down. You walk through calmly. (-0 HP)\n";
            } else if (weapon == 3) {
                cout << "The ceiling caves. The troll is buried. You sprint through the dust.\n";
            } else {
                cout << "Invalid choice — the troll heard you. (-30 HP)\n";
                health -= 30;
            }
            break;
        default:
            cout << "Indecision. The troll spots you first. (-40 HP)\n";
            health -= 40;
    }
}