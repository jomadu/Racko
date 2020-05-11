#include "human.hpp"

bool Human::takeTurn(std::stack<int> &draw, std::stack<int> &discard)
{
    std::cout << std::endl
              << "### HUMAN: " << name_ << "'s turn! ###" << std::endl;
    std::cout << "Current slots: " << std::endl;
    std::cout << slotsToString(true) << std::endl;
    int draw_choice = -1;
    bool valid_input = false;
    while (!valid_input)
    {
        std::cout << "Draw from:" << std::endl;
        std::cout << "[0] - Draw Pile    : ?" << std::endl;
        std::cout << "[1] - Discard Pile : " << discard.top() << std::endl;
        std::cout << "> ";
        std::cin >> draw_choice;
        std::cout << std::endl;
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

        std::cout << "Drew from draw pile: (" << drawn_card << ")" << std::endl;
    }
    else
    {
        drawn_card = discard.top();
        discard.pop();

        std::cout << "Drew from discard pile: (" << drawn_card << ")" << std::endl;
    }

    std::cout << "Current slots: " << std::endl;
    std::cout << slotsToString(true) << std::endl;
    int swap_choice = -1;
    valid_input = false;
    while (!valid_input)
    {
        std::cout << "Drew card: (" << drawn_card << ")" << std::endl;
        std::cout << "[0] - Discard" << std::endl;
        std::cout << "[1] - Swap with a card in a slot" << std::endl;
        std::cout << "> ";
        std::cin >> swap_choice;
        std::cout << std::endl;
        valid_input = swap_choice == 0 || swap_choice == 1;
        if (!valid_input)
        {
            std::cout << "Invalid input: must be 0 or 1" << std::endl;
        }
    }
    if (swap_choice == 1)
    {
        std::cout << "Swap drawn card (" << drawn_card << ") with a card in a slot:" << std::endl;
        std::cout << "Current slots:" << std::endl;
        std::cout << slotsToString(true) << std::endl;
        int slot_choice = -1;
        int slot_choice_index = -1;
        valid_input = false;
        while (!valid_input)
        {
            std::cout << "Choose slot to swap with drawn card (" << drawn_card << "). (input: ";
            auto i = 0;
            std::string del = "";
            while (i < 2 and i < Human::NUM_SLOTS)
            {
                std::cout << del << slotUpperBound(i);
                if (del == "")
                {
                    del = ", ";
                }
                i++;
            }
            std::cout << ", etc...)" << std::endl;
            std::cout << "> ";
            std::cin >> slot_choice;
            std::cout << std::endl;
            slot_choice_index = slotIndex(slot_choice);
            valid_input = slot_choice % slotStepSize() == 0 && slot_choice_index >= 0;
            if (!valid_input)
            {
                std::cout << "Invalid input: must be between a slot number." << std::endl;
            }
        }

        auto swapped_card = slots_.at(slot_choice_index);

        std::cout << "Swapping card in slot " << slotUpperBound(slot_choice_index) << " (" << swapped_card << ") with drawn card (" << drawn_card << ")" << std::endl;

        slots_[slot_choice_index] = drawn_card;

        std::cout << "Slots after swapping:" << std::endl;
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