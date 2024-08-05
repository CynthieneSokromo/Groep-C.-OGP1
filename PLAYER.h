
#ifndef PLAYER_PART_H
#define PLAYER_PART_H

#include <string>
using namespace std;

class Player {
public:
    // Constructor to initialize player's name and score
    Player(const string& playerName) : name(playerName), score(0) {}

    // Getter for player's name
    string getName() const { return name; }

    // Getter for player's score
    int getScore() const { return score; }

    // Increment player's score
    void updateScore() { score++; }

    // Switch current player between player1 and player2
    void switchPlayer(Player*& currentPlayer, Player& player1, Player& player2) {
        currentPlayer = (currentPlayer == &player1) ? &player1 : &player2;
    }

private:
    string name; // Player's name
    int score;   // Player's score
};

#endif // PLAYER_PART_H


