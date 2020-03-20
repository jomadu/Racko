#ifndef COMPUTER_HPP
#define COMPUTER_HPP

#include "player.hpp"

class Computer : public Player
{
public:
    using Player::Player;
    bool takeTurn(std::stack<int> &draw, std::stack<int> &discard) override;
protected:
    int bestSlot(int card) const;
};

#endif //COMPUTER_HPP