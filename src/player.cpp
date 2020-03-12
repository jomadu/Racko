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
bool Player::takeTurn(std::stack<int> &draw, std::stack<int> &discard)
{
    std::cout << std::endl
              << "### " << name_ << "'s turn! ###" << std::endl;
    std::cout << "Current slots: " << std::endl;
    std::cout << slotsToString(true) << std::endl;
    int draw_choice = -1;
    bool valid_input = false;
    while (!valid_input)
    {
        std::cout << "Draw from:" << std::endl;
        std::cout << "[0] - Draw Pile    : ???" << std::endl;
        std::cout << "[1] - Discard Pile : " << discard.top() << std::endl;
        std::cout << ">";
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

    int swap_choice = -1;
    valid_input = false;
    while (!valid_input)
    {
        std::cout << "Current slots: " << std::endl;
        std::cout << slotsToString(true) << std::endl;
        std::cout << "Drew card " << drawn_card << ":" << std::endl;
        std::cout << "[0] - Discard" << std::endl;
        std::cout << "[1] - Swap with a card in a slot" << std::endl;
        std::cin >> swap_choice;
        valid_input = swap_choice == 0 || swap_choice == 1;
        if (!valid_input)
        {
            std::cout << "Invalid input: must be 0 or 1" << std::endl;
        }
    }
    if (swap_choice == 1)
    {
        int slot_choice = -1;
        int slot_choice_index = -1;
        valid_input = false;
        while (!valid_input)
        {
            std::cout << "Swap drawn card " << drawn_card << " with a card in a slot:" << std::endl;
            std::cout << "Current slots:" << std::endl;
            std::cout << slotsToString(true) << std::endl;
            std::cout << "Choose slot to swap with drawn card " << drawn_card << ". (input: ";
            auto i = 0;
            std::string del = "";
            while (i < 2 and i < Player::NUM_SLOTS)
            {
                std::cout << del << slotLabel(i);
                if (del == "")
                {
                    del = ", ";
                }
                i ++;
            }
            std::cout << ", etc...)" << std::endl;
            std::cout << ">";
            std::cin >> slot_choice;
            slot_choice_index = slotIndex(slot_choice);
            valid_input = slot_choice_index >= 0;
            if (!valid_input)
            {
                std::cout << "Invalid input: must be between a slot number." << std::endl;
            }
        }

        auto swapped_card = slots_.at(slot_choice_index);

        std::cout << "Swapping card in slot " << slot_choice_index << " (" << swapped_card << ") with drawn card (" << drawn_card << ")" << std::endl;

        slots_[slot_choice_index] = drawn_card;

        std::cout << "Current slots after swapping:" << std::endl;
        std::cout << slotsToString(true) << std::endl;

        std::cout << "Discarding swapped card (" << swapped_card << ") onto discard pile." << std::endl;
        discard.push(swapped_card);
    }
    else
    {
        std::cout << "Discarding drawn card (" << drawn_card << ") onto discard pile." << std::endl;
        discard.push(drawn_card);
    }

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
            ss << std::setw(digits_in_max_card_val) << slotLabel(i) << slot_delim;
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
int Player::slotIndex(const int label)
{
    int ret  = -1;
    if (label % (Game::MAX_CARD_VALUE / Player::NUM_SLOTS) == 0)
    {
        auto index = label * Player::NUM_SLOTS / Game::MAX_CARD_VALUE - 1;
        if (index >= 0 and index < Player::NUM_SLOTS)
        {
            ret = index;
        }
    }
    return ret;
}
int Player::slotLabel(const int index)
{
    if (index >= 0 and index < Player::NUM_SLOTS)
    {
        return (index + 1) * Game::MAX_CARD_VALUE / Player::NUM_SLOTS;
    }
    else
    {
        return -1;
    }
}

std::ostream &operator<<(std::ostream &os, const Player &p)
{
    os << p.toString();
    return os;
}