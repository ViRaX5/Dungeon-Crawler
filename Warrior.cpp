// Noam Eilat : 322713025
// Amit Lachmann : 207448267

#include <stdexcept>
#include "Character.hpp"
#include "Warrior.hpp"
#include "Item.hpp"



bool Warrior::pickUp(Item *itemToAdd)
{
    if (!itemToAdd)
    {
        throw std::invalid_argument("Error : null item in pickUp Warrior");
    }
    ItemType type = itemToAdd->getItemType();
    switch (type)
    {
    case SWORD:
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
        std::cout << getCharacterName() << " has not picked up the " << itemToAdd->displayStats() << itemToAdd->getName() << " because the equiped one is better" << std::endl;
        return false;
        break;
    }
    case SHIELD:
    {
        int NewTotalStats = itemToAdd->getItemDefenseBonus() + itemToAdd->getItemHealthBonus() + itemToAdd->getItemStrengthBonus();
        if (getSecondItem() == nullptr)
        {
            insertShieldToInventory(itemToAdd);
            std::cout << getCharacterName() << " has picked up the " << itemToAdd->displayStats() << itemToAdd->getName() << std::endl;
            return true;
        }
        else
        {
            int CurrTotalStats = getTotalShieldStats();
            if (NewTotalStats > CurrTotalStats)
            {
                Item* oldShield = Character::swapShield(itemToAdd);
                std::cout << getCharacterName() << " has picked up the " << itemToAdd->displayStats() << itemToAdd->getName() << std::endl;
                std::cout << "The old " << itemToAdd->displayStats() << itemToAdd->getName() << " was destroyed when dropped" << std::endl;
                delete oldShield;
                return true;
            }
        }
        std::cout << getCharacterName() << " has not picked up the " << itemToAdd->displayStats() << itemToAdd->getName() << " because the equiped one is better" << std::endl;
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
