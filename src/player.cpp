#include "player.hpp"

Player::Player()
{
    slots_.fill(0);
}
Player::Player(const std::string& name) : Player()
{
    name_ = name;
}

std::string Player::name() const
{
    return name_;
}
void Player::name(const std::string& name)
{
    name_ = name;
}

std::array<int,10> Player::slots() const
{
    return slots_;
} 
void Player::slots(const std::array<int,10>& slots)
{
    slots_ = slots;
}

bool Player::hasRacko() const
{
    auto last_slot = -1;
    for (auto slot : slots_)
    {
        if (slot <= last_slot)
        {
            return false;
        }
        else
        {
            last_slot = slot;
        }
    }
    return true;
}