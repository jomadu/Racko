#ifndef HUMAN_HPP
#define HUMAN_HPP

#include "player.hpp"

class Human : public Player
{
public:
    using Player::Player;
    std::string toString() const override;
    bool takeTurn(std::stack<int>& draw, std::stack<int>& discard) override;
};

#endif //HUMAN_HPP