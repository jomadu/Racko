#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"
#include <vector>
#include <stack>
#include <memory>

class Game
{
public:
    Game();
    std::vector<std::shared_ptr<Player>> players() const;
    int turn() const;

    void createPlayers();
    template <class T>
    void addPlayer(const std::string &name)
    {
        if (players_.size() < Game::MAX_NUM_PLAYERS)
        {
            players_.push_back(std::make_shared<T>(name));
        }
    }
    void removePlayer(const std::string& name);

    void deal();
    void shuffleDraw();
    void playTurn();
    bool gameOver() const;
    int playerTurn() const;
    void restoreDrawFromDiscard();
    std::string toString() const;
    std::string playersToString() const;
    std::string drawToString() const;
    std::string discardToString() const;
    friend std::ostream &operator<<(std::ostream &os, const Game &g);

    static constexpr int MAX_TERM_WIDTH = 80;
    static constexpr int MAX_CARD_VALUE = 50;
    static constexpr int MAX_NUM_PLAYERS = MAX_CARD_VALUE / Player::NUM_SLOTS;

private:
    std::string pileToString(const std::stack<int> &pile) const;

    bool game_over_;
    std::vector<std::shared_ptr<Player>> players_;
    int turn_;
    std::stack<int> draw_;
    std::stack<int> discard_;
};

#endif //GAME_HPP