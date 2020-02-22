#include <iostream>
#include "logger.hpp"
#include "game.hpp"
int main(){
    auto& logger = Logger::instance();

    Game game;
    game.addPlayer("Shaggy");
    game.addPlayer("Scooby");


    game.deal();
    std::cout << "-----" << std::endl;
    std::cout << "Racko" << std::endl;
    std::cout << "-----" << std::endl;
    while (!game.gameOver())
    {
        game.playTurn();
    }

    std::cout << "Game Over!" << std::endl;
    std::cout << game.toString() << std::endl;

    // Singleton cleanup
    Logger::deleteInstance();
}
