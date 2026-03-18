/*  Noam Eilat : 322713025
    Amit Lachmann : 207448267   */

#include "Dungeon.hpp"
#include "List.hpp"
#include <stdexcept>

Dungeon::Dungeon() : startRoom(nullptr)
{
}

Dungeon::~Dungeon()
{
}

void Dungeon::createRoom(std::string name)
{
    if (name.empty())
    {
        throw std::invalid_argument("Error: Invalid name in createRoom");
    }
    Room *newRoom = new Room(name);
    if (!newRoom)
    {
        throw std::runtime_error("Error: Out of memory in createRoom");
    }
    rooms.insertEnd(newRoom);
}

void Dungeon::matchPairDirections(Room *baseRoom, Room *roomToConnect, Directions whereToConnect)
{
    switch (whereToConnect)
    {
    case NORTH:
        baseRoom->connectNorth(roomToConnect);
        roomToConnect->connectSouth(baseRoom);
        break;

    case SOUTH:
        baseRoom->connectSouth(roomToConnect);
        roomToConnect->connectNorth(baseRoom);
        break;

    case EAST:
        baseRoom->connectEast(roomToConnect);
        roomToConnect->connectWest(baseRoom);
        break;

    case WEST:
        baseRoom->connectWest(roomToConnect);
        roomToConnect->connectEast(baseRoom);
        break;

    default:
        std::cout << "all blue is real! I believe in it" << std::endl;
        break;
    }
}

void Dungeon::connectRoom(std::string baseName, std::string connectionName, Directions whereToConnect)
{
    Room *baseRoom = findRoom(baseName);
    Room *roomToConnect = findRoom(connectionName);
    if (!baseRoom || !roomToConnect)
    {
        throw std::invalid_argument("Error: room doesnt exist in connectRoom");
    }
    matchPairDirections(baseRoom, roomToConnect, whereToConnect);
}

Room *Dungeon::findRoom(std::string name)
{
    List<Room *>::Node *temp = rooms.head;
    while (temp)
    {
        if (temp->data->getName() == name)
        { 
            return temp->data;
        }
        temp = temp->next;
    }
    return nullptr;
}
