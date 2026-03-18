// Noam Eilat : 322713025
// Amit Lachmann : 207448267

#pragma once
#include "Item.hpp"

class Dagger : public Item
{
private:
    ItemType item = DAGGER;
    std::string name = "Dagger";

public:
    Dagger(int healthBonus, int strengthBonus, int defenseBonus)
        : Item(DAGGER, 0 + healthBonus, 7 + strengthBonus, 3 + defenseBonus) {}
    ~Dagger() {}
    inline std::string getName() { return name; }
};