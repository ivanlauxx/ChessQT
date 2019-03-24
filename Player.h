// ChessQT
// Player.h
// Made on 23-03-2019 by Max.

#include <string>

// Dont forget to do the #include for this file.
// #include <Player.h>

class Player {

public:
    // Constructor. Takes a player name and a password.
    Player(std::string playerName, std::string playerPassword);

    // Destructor. I don't know if we actually need this or not.
    ~Player();

    // Returns the player name.
    std::string getName();

    // Set new player password.
    void setNewPassword();

    // Gets player wins.
    int getWins();

    // Adds a win to the Player's record.
    void addWin();

    // Gets player losses.
    int getLosses();

    // Adds a loss to the Player's record.
    void addLoss();

    // Returns the total amount of points a player has earned on their account.
    int getTotalPoints();

    // Adds points to the Player's total. gamePoints is the amount of points a player earned in the game.
    void addGamePoints(int gamePoints);

    // Returns the win rate.
    double getWinRate();

    // Re-calculates the Players win rate.
    // GamesWon divided by GamesPlayed. Given as a percentage.
    void calculateWinRate();

    // Adds one to the games played count. Only call this when a game has ended so players don't ruin win rates.
    void countGame();

    // Add any methods you think are needed.
    // Don't be afraid.

// Constructor will set everything except for name and password to 0.
private:
    std::string playerName;
    std::string playerPassword;
    int gamesPlayed;
    int gameWon;
    int gamesLost;
    double winRate;
    int pointsEarned;
}
