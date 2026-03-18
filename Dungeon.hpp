/*  Noam Eilat : 322713025
    Amit Lachmann : 207448267   */

#pragma once

#include "Room.hpp"
#include "List.hpp"

#define DUNGEON_SIZE 5

class Dungeon
{
private:
    Room *startRoom;
    List<Room*> rooms;

public:
    // Constructors / Destructor
    Dungeon();
    ~Dungeon();

    // Main Functions
    void createRoom(std::string name);
    void connectRoom(std::string baseName, std::string connectionName, Directions whereToConnect);
    Room *findRoom(std::string name);
    void matchPairDirections(Room* baseRoom,Room* roomToConnect,Directions whereToConnect);

    // Getters / Setters
    inline Room *getStartRoom() const
    {
        return this->startRoom;
    }
    inline void setStartRoom(Room *room)
    {
        this->startRoom = room;
    }
};
