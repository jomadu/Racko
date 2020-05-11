#ifndef COMPUTER_HPP
#define COMPUTER_HPP

#include "player.hpp"

class Computer : public Player
{
protected:
    int bestSlot(int card) const;

public:
    using Player::Player;
    std::string toString() const override;
    bool takeTurn(std::stack<int> &draw, std::stack<int> &discard) override;
};

#endif //COMPUTER_HPP