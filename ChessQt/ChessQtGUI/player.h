#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

class Player
{
public:
    Player();
    Player(std::string n, std::string p, int g, int w, int l);
    void setgamePlayed();
    void setgameWon();
    void setgameLose();
    std::string getName();
    std::string getPassword();
    int getGamePlayed();
    int getGameWin();
    int getGameLose();
private:
    std::string name;
    std::string password;
    int gamePlayed = 0;
    int gameWin = 0;
    int gameLose = 0;
};

#endif // PLAYER_H
