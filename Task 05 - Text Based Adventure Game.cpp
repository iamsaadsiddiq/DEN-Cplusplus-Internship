#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

void displayTitle() {
    cout << "======================================================================" << endl;
    cout << "                       WELCOME TO ADVENTURE GAME                              " << endl;
    cout << "======================================================================" << endl;
}

// Function to display the main menu
void displayMenu() {
    displayTitle();
    cout << "1. Start Game" << endl;
    cout << "2. Instructions" << endl;
    cout << "3. Quit" << endl;
    cout << "======================================================================" << endl;
    cout << "Enter your choice: ";
}

// Function to display instructions
void displayInstructions() {
    cout << "\nWelcome to GAME!" << endl;
    cout << "Navigate through the game by making decisions." << endl;
    cout << "Your choices affect the storyline and can lead to various outcomes." << endl;
    cout << "Enter the number corresponding to your choice." << endl;
    cout << "Prepare for an epic journey filled with adventure and mystery!\n" << endl;
}

// Function to validate user input
int getValidChoice(int min, int max) {
    int choice;
    while (true) {
        cin >> choice;
        if (cin.fail() || choice < min || choice > max) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice. Please enter a number between " << min << " and " << max << ": ";
        }
        else {
            cin.ignore(1000, '\n');
            return choice;
        }
    }
}

// Function to display ASCII characters for character selection
void displayCharacterSelection() {
    cout << "Choose your character:\n" << endl;
    cout << "1. Warrior" << endl;
    cout << R"(
       O
      /|\
      / \
    )" << endl;
    cout << "2. Mage" << endl;
    cout << R"(
       *
      /|\
      / \
    )" << endl;
    cout << "3. Archer" << endl;
    cout << R"(
      ---->
       /|\
      / \
    )" << endl;
    cout << "======================================================================" << endl;
    cout << "Enter your choice (1-3): ";
}

// Function for the forest scenario
void scenarioForest() {
    cout << R"(
         _______
       _/       \_
      / |       | \
     /  |       |  \
     \  |_______|  /
      \___________/
    )" << endl;
    cout << "You find yourself in a dense forest. The trees are towering above you, and the light is dim." << endl;
    cout << "You hear rustling nearby and feel an ominous presence. What do you do?" << endl;
    cout << "1. Investigate the sound" << endl;
    cout << "2. Run away quickly" << endl;
    cout << "3. Hide behind a tree" << endl;
    int choice = getValidChoice(1, 3);

    switch (choice) {
    case 1:
        cout << "\nYou cautiously approach the source of the sound." << endl;
        cout << "A wild beast appears! Prepare for battle!\n" << endl;
        // Additional scenario logic for battling the beast
        break;
    case 2:
        cout << "\nYou sprint away from the sound, not looking back." << endl;
        cout << "You stumble upon a hidden cave.\n" << endl;
        // Additional scenario logic for the cave
        break;
    case 3:
        cout << "\nYou hide behind a tree, holding your breath." << endl;
        cout << "The sound gets closer... but then moves away.\n" << endl;
        // Additional scenario logic for avoiding the danger
        break;
    }
}

// Function for the village scenario
void scenarioVillage() {
    cout << R"(
       ________
     /          \
    |            |
    |  ________  |
    | |        | |
    | |  VILLAGE| |
    |_|________|_|
    )" << endl;
    cout << "You arrive at a village with a marketplace bustling with activity." << endl;
    cout << "There are merchants selling goods and townsfolk going about their daily lives." << endl;
    cout << "You notice three places you could go." << endl;
    cout << "1. Visit the tavern" << endl;
    cout << "2. Explore the blacksmith" << endl;
    cout << "3. Talk to the village elder" << endl;
    int choice = getValidChoice(1, 3);

    switch (choice) {
    case 1:
        cout << "\nYou enter the tavern. It's crowded with people enjoying their drinks." << endl;
        cout << "You overhear some adventurers talking about a treasure hidden in the forest.\n" << endl;
        // Additional scenario logic for treasure hunting
        break;
    case 2:
        cout << "\nThe blacksmith is hard at work, forging a sword." << endl;
        cout << "He offers to sell you a weapon or repair your armor.\n" << endl;
        // Additional scenario logic for buying or repairing equipment
        break;
    case 3:
        cout << "\nThe village elder sits in a chair outside a small cottage." << endl;
        cout << "He speaks of an ancient prophecy and the dangers that lie ahead.\n" << endl;
        // Additional scenario logic for learning about the prophecy
        break;
    }
}

// Main game loop
void startGame() {
    bool playing = true;
    while (playing) {
        displayCharacterSelection();
        int characterChoice = getValidChoice(1, 3);
        cout << "You have selected ";
        switch (characterChoice) {
        case 1: cout << "Warrior!\n"; break;
        case 2: cout << "Mage!\n"; break;
        case 3: cout << "Archer!\n"; break;
        }

        // Main storyline branching
        cout << "You find yourself at a crossroads. Where would you like to go?" << endl;
        cout << "1. Enter the dark forest" << endl;
        cout << "2. Head towards the village" << endl;
        cout << "3. Follow the river to the mountains" << endl;
        cout << "======================================================================" << endl;
        cout << "Enter your choice: ";
        int choice = getValidChoice(1, 3);

        switch (choice) {
        case 1: scenarioForest(); break;
        case 2: scenarioVillage(); break;
        case 3: cout << "You follow the river and encounter a mysterious figure near the mountain." << endl;
            // Additional scenario logic for the mountain path
            break;
        }

        cout << "1. Play Again" << endl;
        cout << "2. Return to Main Menu" << endl;
        cout << "======================================================================" << endl;
        int replayChoice = getValidChoice(1, 2);
        if (replayChoice == 2) {
            playing = false;
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(0))); // Seed for random events

    bool gameRunning = true;
    while (gameRunning) {
        displayMenu();
        int choice = getValidChoice(1, 3);
        switch (choice) {
        case 1:
            startGame();
            break;
        case 2:
            displayInstructions();
            break;
        case 3:
            cout << "Thank you for playing. Goodbye!" << endl;
            gameRunning = false;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    return 0;
}
