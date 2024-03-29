#ifndef ACCOUNTMANAGEMENT_H
#define ACCOUNTMANAGEMENT_H

#include <fstream>
#include <sstream>
#include <vector>
#include "player.h"

class AccountManagement
{
public:
    AccountManagement();
    Player player1;
    Player player2;
    std::vector<Player> playersList;
    std::vector<Player> loadList();
    bool login(Player &p, std::string name, std::string password);
    bool registration(std::string name, std::string password);
    void calculateResult(int result);
    void recordResult();
    bool checkIfPlayers();
    void swapColours();
};

#endif // ACCOUNTMANAGEMENT_H
