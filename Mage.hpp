/*  Noam Eilat : 322713025
    Amit Lachmann : 207448267   */

#pragma once
#include "Character.hpp"

class Mage : public Character
{
private:
public:
    Mage(std::string name)
        : Character(name, 40, 25, 5) {}
    ~Mage() {}
    bool pickUp(Item* itemToAdd);
};