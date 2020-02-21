#include <iostream>
#include "logger.hpp"
#include "game.hpp"
int main(){
    auto& logger = Logger::instance();

    logger.log(Logger::LogLevel::INFO, "Hello World!");

    Game game;
    game.addPlayer("Shaggy");
    game.addPlayer("Scooby");

    while (!game.gameOver())
    {
        std::cout << "game.turn_: " << game.turn() << std::endl;
        game.playTurn();
    }

    std::cout << game.toString() << std::endl;

    // Singleton cleanup
    Logger::deleteInstance();
}
