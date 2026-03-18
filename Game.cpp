// Noam Eilat : 322713025
// Amit Lachmann : 207448267

#include "Game.hpp"
#include <climits>

using namespace std;

void Game::capitalize(string &str)
{
    if (!str.empty())
    {
        str[0] = toupper(str[0]);

        for (std::size_t i = 1; i < str.length(); ++i)
            str[i] = std::tolower(str[i]);
    }
}
void Game::move(Character *player, Directions whereToMove)
{
    if (!player->getCurrentRoom())
    {
        return;
    }
    
    Room *newRoom = player->getCurrentRoom()->getConnectedRoom(whereToMove);
    if (newRoom)
    {
        player->setCurrentRoom(player->getCurrentRoom()->getConnectedRoom(whereToMove));
        return;
    }
    cout << "The is no room at the requested direction" << endl;
}

void Game::loadFromFile(string fileName)
{
    if (fileName.empty())
    {
        cout << "Error : Invalid file name" << endl;
        exit(1);
    }
    inputFile = ifstream(fileName);
    if (!inputFile)
    {
        cout << "Error : Can't open file" << endl;
        exit(1);
    }
}

void Game::executeCommands()
{
    string line;
    while (getline(inputFile, line))
    {
        if (line.empty() || line.find("//") == 0)
            continue;

        stringstream streamString(line);
        string arg;
        streamString >> arg;
        if (arg == "" || arg == " ")
            continue;
        capitalize(arg);
        if (arg == "Create")
        {
            try
            {
                handleCreate(streamString);
            }
            catch (const std::exception &e)
            {
                e.what();
            }
        }
        else if (arg == "Set")
        {
            try
            {
                handleSet(streamString);
            }
            catch (exception &e)
            {
                e.what();
            }
        }
        else if (arg == "Connect")
        {
            try
            {
                handleConnect(streamString);
            }
            catch (const std::exception &e)
            {
                e.what();
            }
        }
        else if (arg == "Place")
        {
            try
            {
                handlePlace(streamString);
            }
            catch (const std::exception &e)
            {
                e.what();
            }
        }
        else if (arg == "Enter")
        {
            try
            {
                handleEnter(streamString);
            }
            catch (const std::exception &e)
            {
                e.what();
            }
        }
        else if (arg == "Move")
        {
            handleMove(streamString);
        }
        else if (arg == "Fight")
        {
            handleFight(streamString);
        }
        else if (arg == "Pickup")
        {
            handlePickUp(streamString);
        }
        else
        {
            cout << "Error : Invalid command" << endl;
        }
        streamString.str("");
        streamString.clear();
    }
}

void Game::outputFinalState(std::string fileOutputName)
{
    ofstream outputFile(fileOutputName);
    if (!outputFile.is_open())
    {
        cout << "Error : Couldn't open output file" << endl;
        return;
    }
    List<Character *>::Node *temp = players.head;
    while (temp)
    {
        Item *item1 = temp->data->getFirstItem();
        Item *item2 = temp->data->getSecondItem();
        outputFile << temp->data->getCharacterName() << " final stats: Health " << temp->data->getCharacterHealth() << " Strength: " << temp->data->getCharacterStrength() << " Defense: " << temp->data->getCharacterDefense() << endl;
        if (item1 && item2)
        {
            outputFile << item1->getName() << ": " << item1->getItemHealthBonus() << "/" << item1->getItemStrengthBonus() << "/" << item1->getItemDefenseBonus() << endl;
            outputFile << item2->getName() << ": " << item2->getItemHealthBonus() << "/" << item2->getItemStrengthBonus() << "/" << item2->getItemDefenseBonus() << endl;
        }
        else if (item1)
        {
            outputFile << item1->getName() << ": " << item1->getItemHealthBonus() << "/" << item1->getItemStrengthBonus() << "/" << item1->getItemDefenseBonus() << endl;
        }
        else if (item2)
        {
            outputFile << item2->getName() << ": " << item2->getItemHealthBonus() << "/" << item2->getItemStrengthBonus() << "/" << item2->getItemDefenseBonus() << endl;
        }
        else
        {
            outputFile << temp->data->getCharacterName() << " had no items (and still won eze gever nishba)!" << endl;
        }
        temp = temp->next;
    }
}

FightResult Game::fight(Character *player, Monster *foulBeing)
{
    while (player->getCharacterHealth() > 0 && foulBeing->getMonsterHealth() > 0)
    {
        player->attack(*foulBeing);
        if (foulBeing->getMonsterHealth() > 0)
        {
            foulBeing->attack(*player);
        }
        else
        {
            return VICTORY;
        }
    }
    return LOSE;
}

void Game::handleCreate(stringstream &ss)
{
    string arg2, arg3;
    ss >> arg2;
    ss >> arg3;
    if (arg2 == "Room")
    {
        dungeon.createRoom(arg3);
    }
    else if (arg2 == "Warrior")
    {
        Warrior *PC = new Warrior(arg3);
        players.insertEnd(PC);
    }
    else if (arg2 == "Thief")
    {
        Thief *PC = new Thief(arg3);
        players.insertEnd(PC);
    }
    else if (arg2 == "Mage")
    {
        Mage *PC = new Mage(arg3);
        players.insertEnd(PC);
    }
}

void Game::handleSet(stringstream &ss)
{
    string arg2, arg3;
    ss >> arg2;
    ss >> arg3;
    Room *tempStart = dungeon.findRoom(arg3);
    if (!tempStart)
    {
        std::cout << "Error : Start room could not be found" << std::endl;
        return;
    }
    else
    {
        dungeon.setStartRoom(tempStart);
    }
}

void Game::handleConnect(stringstream &ss)
{
    string arg2, arg3, arg4;
    ss >> arg2;
    ss >> arg3;
    ss >> arg4;
    Directions direction = ALL_BLUE;
    if (arg4 == "North")
    {
        direction = NORTH;
    }
    else if (arg4 == "South")
    {
        direction = SOUTH;
    }
    else if (arg4 == "East")
    {
        direction = EAST;
    }
    else if (arg4 == "West")
    {
        direction = WEST;
    }
    if (direction == ALL_BLUE)
    {
        std::cout << "Error : Invalid direction" << std::endl;
        return;
    }
    else
    {
        dungeon.connectRoom(arg2, arg3, direction);
    }
}

void Game::handlePlace(stringstream &ss)
{
    string arg2;
    ss >> arg2;
    if (arg2 == "Monster")
    {
        handlePlaceMonster(ss);
    }
    else
    {
        handlePlaceItem(arg2, ss);
    }
}

void Game::handleEnter(stringstream &ss)
{
    string arg2, arg3;
    ss >> arg2;
    ss >> arg3;
    if (arg2 != "Dungeon")
    {
        cout << "Error : Not a valid location to enter" << endl;
        return;
    }
    Character *player = findPlayer(arg3);
    if (!player)
    {
        cout << "Error : No existing player to enter the dungeon" << endl;
        return;
    }
    if (!dungeon.getStartRoom())
    {
        cout << "Error : Can't enter the dungeon, no start room available" << endl;
        return;
    }

    player->setCurrentRoom(dungeon.getStartRoom());
    cout << player->getCharacterName() << " has entered the dungeon" << endl;
}

void Game::handleMove(stringstream &ss)
{
    string arg2, arg3;
    ss >> arg2;
    ss >> arg3;
    Character *player = findPlayer(arg2);
    if (!player)
    {
        cout << "Error : No existing player to move" << endl;
        return;
    }
    Directions whereToMove;
    if (arg3 == "North")
    {
        whereToMove = NORTH;
    }
    else if (arg3 == "South")
    {
        whereToMove = SOUTH;
    }
    else if (arg3 == "East")
    {
        whereToMove = EAST;
    }
    else if (arg3 == "West")
    {
        whereToMove = WEST;
    }
    else
    {
        cout << "Error : Invalid direction to move to" << endl;
        return;
    }
    if (!player->getCurrentRoom())
    {
        return;
    }
    if (player->getCurrentRoom()->getConnectedRoom(whereToMove))
    {
        move(player, whereToMove);
        cout << player->getCharacterName() << " has moved " << arg3 << " to the " << player->getCurrentRoom()->getName() << endl;
    }
    else
    {
        cout << "Error : No room connected in this direction" << endl;
        return;
    }
}

void Game::handleFight(stringstream &ss)
{
    string arg2, arg3;
    ss >> arg2;
    ss >> arg3;
    Character *fightingPlayer = findPlayer(arg2);
    if (!fightingPlayer)
    {
        return;
    }
    if (!fightingPlayer->getCurrentRoom())
    {
        return;
    }
    Monster *fightingMonster = fightingPlayer->getCurrentRoom()->findMonster(arg3);
    if (fightingPlayer && fightingMonster)
    {
        FightResult result = fight(fightingPlayer, fightingMonster);
        if (result == LOSE)
        {
            cout << fightingPlayer->getCharacterName() << " was defeated by " << fightingMonster->getMonsterName() << endl;
            players.remove(fightingPlayer);
        }
        else
        {
            cout << fightingPlayer->getCharacterName() << " was triumphant over the " << fightingMonster->getMonsterName() << endl;
        }
    }
}

void Game::handlePickUp(stringstream &ss)
{
    string arg2, arg3;
    ss >> arg2;
    ss >> arg3;
    Character *player = findPlayer(arg2);
    if (!player)
    {
        cout << "Error : Invalid player to pick up item" << endl;
        return;
    }
    if (!player->getCurrentRoom())
    {
        return;
    }
    if (arg3 == "Sword")
    {
        Item *itemToPickUp = player->getCurrentRoom()->findItem(SWORD);
        if (itemToPickUp)
        {
            cout << player->getCharacterName() << " is trying to pick up " << itemToPickUp->getName() << endl;
            bool result = player->pickUp(itemToPickUp);
            if(result)
            {
                player->getCurrentRoom()->getItems().deleteNode(itemToPickUp);
            }
        }
        else
        {
            cout << "Error : No sword in the room" << endl;
            return;
        }
    }
    else if (arg3 == "Shield")
    {
        Item *itemToPickUp = player->getCurrentRoom()->findItem(SHIELD);
        if (itemToPickUp)
        {
            cout << player->getCharacterName() << " is trying to pick up " << itemToPickUp->getName() << endl;
            bool result = player->pickUp(itemToPickUp);
            if(result)
            {
                player->getCurrentRoom()->getItems().deleteNode(itemToPickUp);
            }
        }
        else
        {
            cout << "Error : No shield in the room" << endl;
            return;
        }
    }
    else if (arg3 == "Dagger")
    {
        Item *itemToPickUp = player->getCurrentRoom()->findItem(DAGGER);
        if (itemToPickUp)
        {
            cout << player->getCharacterName() << " is trying to pick up " << itemToPickUp->getName() << endl;
            bool result = player->pickUp(itemToPickUp);
            if(result)
            {
                player->getCurrentRoom()->getItems().deleteNode(itemToPickUp);
            }
        }
        else
        {
            cout << "Error : No dagger in the room" << endl;
            return;
        }
    }
    else if (arg3 == "Wand")
    {
        Item *itemToPickUp = player->getCurrentRoom()->findItem(WAND);
        if (itemToPickUp)
        {
            cout << player->getCharacterName() << " is trying to pick up " << itemToPickUp->getName() << endl;
            bool result = player->pickUp(itemToPickUp);
            if(result)
            {
                player->getCurrentRoom()->getItems().deleteNode(itemToPickUp);
            }
        }
        else
        {
            cout << "Error : No wand in the room" << endl;
            return;
        }
    }
    else if (arg3 == "Health" || arg3 == "Strength" || arg3 == "Defense")
    {
        string arg4;
        ss >> arg4;
        if (arg4 != "Potion")
        {
            cout << "Error : Invalid item to pick up" << endl;
            return;
        }
        if (arg3 == "Health")
        {
            Item *itemToPickUp = player->getCurrentRoom()->findItem(POTIONHP);
            if (!itemToPickUp)
            {
                cout << "Error : No potion in the room" << endl;
                return;
            }
            else
            {
                Potion *temp = dynamic_cast<Potion *>(itemToPickUp);
                if (temp->getPotionType() != HEALTHP)
                {
                    cout << "Error : No such potion in the room" << endl;
                    return;
                }
                cout << player->getCharacterName() << " is drinking the " << itemToPickUp->getName() << endl;
                player->drinkPotion(itemToPickUp);   
            }
        }
        else if (arg3 == "Strength")
        {
            Item *itemToPickUp = player->getCurrentRoom()->findItem(POTIONSTR);
            if (!itemToPickUp)
            {
                cout << "Error : No potion in the room" << endl;
                return;
            }
            else
            {
                Potion *temp = dynamic_cast<Potion *>(itemToPickUp);
                if (temp->getPotionType() != STRENGTHP)
                {
                    cout << "Error : No such potion in the room" << endl;
                    return;
                }
                cout << player->getCharacterName() << " is drinking the " << itemToPickUp->getName() << endl;
                player->drinkPotion(itemToPickUp);
            }
        }
        else if (arg3 == "Defense")
        {
            Item *itemToPickUp = player->getCurrentRoom()->findItem(POTIONDEF);
            if (!itemToPickUp)
            {
                cout << "Error : No potion in the room" << endl;
                return;
            }
            else
            {
                Potion *temp = dynamic_cast<Potion *>(itemToPickUp);
                if (temp->getPotionType() != DEFENSEP)
                {
                    cout << "Error : No such potion in the room" << endl;
                    return;
                }
                cout << player->getCharacterName() << " is drinking the " << itemToPickUp->getName() << endl;
                player->drinkPotion(itemToPickUp);
            }
        }
    }
    else
    {
        cout << "Error : Invalid item to pick up" << endl;
        return;
    }
}

void Game::handlePlaceMonster(stringstream &ss)
{
    string arg3, arg4;
    int arg5 = -1, arg6 = -1, arg7 = -1;
    ss >> arg3;
    ss >> arg4;
    ss >> arg5;
    ss >> arg6;
    ss >> arg7;
    Room *temp = dungeon.findRoom(arg4);
    if (!temp)
    {
        cout << "Error : No such room was found" << endl;
        return;
    }

    if (arg5 < 0 || arg6 < 0 || arg7 < 0)
    {
        cout << "Error : Invalid stats for monster" << endl;
        return;
    }
    Monster *monsterToAdd = new Monster(arg3, arg5, arg6, arg7);
    if (!monsterToAdd)
    {
        cout << "Error : Out of memory while creating monster" << endl;
        return;
    }
    temp->placeMonster(monsterToAdd);
}

void Game::handlePlaceItem(string arg2, stringstream &ss)
{
    string arg3;
    int arg4 = INT_MIN, arg5 = INT_MIN, arg6 = INT_MIN;
    if (arg2 == "Sword")
    {
        ss >> arg3;
        ss >> arg4;
        ss >> arg5;
        ss >> arg6;
        if (arg4 == INT_MIN || arg5 == INT_MIN || arg6 == INT_MIN)
        {
            cout << "Error : Invalid line input" << endl;
        } 
        Room *roomToPlace = dungeon.findRoom(arg3);
        if (!roomToPlace)
        {
            cout << "Error : No such room was found" << endl;
            return;
        }
        Sword *swordToAdd = new Sword(arg4, arg5, arg6);
        roomToPlace->placeItem(swordToAdd);
    }
    else if (arg2 == "Shield")
    {
        ss >> arg3;
        ss >> arg4;
        ss >> arg5;
        ss >> arg6;
        if (arg4 == INT_MIN || arg5 == INT_MIN || arg6 == INT_MIN)
        {
            cout << "Error : Invalid line input" << endl;
        }
        Room *roomToPlace = dungeon.findRoom(arg3);
        if (!roomToPlace)
        {
            cout << "Error : No such room was found" << endl;
            return;
        }
        Shield *shieldToAdd = new Shield(arg4, arg5, arg6);
        roomToPlace->placeItem(shieldToAdd);
    }
    else if (arg2 == "Dagger")
    {
        ss >> arg3;
        ss >> arg4;
        ss >> arg5;
        ss >> arg6;
        if (arg4 == INT_MIN || arg5 == INT_MIN || arg6 == INT_MIN)
        {
            cout << "Error : Invalid line input" << endl;
        }
        Room *roomToPlace = dungeon.findRoom(arg3);
        if (!roomToPlace)
        {
            cout << "Error : No such room was found" << endl;
            return;
        }
        Dagger *daggerToAdd = new Dagger(arg4, arg5, arg6);
        roomToPlace->placeItem(daggerToAdd);
    }
    else if (arg2 == "Wand")
    {
        ss >> arg3;
        ss >> arg4;
        ss >> arg5;
        ss >> arg6;
        if (arg4 == INT_MIN || arg5 == INT_MIN || arg6 == INT_MIN)
        {
            cout << "Error : Invalid line input" << endl;
        }
        Room *roomToPlace = dungeon.findRoom(arg3);
        if (!roomToPlace)
        {
            cout << "Error : No such room was found" << endl;
            return;
        }
        Wand *wandToAdd = new Wand(arg4, arg5, arg6);
        roomToPlace->placeItem(wandToAdd);
    }
    else if (arg2 == "Strength" || arg2 == "Health" || arg2 == "Defense")
    {
        string arg3, arg4;
        int arg5, arg6, arg7;
        ss >> arg3;
        ss >> arg4;
        ss >> arg5;
        ss >> arg6;
        ss >> arg7;
        if (arg7 == INT_MIN || arg5 == INT_MIN || arg6 == INT_MIN)
        {
            cout << "Error : Invalid line input" << endl;
        }
        Room *roomToPlace = dungeon.findRoom(arg4);
        if (!roomToPlace)
        {
            cout << "Error : No such room was found" << endl;
            return;
        }
        Potion *potionToAdd = new Potion(arg2, arg5, arg6, arg7);
        roomToPlace->placeItem(potionToAdd);
    }
    else
    {
        cout << "Error : Trying to place an invalid item" << endl;
    }
}

Character *Game::findPlayer(std::string name)
{
    List<Character *>::Node *temp = players.head;
    while (temp)
    {
        if (temp->data->getCharacterName() == name)
        {
            return temp->data;
        }
        temp = temp->next;
    }
    cout << "Error : Player not found" << endl;
    return nullptr;
}
