#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"
#include <vector>

class Game
{
public:
    Game();
    std::vector<Player> players() const;
    int turn() const;
    void addPlayer(const std::string& name);
    void playTurn();
    bool gameOver() const;
    int playerTurn() const;
    std::string toString() const;
private:
    std::vector<Player> players_;
    int turn_;
};



#endif //GAME_HPP