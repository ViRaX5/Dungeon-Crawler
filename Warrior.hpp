/*  Noam Eilat : 322713025
    Amit Lachmann : 207448267   */

#pragma once
#include "Character.hpp"

class Warrior : public Character
{
private:
public:
    Warrior(){}
    Warrior(std::string name) : Character(name, 100, 15, 10) {}
    ~Warrior() {}
    bool pickUp(Item* itemToAdd);
};
