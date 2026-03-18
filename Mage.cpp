// Noam Eilat : 322713025
// Amit Lachmann : 207448267

#include <stdexcept>
#include "Character.hpp"
#include "Mage.hpp"
#include "Item.hpp"

bool Mage::pickUp(Item *itemToAdd)
{
    ItemType type = itemToAdd->getItemType();
    switch (type)
    {
    case WAND:
    {
        int NewTotalStats = itemToAdd->getTotalStats();
        if (getFirstItem() == nullptr)
        {
            insertWeaponToInventory(itemToAdd);
            std::cout << getCharacterName() << " has picked up the " << itemToAdd->displayStats() << itemToAdd->getName() << std::endl;
            return true;
        }
        else
        {
            int CurrTotalStats = getTotalWeaponStats();
            if (NewTotalStats > CurrTotalStats)
            {
                Item* oldWeapon = Character::swapWeapon(itemToAdd);
                std::cout << getCharacterName() << " has picked up the " << itemToAdd->displayStats() << itemToAdd->getName() << std::endl;
                std::cout << "The old " << itemToAdd->displayStats() << itemToAdd->getName() << " was destroyed when dropped" << std::endl;
                delete oldWeapon;
                return true;
            }
        }
        std::cout << getCharacterName() << " has not picked up the " << itemToAdd->displayStats() << itemToAdd->getName() << " because the equiped item is better" << std::endl;
        return false;
        break;
    }
    case POTION:
    {
        Character::drinkPotion(itemToAdd);
        return true;
        break;
    }
    default:
    {
        std::cout << getCharacterName() << " can't pick up the " << itemToAdd->getName() << std::endl;
        return false;
        break;
    }
    }
}