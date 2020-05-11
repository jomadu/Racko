#include "utils.hpp"
#include "logger.hpp"
#include <iostream>
#include <iomanip>

std::tuple<int, std::string, std::string> Utils::optionsMenu(const std::string &title, const std::string &prompt, const std::vector<std::string> &choices)
{
    std::vector<std::pair<std::string, std::string>> choices_helper;
    for (auto i = 0; i < choices.size(); i++)
    {
        choices_helper.emplace_back(std::to_string(i), choices.at(i));
    }

    return optionsMenu(title, prompt, choices_helper);
}

std::tuple<int, std::string, std::string> Utils::optionsMenu(const std::string &title, const std::string &prompt, const std::vector<std::pair<std::string, std::string>> &choices)
{
    if (title != "")
    {
        std::cout << title << std::endl;
    }
    int selected_idx = -1;
    std::string selected_text = "";
    std::map<std::string, std::pair<int, std::string>> selectors;

    int max_selector_length = 0;

    for (auto i = 0; i < choices.size(); i++)
    {
        auto &selector = choices.at(i).first;
        if (selectors.count(selector))
        {
            throw std::invalid_argument("choice selectors must be unique");
        }
        selectors[selector] = std::pair<int, std::string>(i, choices.at(i).second);
        if (selector.size() > max_selector_length)
        {
            max_selector_length = selector.size();
        }
    }

    std::stringstream menu_ss;
    menu_ss << prompt << ":" << std::endl;
    for (auto& pair : choices)
    {
        auto selector = "[" + pair.first + "]";
        auto &text = pair.second;
        menu_ss << std::setw(max_selector_length + 2) << selector << " : " << text << std::endl;
    }
    std::string menu = menu_ss.str();

    bool valid_input = false;
    std::string selected;
    while (!valid_input)
    {
        std::cout << menu;
        std::cout << "> ";
        std::getline(std::cin, selected);
        std::cout << std::endl;

        valid_input = selectors.count(selected);
        if (!valid_input)
        {
            std::cout << "Invalid input: must be one of [";
            auto delim = "";
            for (auto &kv : selectors)
            {
                std::cout << delim << kv.first;
                if (delim == "")
                {
                    delim = ", ";
                }
            }
            std::cout << "]" << std::endl;
        }
        else
        {
            selected_idx = selectors.at(selected).first;
            selected_text = choices.at(selected_idx).second;
        }
    }

    return std::tuple<int, std::string, std::string>(selected_idx, selected, selected_text);
}

std::string Utils::validatedStringInput(const std::string &title, const std::string &prompt, const std::string &regex_validator)
{
    if (title != "")
    {
        std::cout << title << std::endl;
    }
    std::string input = "";
    bool valid_input = false;
    std::regex validator(regex_validator);

    while (!valid_input)
    {
        std::cout << prompt << std::endl;
        std::cout << "> ";
        std::getline(std::cin, input);
        std::cout << std::endl;
        valid_input = std::regex_match(input, validator);
        if (!valid_input)
        {
            std::cout << "Invalid input: input must match the regex " << regex_validator << std::endl;
        }
    }
    return input;
}
