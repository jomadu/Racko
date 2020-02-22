#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"
#include <vector>
#include <stack>

class Game
{
public:
    Game();
    std::vector<Player> players() const;
    int turn() const;
    void addPlayer(const std::string& name);
    void deal();
    void shuffleDraw();
    void playTurn();
    bool gameOver() const;
    int playerTurn() const;
    std::string toString() const;
    std::string playersToString() const;
    std::string drawToString() const;
    std::string discardToString() const;
    friend std::ostream& operator<<(std::ostream& os, const Game& g);

private:
    std::string pileToString(const std::stack<int>& pile) const;

    bool game_over_;
    std::vector<Player> players_;
    int turn_;
    std::stack<int> draw_;
    std::stack<int> discard_;
    static constexpr int MAX_CARD_VALUE = 50;
};



#endif //GAME_HPP