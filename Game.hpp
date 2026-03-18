// Noam Eilat : 322713025
// Amit Lachmann : 207448267

#pragma once

#include "Dungeon.hpp"
#include "Character.hpp"
#include "Item.hpp"
#include "Monster.hpp"
#include <fstream>
#include <sstream>
#include "Sword.hpp"
#include "Shield.hpp"
#include "Dagger.hpp"
#include "Wand.hpp"
#include "Potion.hpp"
#include "Warrior.hpp"
#include "Thief.hpp"
#include "Mage.hpp"
#include "List.hpp"

typedef enum FightResult_E
{
    VICTORY,
    LOSE,
} FightResult;

class Game
{
private:
    Dungeon dungeon;
    List<Character *> players;
    std::ifstream inputFile;
    std::ofstream outputFile;

public:
    Game() {};
    ~Game() {}
    void move(Character *player, Directions whereToMove);
    void loadFromFile(std::string fileName);
    void executeCommands();
    void outputFinalState(std::string fileOutputName);
    FightResult fight(Character *player, Monster *foulBeing);

    void capitalize(std::string &str);

    void handleCreate(std::stringstream &ss);
    void handleSet(std::stringstream &ss);
    void handleConnect(std::stringstream &ss);
    void handlePlace(std::stringstream &ss);
    void handleEnter(std::stringstream &ss);
    void handleMove(std::stringstream &ss);
    void handleFight(std::stringstream &ss);
    void handlePickUp(std::stringstream &ss);
    void handlePlaceMonster(std::stringstream &ss);
    void handlePlaceItem(std::string arg2, std::stringstream &ss);
    Character *findPlayer(std::string name);
};
