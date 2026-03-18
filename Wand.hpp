
#pragma once
#include "Item.hpp"

class Wand : public Item
{
private:
    ItemType item = WAND;
    std::string name = "Wand";

public:
    Wand(int healthBonus, int strengthBonus, int defenseBonus)
        : Item(WAND, 0 + healthBonus, 10 + strengthBonus, 0 + defenseBonus) {}
    ~Wand() {}
    inline std::string getName() { return name; }
};
