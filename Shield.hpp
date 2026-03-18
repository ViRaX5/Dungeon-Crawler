// Noam Eilat : 322713025
// Amit Lachmann : 207448267

#pragma once
#include "Item.hpp"

class Shield : public Item
{
private:
    ItemType item = SHIELD;
    std::string name = "Shield";

public:
    Shield(int healthBonus, int strengthBonus, int defenseBonus)
        : Item(SHIELD, 0 + healthBonus, 0 + strengthBonus, 5 + defenseBonus) {}
    ~Shield() {}
    inline std::string getName() { return name; }
};