// Noam Eilat : 322713025
// Amit Lachmann : 207448267

#include <iostream>
#include "List.hpp"
#include "Item.hpp"
#include "Game.hpp"

int main()
{

    Game game;
    game.loadFromFile("nivInput.txt");

    // Run game logic based on loaded commands
    game.executeCommands();

    game.outputFinalState("output.txt");

    return 0;
}