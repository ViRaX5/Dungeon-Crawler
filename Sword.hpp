// Noam Eilat : 322713025
// Amit Lachmann : 207448267

#pragma once
#include "Item.hpp"

class Sword : public Item
{
private:
    ItemType item = SWORD;
    std::string name = "Sword";

public:
    Sword(int healthBonus, int strengthBonus, int defenseBonus)
        : Item(SWORD, 0 + healthBonus, 10 + strengthBonus, 5 + defenseBonus) {}
    ~Sword() {}
    inline std::string getName() { return name; }
};