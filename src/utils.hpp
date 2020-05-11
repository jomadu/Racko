#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <regex>

class Utils 
{
    public:
    static int menu(const std::string& title, const std::string& prompt, const std::vector<std::string>& options, const std::vector<int>& custom_selectors = {});
    static std::string menu(const std::string& title, const std::string& prompt, const std::string& regex_validator);
};

#endif // UTILS_HPP