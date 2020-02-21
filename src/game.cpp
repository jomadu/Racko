#include "game.hpp"

Game::Game() : turn_(0)
{

}
std::vector<Player> Game::players() const
{
    return players_;
}
int Game::turn() const
{
    return turn_;
}

void Game::addPlayer(const std::string& name)
{
    players_.emplace_back(name);
}
void Game::playTurn()
{
    turn_ ++;    
}
bool Game::gameOver() const
{
    return turn_ >= 10;
}
int Game::playerTurn() const
{
    return turn_ % players_.size();
}
std::string Game::toString() const
{
    return "Game State! :)";
}
