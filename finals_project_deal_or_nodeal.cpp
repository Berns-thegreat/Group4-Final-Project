#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

const int NUM_CASES = 20;
const int NUM_ROUNDS = 5;
const int roundOpenCount[NUM_ROUNDS] = {5, 5, 3, 3, 2};

// Structure to hold case info
struct Briefcase {
    int amount;
    bool isOpened;
};

// Function to shuffle array
void shuffleCases(Briefcase cases[]) {
    srand(time(0));
    for (int i = NUM_CASES - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(cases[i], cases[j]);
    }
}

// Function to calculate average of unopened amounts
double calculateOffer(Briefcase cases[]) {
    double total = 0;
    int count = 0;
    for (int i = 0; i < NUM_CASES; i++) {
        if (!cases[i].isOpened) {
            total += cases[i].amount;
            count++;
        }
    }
    return (count > 0) ? total / count : 0;
}

// Display unopened briefcases
void showBriefcases(Briefcase cases[]) {
    cout << "Remaining Briefcases: ";
    for (int i = 0; i < NUM_CASES; i++) {
        if (!cases[i].isOpened) {
            cout << "[" << (i + 1) << "] ";
        }
    }
    cout << "\n";
}

// Function to print all amounts left
void showAmountsLeft(Briefcase cases[]) {
    cout << "Remaining Amounts: ";
    for (int i = 0; i < NUM_CASES; i++) {
        if (!cases[i].isOpened) {
            cout << "₱" << cases[i].amount << " ";
        }
    }
    cout << "\n";
}

int main() {
    Briefcase cases[NUM_CASES] = {
        {10,false}, {50,false}, {250,false}, {500,false}, {750,false},
        {1000,false}, {2500,false}, {5000,false}, {7500,false}, {10000,false},
        {15000,false}, {25000,false}, {50000,false}, {75000,false}, {100000,false},
        {150000,false}, {250000,false}, {500000,false}, {750000,false}, {1000000,false}
    };

    shuffleCases(cases);

    cout << "=== DEAL OR NO DEAL ===\n\n";
    showBriefcases(cases);

    int playerChoice;
    cout << "Pick your briefcase (1-20): ";
    cin >> playerChoice;
    playerChoice--;
    cases[playerChoice].isOpened = true;

    for (int round = 0; round < NUM_ROUNDS; round++) {
        cout << "\n--- ROUND " << (round + 1) << " ---\n";

        int toOpen = roundOpenCount[round];
        while (toOpen > 0) {
            showBriefcases(cases);
            int pick;
            cout << "Pick a briefcase to open: ";
            cin >> pick;
            pick--;

            if (pick < 0 || pick >= NUM_CASES || cases[pick].isOpened) {
                cout << "Invalid or already opened! Try again.\n";
                continue;
            }

            cases[pick].isOpened = true;
            cout << "You opened briefcase #" << (pick + 1) << " with ₱" << cases[pick].amount << "\n";
            toOpen--;
        }

        showAmountsLeft(cases);
        double offer = calculateOffer(cases);
        cout << "\n💼 BANKER OFFER: ₱" << (int)offer << "\n";
        string decision;
        cout << "Deal or No Deal? (deal/no): ";
        cin >> decision;

        if (decision == "deal") {
            cout << "\nYou accepted the deal of ₱" << (int)offer << ".\n";
            cout << "Your original case had ₱" << cases[playerChoice].amount << "\n";
            cout << "Thanks for playing Deal or No Deal!\n";
            return 0;
        }
    }

    // Final two briefcases left
    int lastCase = -1;
    for (int i = 0; i < NUM_CASES; i++) {
        if (!cases[i].isOpened && i != playerChoice) {
            lastCase = i;
            break;
        }
    }

    cout << "\nOnly two cases left:\n";
    cout << "1. Your case #" << (playerChoice + 1) << "\n";
    cout << "2. Remaining case #" << (lastCase + 1) << "\n";
    string finalChoice;
    cout << "Do you want to switch? (yes/no): ";
    cin >> finalChoice;

    int finalAmount = (finalChoice == "yes") ? cases[lastCase].amount : cases[playerChoice].amount;

    cout << "\n🎉 You won ₱" << finalAmount << "! 🎉\n";
    cout << "Thanks for playing Deal or No Deal!\n";

    return 0;
}