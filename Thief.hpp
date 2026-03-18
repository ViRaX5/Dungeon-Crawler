
#pragma once
#include "Character.hpp"

class Thief : public Character
{
private:
public:
    Thief(std::string name)
        : Character(name, 60, 20, 7) {}
    ~Thief() {}
    bool pickUp(Item* itemToAdd);
};
