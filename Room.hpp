/*  Noam Eilat : 322713025
    Amit Lachmann : 207448267   */

#pragma once

#include <string>
#include "Item.hpp"
#include "Monster.hpp"
#include "List.hpp"

typedef enum Directions_E
{
    NORTH,
    SOUTH,
    EAST,
    WEST,
    ALL_BLUE,
} Directions;

class Room
{
private:
    std::string name;
    List<Item *> itemList;
    List<Monster *> monsters;
    Room *north;
    Room *south;
    Room *east;
    Room *west;

public:
    // Constructors / Destructor
    Room(std::string name);
    ~Room();

    Item *findItem(ItemType itemToFind);

    inline virtual void removeItemFromList(Item* itemToRemove) {itemList.remove(itemToRemove);}

    // Getters / Setters
    inline std::string getName() const
    {
        return this->name;
    }
    inline void setName(std::string newName)
    {
        this->name = newName;
    }
    inline void placeItem(Item *item)
    {
        itemList.insertEnd(item);
    }
    inline List<Item *>& getItems()
    {
        return itemList;
    }
    inline void placeMonster(Monster *monster)
    {
        monsters.insertEnd(monster);
    }
    Monster *findMonster(std::string name);
    inline Room *getConnectedRoom(Directions direction)
    {
        switch (direction)
        {
        case NORTH:
            return north;
            break;

        case SOUTH:
            return south;
            break;

        case EAST:
            return east;
            break;

        case WEST:
            return west;
            break;

        default:
            return nullptr;
            break;
        }
    }
    inline void connectNorth(Room *room)
    {
        this->north = room;
    }
    inline void connectSouth(Room *room)
    {
        this->south = room;
    }
    inline void connectEast(Room *room)
    {
        this->east = room;
    }
    inline void connectWest(Room *room)
    {
        this->west = room;
    }
};
