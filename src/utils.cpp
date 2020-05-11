#include "utils.hpp"
#include <iostream>

int Utils::menu(const std::string &title, const std::string &prompt, const std::vector<std::string> &options, const std::vector<int> &custom_selectors)
{
    std::cout << title << std::endl;
    int choice = -1;
    bool valid_input = false;
    auto using_custom_selectors = custom_selectors.size() == options.size();
    std::vector<int> valid_inputs;

    for (auto i = 0; i < options.size(); i++)
    {
        valid_inputs.push_back(using_custom_selectors ? custom_selectors.at(i) : i);
    }

    while (!valid_input)
    {
        std::cout << prompt << std::endl;
        for (auto i = 0; i < options.size(); i++)
        {
            std::cout << "[" << (using_custom_selectors ? custom_selectors.at(i) : i) << "] - " << options.at(i) << std::endl;
        }
        std::cout << "> ";
        std::cin >> choice;
        std::cout << std::endl;
        valid_input = std::find(valid_inputs.begin(), valid_inputs.end(), choice) != valid_inputs.end();
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

    return choice;
}

std::string Utils::menu(const std::string &title, const std::string &prompt, const std::string &regex_validator)
{
    std::cout << title << std::endl;
    std::string input = "";
    bool valid_input = false;
    std::regex validator(regex_validator);

    while (!valid_input)
    {
        std::cout << prompt << std::endl;
        std::cout << "> ";
        std::cin >> input;
        std::cout << std::endl;
        valid_input = std::regex_match(input, validator);
        if (!valid_input)
        {
            std::cout << "Invalid input: input must match the regex " << regex_validator << std::endl;
        }
    }
    return input;
}
