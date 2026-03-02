#include <iostream>
#include <string>
#include <cstdlib> // Needed for rand() and srand()
#include <ctime>   // Needed for time()

using namespace std;

// --- Function Prototypes ---
void showHeader();
int rollDice();
void playRound(int &tokens); // We use & (reference) to update the actual token variable
int getValidBet(int tokens);

int main() {
    // Seed the random number generator so dice rolls are different every time
    srand(static_cast<unsigned int>(time(0)));

    int tokens = 100; // Starting bankroll
    char playChoice;

    showHeader();
    cout << "You enter the Neon Vault with " << tokens << " tokens." << endl;

    // The Main Game Loop
    while (tokens > 0) {
        cout << "\n--- New Round ---" << endl;
        playRound(tokens);

        if (tokens <= 0) {
            cout << "\n[!] You are out of tokens! The bouncers escort you out." << endl;
            break;
        }

        cout << "\nYou have " << tokens << " tokens. Keep playing? (y/n): ";
        cin >> playChoice;

        if (playChoice == 'n' || playChoice == 'N') {
            break;
        }
    }

    cout << "\nFinal Score: " << tokens << " tokens." << endl;
    cout << "Thanks for playing Neon Dice 21!" << endl;

    return 0;
}

// --- Function Definitions ---

void showHeader() {
    cout << "========================================" << endl;
    cout << "           NEON DICE 21                 " << endl;
    cout << "   (Blackjack rules, Craps dice!)       " << endl;
    cout << "========================================" << endl;
}

int rollDice() {
    // rand() % 6 gives 0-5, so we add 1 to get 1-6
    int die1 = (rand() % 6) + 1;
    int die2 = (rand() % 6) + 1;
    return die1 + die2;
}

int getValidBet(int tokens) {
    int bet;
    while (true) {
        cout << "Enter your bet (Available: " << tokens << "): ";
        cin >> bet;

        if (bet > 0 && bet <= tokens) {
            return bet;
        }
        cout << "Invalid bet! Please bet between 1 and " << tokens << "." << endl;
    }
}

void playRound(int &tokens) {
    int bet = getValidBet(tokens);
    int playerTotal = rollDice();
    int dealerTotal = rollDice();

    cout << "\nYou rolled a " << playerTotal << "." << endl;
    cout << "Dealer is showing a " << dealerTotal << "." << endl;

    // Player's Turn Loop
    bool playerStanding = false;
    while (playerTotal < 21 && !playerStanding) {
        char action;
        cout << "Your Total: " << playerTotal << ". [R]oll again or [S]tand? ";
        cin >> action;

        if (action == 'r' || action == 'R') {
            int roll = rollDice();
            playerTotal += roll;
            cout << "You rolled a " << roll << ". New total: " << playerTotal << endl;
        } else {
            playerStanding = true;
        }
    }

    // Logic to determine winner
    if (playerTotal > 21) {
        cout << "BUST! You went over 21." << endl;
        tokens -= bet;
    } else {
        // Dealer's Turn (Simple AI: Dealer hits if under 17)
        cout << "\nDealer's turn..." << endl;
        while (dealerTotal < 17) {
            int dRoll = rollDice();
            dealerTotal += dRoll;
            cout << "Dealer rolls a " << dRoll << ". Dealer total: " << dealerTotal << endl;
        }

        if (dealerTotal > 21 || playerTotal > dealerTotal) {
            cout << "YOU WIN! You gained " << bet << " tokens." << endl;
            tokens += bet;
        } else if (playerTotal == dealerTotal) {
            cout << "PUSH! (Tie). Your bet is returned." << endl;
        } else {
            cout << "HOUSE WINS! You lost " << bet << " tokens." << endl;
            tokens -= bet;
        }
    }
}