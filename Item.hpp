// Noam Eilat : 322713025
// Amit Lachmann : 207448267

#pragma once
#include <string>

typedef enum ItemType_e
{
    SWORD,
    WAND,
    DAGGER,
    SHIELD,
    POTION,
    POTIONHP,
    POTIONSTR,
    POTIONDEF,
} ItemType;

class Item
{
private:
    ItemType itemType;
    int healthBonus;
    int strengthBonus;
    int defenseBonus;

public:
    // Constructors / Destructor
    Item(ItemType type, int health, int strength, int defense);
    virtual ~Item() = 0;

    // Getters / Setters
    inline virtual void setItemType(ItemType type) {itemType = type;}
    inline virtual ItemType getItemType() { return this->itemType; }
    inline virtual int getItemHealthBonus() const { return this->healthBonus; }
    inline virtual int getTotalStats() {return healthBonus + strengthBonus + defenseBonus;}
    // inline virtual void setItemHealthBonus(int newHealth) {}
    inline virtual void addItemHealthBonus(int addHealth) { healthBonus += addHealth; }
    inline virtual int getItemStrengthBonus() const { return this->strengthBonus; }
    inline virtual void addItemStrengthBonus(int addStrength) { strengthBonus += addStrength; }
    // inline virtual void setItemStrengthBonus(int newStrength) {}
    inline virtual int getItemDefenseBonus() const { return this->defenseBonus; }
    // inline virtual void setItemDefenseBonus(int newDefense) {}
    inline virtual void addItemDefenseBonus(int addDefense) { defenseBonus += addDefense; }
    inline virtual std::string getName() = 0;

    inline virtual std::string displayStats() {return std::to_string(healthBonus) + " " + std::to_string(strengthBonus) + " " + std::to_string(defenseBonus) + " ";}
};
