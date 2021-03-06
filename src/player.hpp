#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <array>
#include <stack>
#include <iostream>
#include "utils.hpp"

class Player
{
public:
    static constexpr int NUM_SLOTS = 10;

protected:
    std::string name_;
    std::array<int, NUM_SLOTS> slots_;

public:
    Player();
    Player(const std::string &name);
    virtual ~Player(){};

    std::string name() const;
    void name(const std::string &name);

    std::array<int, NUM_SLOTS> slots() const;
    void slots(const std::array<int, NUM_SLOTS> &slots);

    int slot(const int idx) const;
    void slot(const int idx, const int val);

    virtual bool takeTurn(std::stack<int> &draw, std::stack<int> &discard) = 0;

    bool hasRacko() const;
    virtual std::string toString() const;
    std::string slotsToString(const bool formatted = false) const;
    std::string slotToString(const int index, const bool formatted = false, const int max_width = Utils::MAX_TERM_WIDTH) const;
    static int slotIndex(const int val);
    static int slotUpperBound(const int index);
    static int slotLowerBound(const int index);
    static int slotStepSize();
    friend std::ostream &operator<<(std::ostream &os, const Player &p);
};

#endif //PLAYER_HPP