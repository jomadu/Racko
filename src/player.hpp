#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <array>

class Player
{
public:
    Player();
    Player(const std::string& name);
    
    std::string name() const;
    void name(const std::string& name);

    std::array<int,10> slots() const; 
    void slots(const std::array<int,10>& slots); 

    bool hasRacko() const;

private:
    std::string name_;
    std::array<int,10> slots_;
};



#endif //PLAYER_HPP