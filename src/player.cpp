#include "player.hpp"
#include "game.hpp"
#include <sstream>
#include <iostream>
#include <regex>
#include <iomanip>
#include "math.h"

Player::Player()
{
    slots_.fill(0);
}
Player::Player(const std::string &name) : Player()
{
    name_ = name;
}

std::string Player::name() const
{
    return name_;
}
void Player::name(const std::string &name)
{
    name_ = name;
}

std::array<int, Player::NUM_SLOTS> Player::slots() const
{
    return slots_;
}
void Player::slots(const std::array<int, Player::NUM_SLOTS> &slots)
{
    slots_ = slots;
}
int Player::slot(const int idx) const
{
    if (idx < 0 || idx >= slots_.size())
    {
        throw std::out_of_range("out of range");
    }
    return slots_.at(idx);
}
void Player::slot(const int idx, const int val)
{
    if (idx < 0 || idx >= slots_.size())
    {
        throw std::out_of_range("out of range");
    }
    slots_[idx] = val;
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
std::string Player::toString() const
{
    std::stringstream ss;
    ss << "Player::name_: " << name_ << ", Player::slots_: " << slotsToString();
    return ss.str();
}
std::string Player::slotsToString(const bool formatted) const
{
    std::stringstream ss;
    if (formatted)
    {
        for (int i = slots_.size() - 1; i >= 0; i--)
        {
            auto card_val = slots_[i];
            auto digits_in_max_card_val = ceil(log10(Game::MAX_CARD_VALUE));
            auto digits_in_curr_card_val = ceil(log10(card_val));
            std::string slot_delim = ":";
            auto num_dashes = int(card_val / float(Game::MAX_CARD_VALUE) * (Game::MAX_TERM_WIDTH - digits_in_max_card_val - slot_delim.size())) - digits_in_curr_card_val;
            ss << std::setw(digits_in_max_card_val) << slotHuer(i) << slot_delim;
            while (num_dashes > 0)
            {
                ss << '-';
                num_dashes--;
            }
            ss << card_val << std::endl;
        }
    }
    else
    {
        std::string del = "";
        for (auto slot : slots_)
        {
            ss << del << slot;
            if (del == "")
            {
                del = ",";
            }
        }
    }

    return ss.str();
}
int Player::slotIndex(const int val)
{
    int ret  = -1;
    if (val >= 0 && val <= Game::MAX_CARD_VALUE)
    {
        ret = (val - 1) / slotStepSize();
    }
    return ret;
}
int Player::slotHuer(const int index)
{
    if (index >= 0 and index < Player::NUM_SLOTS)
    {
        return (index + 1) * slotStepSize();
    }
    else
    {
        return -1;
    }
}
int Player::slotStepSize()
{
    return Game::MAX_CARD_VALUE / Player::NUM_SLOTS;
}

std::ostream &operator<<(std::ostream &os, const Player &p)
{
    os << p.toString();
    return os;
}