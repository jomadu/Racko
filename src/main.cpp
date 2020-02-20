#include <iostream>
#include "logger.hpp"

int main(){
    auto& logger = Logger::instance();

    logger.log(Logger::LogLevel::INFO, "Hello World!");

    // Singleton cleanup
    Logger::deleteInstance();
}
