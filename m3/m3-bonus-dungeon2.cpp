#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void displayStatus(int health, int weapon);
void chooseWeapon(int &weapon);
void roomOne(int &health, int weapon);
void roomTwo(int &health, int weapon);       // CHANGED
void roomThree(int &health, int weapon);     // CHANGED
void calculateScore(int health, int weapon, int &score);  // NEW

int main() {
    srand(time(0));

    int health = 100;
    int weapon = 0;
    int score = 0;   // NEW

    cout << "=== DUNGEON ESCAPE ===\n\n";
    cout << "You wake up in a dark dungeon. Three doors stand between you and freedom.\n\n";

    chooseWeapon(weapon);

    roomOne(health, weapon);
    if (health <= 0) { cout << "\nYou died. Better luck next run.\n"; return 0; }

    roomTwo(health, weapon);
    if (health <= 0) { cout << "\nYou died. Better luck next run.\n"; return 0; }

    roomThree(health, weapon);
    if (health <= 0) { cout << "\nYou died. Better luck next run.\n"; return 0; }

    calculateScore(health, weapon, score);   // NEW
    cout << "\n*** You escaped! Final HP: " << health << " | Score: " << score << " ***\n";
    return 0;
}

// ── unchanged from Stage 1 ───────────────────────────────────────────────────
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
    int roll = rand() % 6 + 1;

    switch (choice) {
        case 1:
            if (roll >= 3) { cout << "You slash through the rats. (-15 HP)\n"; health -= 15; }
            else           { cout << "They overwhelm you. (-30 HP)\n"; health -= 30; }
            break;
        case 2:
            if (roll >= 4) { cout << "You slip past quietly.\n"; }
            else           { cout << "A rat alerts the pack. (-20 HP)\n"; health -= 20; }
            break;
        case 3:
            if (weapon == 2)      { cout << "Clean shots. Easy passage. (-5 HP)\n"; health -= 5; }
            else if (weapon == 3) { cout << "Rats scatter in the flash. No damage.\n"; }
            else                  { cout << "Hesitation costs you. (-20 HP)\n"; health -= 20; }
            break;
        default:
            cout << "You freeze. The rats swarm you. (-25 HP)\n"; health -= 25;
    }
}

// ── CHANGED: roomTwo now includes a potion event ─────────────────────────────
void roomTwo(int &health, int weapon) {
    cout << "\n── ROOM 2: The Armory ──\n";
    displayStatus(health, weapon);

    // NEW: 50/50 chance a potion appears before the main choice
    if (rand() % 2 == 0) {
        cout << "You notice a glowing potion on a shelf. Take it? (1 = yes, 2 = no): ";
        int potionChoice;
        cin >> potionChoice;
        if (potionChoice == 1) {
            int heal = rand() % 21 + 10;   // heals 10–30 HP
            health += heal;
            if (health > 100) health = 100; // cap at 100
            cout << "You drink it. +" << heal << " HP restored.\n";
        }
    }

    cout << "A guard is asleep at a desk. A key ring hangs on the far wall.\n";
    cout << "  1. Sneak past and grab the keys\n";
    cout << "  2. Attack the guard directly\n";
    if (weapon == 1) cout << "  3. [SWORD] Disarm and restrain the guard quietly\n";
    if (weapon == 3) cout << "  3. [MAGIC] Cast a sleep spell to keep him under\n";

    int choice;
    cin >> choice;
    int roll = rand() % 6 + 1;

    switch (choice) {
        case 1:
            if (roll >= 3) { cout << "Keys in hand, you're through. No damage.\n"; }
            else           { cout << "Floorboard creaks. He swings. (-25 HP)\n"; health -= 25; }
            break;
        case 2:
            cout << "You win, but not cleanly. (-30 HP)\n"; health -= 30;
            break;
        case 3:
            if (weapon == 1)      { cout << "Blade to his throat. He hands over the keys.\n"; }
            else if (weapon == 3) { cout << "Deep sleep locked in. Keys grabbed easily.\n"; }
            else                  { cout << "Invalid — guard wakes. (-20 HP)\n"; health -= 20; }
            break;
        default:
            cout << "You hesitate too long. (-25 HP)\n"; health -= 25;
    }
}

// ── CHANGED: roomThree is now a multi-round boss fight ───────────────────────
void roomThree(int &health, int weapon) {
    cout << "\n── ROOM 3: The Troll Gate ──\n";
    displayStatus(health, weapon);

    // Weapon option up front, before the fight
    cout << "A troll guards the exit.\n";
    cout << "  1. Fight it directly\n";
    cout << "  2. Look for another way around\n";
    if (weapon == 2) cout << "  3. [BOW] Aim for its eye from the shadows\n";
    if (weapon == 3) cout << "  3. [MAGIC] Collapse the ceiling above it\n";

    int choice;
    cin >> choice;

    // Instant-resolve options (2, 3) — same as Stage 1
    if (choice == 2) {
        if (rand() % 6 + 1 >= 5) {
            cout << "You find a drainage tunnel. You make it out unharmed!\n";
        } else {
            cout << "No other way. You have to fight. (-30 HP)\n";
            health -= 30;
        }
        return;   // skip the fight loop entirely
    }

    if (choice == 3) {
        if (weapon == 2)      { cout << "Arrow through the eye. Troll down. (-0 HP)\n"; }
        else if (weapon == 3) { cout << "Ceiling caves. Troll buried. You sprint through.\n"; }
        else                  { cout << "Invalid — troll heard you. (-30 HP)\n"; health -= 30; }
        return;   // skip the fight loop
    }

    // NEW: multi-round fight loop (triggers on choice 1, or any invalid input)
    cout << "\nYou charge at the troll!\n";
    int trollHP = 60;
    int round = 1;

    while (health > 0 && trollHP > 0) {
        cout << "\n-- Round " << round << " --\n";
        cout << "   Your HP: " << health << " | Troll HP: " << trollHP << "\n";

        // Player attacks — sword hits harder, bow is consistent, magic varies wildly
        int playerDamage;
        if (weapon == 1)      playerDamage = rand() % 11 + 10;  // 10–20
        else if (weapon == 2) playerDamage = rand() % 6  + 12;  // 12–17
        else                  playerDamage = rand() % 21 + 5;   // 5–25 (high risk/reward)

        trollHP -= playerDamage;
        cout << "   You hit the troll for " << playerDamage << " damage.\n";

        if (trollHP <= 0) break;   // troll dead — exit loop before it attacks back

        // Troll attacks
        int trollDamage = rand() % 16 + 10;   // 10–25
        health -= trollDamage;
        cout << "   The troll smashes you for " << trollDamage << " damage.\n";

        round++;
    }

    if (health > 0) {
        cout << "\nThe troll collapses! You limp through the gate.\n";
    }
    // health <= 0 is handled back in main
}

// ── NEW: score function ───────────────────────────────────────────────────────
void calculateScore(int health, int weapon, int &score) {
    score = health * 10;           // base: 10 points per HP remaining

    if (weapon == 3) score += 200; // magic bonus — hardest path
    if (weapon == 2) score += 100; // bow bonus — moderate difficulty

    cout << "\n── SCORE BREAKDOWN ──\n";
    cout << "   HP remaining: " << health << " x10 = " << health * 10 << " pts\n";
    if (weapon == 3) cout << "   Magic user bonus: +200\n";
    if (weapon == 2) cout << "   Bow user bonus: +100\n";
    cout << "   Total: " << score << " pts\n";
}