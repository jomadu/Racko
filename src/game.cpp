#include "game.hpp"
#include "human.hpp"
#include "computer.hpp"
#include <random>
#include <algorithm>
#include <iterator>
#include <sstream>

Game::Game() : game_over_(false), turn_(0)
{
    std::random_device rd;
    std::mt19937 g(rd());

    std::vector<int> vals;
    for (auto i = 1; i <= Game::MAX_CARD_VALUE; i++)
    {
        vals.push_back(i);
    }
    std::shuffle(vals.begin(), vals.end(), g);

    for (auto val : vals)
    {
        draw_.push(val);
    }

    auto first_discard = draw_.top();
    draw_.pop();

    discard_.push(first_discard);
}
std::vector<std::shared_ptr<Player>> Game::players() const
{
    return players_;
}
int Game::turn() const
{
    return turn_;
}

void Game::addHuman(const std::string &name)
{
    players_.push_back(std::make_shared<Human>(name));
}
void Game::addComputer(const std::string &name)
{
    players_.push_back(std::make_shared<Computer>(name));
}

void Game::deal()
{
    for (auto i = 0; i < Player::NUM_SLOTS; i++)
    {
        for (auto &player : players_)
        {
            auto card = draw_.top();
            draw_.pop();
            player->slot(i, card);
        }
    }
}
void Game::playTurn()
{
    if (players_.size() > 0)
    {
        if (players_.at(playerTurn())->takeTurn(draw_, discard_))
        {
            game_over_ = true;
        }
        else
        {
            turn_++;
        }
    }
    else
    {
        game_over_ = true;
    }
    if (draw_.size() == 0)
    {
    }
}
bool Game::gameOver() const
{
    return game_over_;
}
int Game::playerTurn() const
{
    return turn_ % players_.size();
}
void Game::restoreDrawFromDiscard()
{
    std::random_device rd;
    std::mt19937 g(rd());

    auto top_discard = discard_.top();
    discard_.pop();

    std::vector<int> vals;
    while (!discard_.empty())
    {
        vals.push_back(discard_.top());
        discard_.pop();
    }
    std::shuffle(vals.begin(), vals.end(), g);

    for (auto val : vals)
    {
        draw_.push(val);
    }
}

std::string Game::toString() const
{
    std::stringstream ss;
    ss << drawToString() << std::endl;
    ss << discardToString() << std::endl;
    ss << playersToString() << std::endl;
    return ss.str();
}
std::string Game::playersToString() const
{
    std::stringstream ss;
    ss << "Game::players_:" << std::endl;
    bool first = true;
    std::string del = "";
    for (auto player : players_)
    {
        if (!first)
        {
            ss << std::endl;
        }
        ss << del << player;
        if (del == "")
        {
            del = ",";
        }
    }
    return ss.str();
}

std::string Game::drawToString() const
{
    std::stringstream ss;
    ss << "Game::draw_: " << pileToString(draw_);
    return ss.str();
}
std::string Game::discardToString() const
{
    std::stringstream ss;
    ss << "Game::discard_: " << pileToString(discard_);
    return ss.str();
}
std::ostream &operator<<(std::ostream &os, const Game &g)
{
    os << g.toString();
    return os;
}
std::string Game::pileToString(const std::stack<int> &pile) const
{
    std::stringstream ss;
    auto pile_cpy = pile;
    std::string del = "";
    while (!pile_cpy.empty())
    {
        auto val = pile_cpy.top();
        pile_cpy.pop();
        ss << del << val;
        if (del == "")
        {
            del = ",";
        }
    }
    return ss.str();
}
