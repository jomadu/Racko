#include "human.hpp"
#include "utils.hpp"
#include "math.h"
#include "game.hpp"

std::string Human::toString() const
{
    std::stringstream ss;
    ss << "Human Name: " << name_ << ", Human Slots: " << slotsToString();
    return ss.str();
}
bool Human::takeTurn(std::stack<int> &draw, std::stack<int> &discard)
{
    std::cout << std::endl
              << "### HUMAN: " << name_ << "'s turn! ###" << std::endl;
    std::string title = "Current slots:\n" + slotsToString(true);
    std::string prompt = "Draw from:";
    std::vector<std::string> options = {"Draw Pile    : ?", "Discard Pile : " + std::to_string(discard.top())};
    auto draw_choice = std::get<2>(Utils::optionsMenu(title, prompt, options));

    int drawn_card;
    if (draw_choice == options.at(0))
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

    title = "Current slots:\n" + slotsToString(true);
    prompt = "Drew card: (" + std::to_string(drawn_card) + ")";
    options = {"Discard", "Swap with a card in a slot"};
    auto swap_choice = std::get<2>(Utils::optionsMenu(title, prompt, options));

    if (swap_choice == options.at(1))
    {

        title = "Swap drawn card (" + std::to_string(drawn_card) + ") with a card in a slot:\nCurrent slots:\n" + slotsToString(true);

        // Create prompt
        std::stringstream prompt_ss;
        prompt_ss << "Choose slot to swap with drawn card (" << drawn_card << "). (input: ";
        auto i = 0;
        std::string del = "";
        while (i < 2 and i < Player::NUM_SLOTS)
        {
            prompt_ss << del << slotUpperBound(i);
            if (del == "")
            {
                del = ", ";
            }
            i++;
        }
        prompt_ss << ", etc...)" << std::endl;
        prompt = prompt_ss.str();

        // Create options and custom selectors
        std::vector<std::pair<std::string, std::string>> options;
        auto current_slots = slots();

        auto digits_in_max_card_val = ceil(log10(Game::MAX_CARD_VALUE));
        auto max_width = Utils::MAX_TERM_WIDTH - digits_in_max_card_val - std::string(":").size() - std::string("[]").size(); // - 2 for the '[' and ']' surrounding the options
        for (auto i = Player::NUM_SLOTS - 1; i >= 0; i--)
        {
            options.emplace_back(std::to_string(slotUpperBound(i)), slotToString(i,true, max_width));
        }

        // Present menu
        auto slot_choice = std::get<1>(Utils::optionsMenu(title, prompt, options));
        auto slot_choice_index = slotIndex(std::stoi(slot_choice));

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