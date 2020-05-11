#include "utils.hpp"
#include <iostream>

int Utils::optionsMenu(const std::string &title, const std::string &prompt, const std::vector<std::string> &options, const std::vector<int> &custom_selectors)
{
    if (title != "")
    {
        std::cout << title << std::endl;
    }
    std::string choice_str;

    bool valid_input = false;
    auto using_custom_selectors = custom_selectors.size() == options.size();
    std::vector<std::string> valid_inputs;

    for (auto i = 0; i < options.size(); i++)
    {
        valid_inputs.push_back(std::to_string(using_custom_selectors ? custom_selectors.at(i) : i));
    }

    while (!valid_input)
    {
        std::cout << prompt << std::endl;
        for (auto i = 0; i < options.size(); i++)
        {
            std::cout << "[" << (using_custom_selectors ? custom_selectors.at(i) : i) << "] - " << options.at(i) << std::endl;
        }
        std::cout << "> ";
        std::getline(std::cin, choice_str);
        std::cout << std::endl;
        valid_input = std::find(valid_inputs.begin(), valid_inputs.end(), choice_str) != valid_inputs.end();
        if (!valid_input)
        {
            std::cout << "Invalid input: must be one of [";
            auto delim = "";
            for (auto vi : valid_inputs)
            {
                std::cout << delim << vi;
                if (delim == "")
                {
                    delim = ", ";
                }
            }
            std::cout << "]" << std::endl;
        }
    }
    return std::stoi(choice_str);
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
