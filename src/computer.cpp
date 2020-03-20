#include "computer.hpp"

bool Computer::takeTurn(std::stack<int> &draw, std::stack<int> &discard)
{
    std::cout << std::endl
              << "### COMPUTER: " << name_ << "'s turn! ###" << std::endl;
    std::cout << "Current slots: " << std::endl;
    std::cout << slotsToString(true) << std::endl;

    auto discard_best_slot = bestSlot(discard.top());
    if (discard_best_slot >= 0)
    {
        auto drawn_card = discard.top();
        discard.pop();
        std::cout << "Drew from discard pile: " << drawn_card << std::endl;
        auto swapped_card = slots_.at(discard_best_slot);
        std::cout << "Swapping card in slot " << discard_best_slot << " (" << swapped_card << ") with drawn card (" << drawn_card << ")" << std::endl;
        slots_.at(discard_best_slot) = drawn_card;
        discard.push(swapped_card);
    }
    else
    {
        auto drawn_card = draw.top();
        draw.pop();
        std::cout << "Drew from draw pile: " << drawn_card << std::endl;
        auto draw_best_slot = bestSlot(drawn_card);
        if (draw_best_slot >= 0)
        {
            auto swapped_card = slots_.at(draw_best_slot);
            std::cout << "Swapping card in slot " << draw_best_slot << " (" << swapped_card << ") with drawn card (" << drawn_card << ")" << std::endl;
            slots_.at(draw_best_slot) = drawn_card;
            discard.push(swapped_card);
        }
        else
        {
            std::cout << "Discarding drawn card (" << drawn_card << ") onto discard pile." << std::endl;
            discard.push(drawn_card);
        }
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

int Computer::bestSlot(int card) const
{
    auto ret = -1;

    // card is 38, we'd want to check if slot labeled 35 has a good card
    auto step_size = slotStepSize();
    auto card_slot_index = slotIndex(card);
    if (card_slot_index >= 0)
    {
        auto lower_bound_inc = step_size * card_slot_index;
        auto upper_bound = step_size * (card_slot_index + 1);
        auto existing_card = slots_.at(card_slot_index);
        if (existing_card < lower_bound_inc || existing_card >= upper_bound)
        {
            ret = card_slot_index;
        }
    }

    return ret;
}
