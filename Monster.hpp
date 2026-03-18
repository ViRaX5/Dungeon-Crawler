/*  Noam Eilat : 322713025
    Amit Lachmann : 207448267   */
#include<iostream>
//#include "Character.hpp"

#pragma once

class Character;

class Monster
{
private:
    std::string name;
    int health;
    int strength;
    int defense;

public:
    // Constructors / Destructor
    Monster(std::string name, int health, int strength, int defense);
    ~Monster() {};

    // Main Functions
    void attack(Character &target);
    bool isDefeated() const;

    inline std::string getMonsterName() const {return name;}
    inline void setMonsterName(std::string newName) {name = newName;}
    inline int getMonsterHealth() const {return health;}
    inline void setMonsterHealth(int newHealth) {health = newHealth;}
    inline int getMonsterStrength() const {return strength;}
    inline void setMonsterStrength(int newStrength) {strength = newStrength;}
    inline int getMonsterDefense() const {return defense;}
    inline void setMonsterDefense(int newDefense) {defense = newDefense;}
};
