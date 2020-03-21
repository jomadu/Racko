#include <iostream>
#include "logger.hpp"
#include "game.hpp"
#include "computer.hpp"
#include "human.hpp"

int main()
{
    auto &logger = Logger::instance();

    Game game;
    game.addPlayer<Computer>("Zoidberg");
    game.addPlayer<Human>("Max");
    game.addPlayer<Human>("Becca");

    game.deal();
    std::cout << "--------------------------------" << std::endl;
    std::cout << " ____   __    ___  __ _  __   _ " << std::endl;
    std::cout << "(  _ \\ / _\\  / __)(  / )/  \\ / \\" << std::endl;
    std::cout << " )   //    \\( (__  )  ((  O )\\_/" << std::endl;
    std::cout << "(__\\_)\\_/\\_/ \\___)(__\\_)\\__/ (_)" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    while (!game.gameOver())
    {
        game.playTurn();
    }

    std::cout << "------------------------" << std::endl;
    std::cout << "  ___   __   _  _  ____ " << std::endl;
    std::cout << " / __) / _\\ ( \\/ )(  __)" << std::endl;
    std::cout << "( (_ \\/    \\/ \\/ \\ ) _) " << std::endl;
    std::cout << " \\___/\\_/\\_/\\_)(_/(____)" << std::endl;
    std::cout << "  __   _  _  ____  ____ " << std::endl;
    std::cout << " /  \\ / )( \\(  __)(  _ \\" << std::endl;
    std::cout << "(  O )\\ \\/ / ) _)  )   /" << std::endl;
    std::cout << " \\__/  \\__/ (____)(__\\_)" << std::endl;
    std::cout << "------------------------" << std::endl;


    std::cout << game.toString() << std::endl;

    // Singleton cleanup
    Logger::deleteInstance();
}
