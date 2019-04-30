#include "player.h"

Player::Player()
{
}

Player::Player(std::string n, std::string p, int g, int w, int l)
{
    this->name = n;
    this->password = p;
    this->gamePlayed = g;
    this->gameWin = w;
    this->gameLose = l;
}

void Player::printPlayerRecord()
{
    std::cout << "Name: " << name << "\nGames Played: " << gamePlayed << "\nGames Won: " << gameWin << "\nGames Lost: " << gameLose << std::endl;
}

void Player::setgamePlayed()
{
    this->gamePlayed++;
}

void Player::setgameWon()
{
    this->gameWin++;
}

void Player::setgameLose()
{
    this->gameLose++;
}

std::string Player::getName()
{
    return name;
}

std::string Player::getPassword()
{
    return password;
}

int Player::getGamePlayed()
{
    return gamePlayed;
}

int Player::getGameWin()
{
    return gameWin;
}

int Player::getGameLose()
{
    return gameLose;
}

