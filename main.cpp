
#include <iostream>
#include "List.hpp"
#include "Item.hpp"
#include "Game.hpp"

int main()
{

    Game game;
    game.loadFromFile("Input.txt");

    // Run game logic based on loaded commands
    game.executeCommands();

    game.outputFinalState("output.txt");

    return 0;
}
