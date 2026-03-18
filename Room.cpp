/*  Noam Eilat : 322713025
    Amit Lachmann : 207448267   */

#include <stdexcept>
#include "Room.hpp"

Room::Room(std::string name)
    : name(name), north(nullptr), south(nullptr), east(nullptr), west(nullptr)
{
    if (name.empty())
    {
        throw std::invalid_argument("Error : Room Name must not be empty");
    }
}

Room::~Room()
{
}

Item *Room::findItem(ItemType itemToFind)
{
    Item *currentBest = nullptr;
    List<Item *>::Node *temp = itemList.head;
    while (temp)
    {
        if (temp->data)
        {
            if (temp->data->getItemType() == itemToFind)
            {
                if (!currentBest)
                {
                    currentBest = temp->data;
                }
                else
                {
                    if (currentBest->getTotalStats()<temp->data->getTotalStats())
                    {
                        currentBest = temp->data;
                    }
                }
            }
        }
        temp = temp->next;
    }
    return currentBest;
}

Monster *Room::findMonster(std::string name)
{
    List<Monster *>::Node *temp = monsters.head;
    while (temp)
    {
        if (temp->data->getMonsterName() == name)
        {
            return temp->data;
        }
        temp = temp->next;
    }
    std::cout << "Error : Monster not found" << std::endl;
    return nullptr;
}
