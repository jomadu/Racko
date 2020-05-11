#include "player.hpp"
#include <sstream>
#include <iostream>
#include <regex>
#include <iomanip>
#include "math.h"
#include "game.hpp"

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
    ss << "Player Name: " << name_ << ", Player Slots: " << slotsToString();
    return ss.str();
}
std::string Player::slotsToString(const bool formatted) const
{
    std::stringstream ss;
    if (formatted)
    {
        auto digits_in_max_card_val = ceil(log10(Game::MAX_CARD_VALUE));
        std::string slot_delim = " : ";
        auto max_width = Utils::MAX_TERM_WIDTH - digits_in_max_card_val - slot_delim.size() - std::string("[]").size();
        for (int i = Player::NUM_SLOTS - 1; i >= 0; i--)
        {
            auto slot_val = slots_.at(i);

            ss << "[" << std::setw(digits_in_max_card_val) << slotUpperBound(i) << "]" << slot_delim
               << slotToString(i, true, max_width) << std::endl;
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
std::string Player::slotToString(const int index, const bool formatted, const int max_width) const
{
    if (index < 0 || index >= Player::NUM_SLOTS)
    {
        return "";
    }

    std::stringstream ss;
    auto slot_val = slots_.at(index);
    if (formatted)
    {
        auto digits_in_curr_card_val = ceil(log10(slot_val));
        auto num_dashes = int(slot_val / float(Game::MAX_CARD_VALUE) * (max_width)) - digits_in_curr_card_val;
        while (num_dashes > 0)
        {
            ss << '-';
            num_dashes--;
        }
        ss << slot_val;
    }
    else
    {
        ss << slot_val;
    }
    return ss.str();
}
int Player::slotIndex(const int val)
{

    int ret = -1;
    if (val >= 0 && val <= Game::MAX_CARD_VALUE)
    {
        ret = (val - 1) / slotStepSize();
    }
    return ret;
}
int Player::slotUpperBound(const int index)
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
int Player::slotLowerBound(const int index)
{
    if (index >= 0 and index < Player::NUM_SLOTS)
    {
        return index * slotStepSize();
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