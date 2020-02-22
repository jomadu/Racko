#include "player.hpp"
#include <sstream>
#include <iostream>
#include <regex>

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
bool Player::takeTurn(std::stack<int> &draw, std::stack<int> &discard)
{
    std::cout << name_ << "'s turn!" << std::endl;
    std::cout << "slots: " << slotsToString() << std::endl;
    std::cout << std::endl;
    int draw_choice = -1;
    bool valid_input = false;
    while (!valid_input)
    {
        std::cout << "Draw from: (input 0 or 1)" << std::endl;
        std::cout << "[0] - Draw Pile    : ???"<< std::endl;
        std::cout << "[1] - Discard Pile : " << discard.top() << std::endl;
        std::cin >> draw_choice;
        valid_input = draw_choice == 0 || draw_choice == 1;
        if (!valid_input)
        {
            std::cout << "Invalid input: must be 0 or 1" << std::endl;
        }
    }

    int drawn_card;
    if (draw_choice == 0)
    {
        drawn_card = draw.top();
        draw.pop();

        std::cout << "Drew from draw pile: " << drawn_card << std::endl;
    }
    else
    {
        drawn_card = discard.top();
        discard.pop();

        std::cout << "Drew from discard pile: " << drawn_card << std::endl;
    }

    int slot_choice = -1;
    valid_input = false;
    while (!valid_input)
    {
        std::cout << "Swap drawn card (" << drawn_card << ") with a card in a slot:" << std::endl;
        std::cout << "(input 0 - " << Player::NUM_SLOTS - 1 << ")" << std::endl;
        for (auto i = 0; i < slots_.size(); i++)
        {
            std::cout << "[" << i << "]: " << slots_.at(i) << std::endl;
        }
        std::cin >> slot_choice;
        valid_input = slot_choice >= 0 && slot_choice < Player::NUM_SLOTS;
        if (!valid_input)
        {
            std::cout << "Invalid input: must be between 0 and " << Player::NUM_SLOTS - 1 << std::endl;
        }
    }

    auto swapped_card = slots_.at(slot_choice);

    std::cout << "Swapping card in slot " << slot_choice << " (" << swapped_card << ") with drawn card (" << drawn_card << ")" << std::endl;

    slots_[slot_choice] = drawn_card;

    std::cout << "Discarding swapped card (" << swapped_card << ") onto discard pile." << std::endl;
    discard.push(swapped_card);

    bool has_racko = hasRacko();
    if (has_racko)
    {
        std::cout << name_ << " has a Racko!" << std::endl;
    }
    else
    {
        std::cout << name_ << "'s turn complete!" << std::endl;
    }
    
    return hasRacko();
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
std::string Player::slotsToString() const
{
    std::stringstream ss;
    std::string del = "";
    for (auto slot : slots_)
    {
        ss << del << slot;
        if (del == "")
        {
            del = ",";
        }
    }
    return ss.str();
}

std::ostream &operator<<(std::ostream &os, const Player &p)
{
    os << p.toString();
    return os;
}