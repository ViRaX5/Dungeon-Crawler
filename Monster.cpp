/*  Noam Eilat : 322713025
    Amit Lachmann : 207448267   */

#include <string>
#include <stdexcept>
#include "Monster.hpp"
#include "Character.hpp"

Monster::Monster(std::string name, int health, int strength, int defense)
    : name(name), health(health), strength(strength), defense(defense)
{
    if (name.empty())
    {
        throw std::invalid_argument("Error : Monster Name must not be empty");
    }
    if (health <= 0)
    {
        throw std::invalid_argument("Error : Monster Health must be at least 1");
    }
    if (strength < 0)
    {
        throw std::invalid_argument("Error : Monster Strength must be at least 0");
    }
    if (defense < 0)
    {
        throw std::invalid_argument("Error : Monster Defense must be at least 0");
    }
}

void Monster::attack(Character &target)
{
    target.setCharacterHealth(target.getCharacterHealth() - std::max((this->strength - target.getCharacterDefense()), 1));
}

bool Monster::isDefeated() const
{
    return this->health > 0 ? false : true;
}
