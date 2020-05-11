#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <tuple>
#include <regex>

class Utils 
{
    public:
    static std::tuple<int, std::string, std::string> optionsMenu(const std::string& title, const std::string& prompt, const std::vector<std::string>& choices);
    static std::tuple<int, std::string, std::string> optionsMenu(const std::string& title, const std::string& prompt, const std::vector<std::pair<std::string, std::string>>& choices);
    static std::string validatedStringInput(const std::string& title, const std::string& prompt, const std::string& regex_validator);
    static std::string hLine();
    static constexpr int MAX_TERM_WIDTH = 80;
};

#endif // UTILS_HPP