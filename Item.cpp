
#include <stdexcept>
#include "Item.hpp"

Item::Item(ItemType type, int health, int strength, int defense)
    : itemType(type), healthBonus(health), strengthBonus(strength), defenseBonus(defense)
{
}
Item::~Item() {}
