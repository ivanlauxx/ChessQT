#include "accountmanagement.h"

AccountManagement::AccountManagement()
{
    playersList = loadList();
}

std::vector<Player> AccountManagement::loadList()
{
    std::ifstream file("../../playerData.txt");
    std::string line;
    std::vector<Player> playersList;
    std::string un;
    std::string pw;
    int gp;
    int gw;
    int gl;
    if (file.is_open())
    {
        while(getline(file, line))
        {
            std::istringstream is(line);
            is >> un >> pw >> gp >> gw >> gl;
            playersList.push_back(Player(un, pw, gp, gw, gl));
        }
    }
    return playersList;
}

bool AccountManagement::login(Player &p, std::string name, std::string password)
{
    if(name != player2.getName() && name != player1.getName())
    {
        for(Player player : playersList)
        {
            if(player.getName() == name && player.getPassword() == password)
            {
                p = player;
                return true;
            }
        }
    }
    return false;
}

bool AccountManagement::registration(std::string name, std::string password)
{
    int gp = 0;
    int gw = 0;
    int gl = 0;
    std::ofstream file;
    file.open("../../playerData.txt", std::ios::out | std::ios::app);
    for(Player player : this->playersList)
    {
        if(player.getName() == name)
        {
            file.close();
            return false;
        }
    }
    file << name << " " << password << " " << gp << " " << gw << " " << gl << std::endl;
    file.close();
    return true;
}

void AccountManagement::calculateResult(int result)
{
    if(result == 1)
    {
        player1.setgameWon();
        player1.setgamePlayed();
        player2.setgameLose();
        player2.setgamePlayed();
        for(Player &player : this->playersList)
        {
            if(player.getName() == player1.getName())
            {
                player.setgameWon();
                player.setgamePlayed();
            }
            if(player.getName() == player2.getName())
            {
                player.setgameLose();
                player.setgamePlayed();
            }
        }
    }
    else
    {
        player2.setgameWon();
        player2.setgamePlayed();
        player1.setgameLose();
        player1.setgamePlayed();
        for(Player &player : this->playersList)
        {
            if(player.getName() == player2.getName())
            {
                player.setgameWon();
                player.setgamePlayed();
            }
            if(player.getName() == player1.getName())
            {
                player.setgameLose();
                player.setgamePlayed();
            }
        }
    }
    recordResult();
}

void AccountManagement::recordResult()
{
    std::ofstream temp("../../temp.txt");
    for(Player p : playersList)
    {
        temp << p.getName() << " " << p.getPassword() << " " << p.getGamePlayed() << " " << p.getGameWin() << " " << p.getGameLose() << std::endl;
    }
    temp.close();
    remove("../../playerData.txt");
    rename("../../temp.txt","../../playerData.txt");
    temp.close();
}

bool AccountManagement::checkIfPlayers()
{
    bool bothPlayers = false;
    if (player1.getName() != "" && player2.getName() != "") {
        bothPlayers = true;
    }

    return bothPlayers;
}

void AccountManagement::swapColours()
{
    Player whitePlayer = player1;
    Player blackPlayer = player2;

    Player temp = whitePlayer;
    player1 = blackPlayer;
    player2 = temp;
}
