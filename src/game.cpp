#include "game.hpp"
#include "human.hpp"
#include "computer.hpp"
#include "utils.hpp"
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

void Game::createPlayers()
{
    std::string action = "";
    std::cout << Utils::h1("Create Players") << std::endl;
    while (action != "Begin Game")
    {
        std::stringstream prompt_ss;
        if (players_.size())
        {
            prompt_ss << Utils::h2("Players:") << std::endl;
            for (auto i = 0; i < players_.size(); i++)
            {
                prompt_ss << i << ". " << players_.at(i)->name() << std::endl;
            }
            prompt_ss << std::endl;
        }
        prompt_ss << "Choose an Action:";

        action = std::get<2>(Utils::optionsMenu(
            prompt_ss.str(),
            {"Create Player", "Remove Player", "Update Player Name", "Begin Game"}));
        if (action == "Create Player")
        {
            createPlayer();
        }
        else if (action == "Remove Player")
        {
            removePlayer();
        }
        else if (action == "Update Player Name")
        {
            updatePlayerName();
        }
    }
}
void Game::createPlayer()
{
    std::cout << Utils::h1("Create Player") << std::endl;
    auto player_type = std::get<2>(Utils::optionsMenu("Select player type:", std::vector<std::string>({"Human", "Computer"})));
    auto player_name = Utils::validatedStringInput("Enter player name:", ".*");
    if (player_type == "Human")
    {
        std::cout << "Adding Human player with name " << player_name << std::endl;
        addPlayer<Human>(player_name);
    }
    else if (player_type == "Computer")
    {
        std::cout << "Adding Computer player with name " << player_name << std::endl;
        addPlayer<Computer>(player_name);
    }
}
void Game::removePlayer()
{
    if (players_.size() == 0)
    {
        std::cout << "No players to remove!" << std::endl;
        return;
    }
    std::vector<std::string> options;
    for (auto i = 0; i < players_.size(); i++)
    {
        auto player = players_.at(i);
        options.push_back(player->name());
    }
    std::cout << Utils::h1("Remove Player") << std::endl;
    auto selection = Utils::optionsMenu("Select player to remove:", options);
    auto player_index = std::get<0>(selection);
    auto player_name = std::get<2>(selection);
    players_.erase(players_.begin() + player_index);
    std::cout << "Removed " << player_name << " from players" << std::endl;
}

void Game::updatePlayerName()
{
    if (players_.size() == 0)
    {
        std::cout << "No players to update!" << std::endl;
        return;
    }

    std::vector<std::string> options;
    for (auto i = 0; i < players_.size(); i++)
    {
        auto player = players_.at(i);
        options.push_back(player->name());
    }
    std::cout << Utils::h1("Update Player Name") << std::endl;
    auto selection = Utils::optionsMenu("Select player to update:", options);
    auto player_index = std::get<0>(selection);
    auto player_name = std::get<2>(selection);

    auto new_player_name = Utils::validatedStringInput("Enter new player name:", ".*");
    players_.at(player_index)->name(new_player_name);

    std::cout << "Updated player name \"" << player_name << "\" -> \"" << new_player_name << "\"" << std::endl;
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
        restoreDrawFromDiscard();
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
    ss << "Players:" << std::endl;
    if (players_.size())
    {
        bool first = true;
        std::string del = "";
        for (auto player : players_)
        {
            if (!first)
            {
                ss << std::endl;
            }
            ss << player->toString();
            first = false;
        }
    }
    else
    {
        ss << "No players";
    }
    return ss.str();
}

std::string Game::drawToString() const
{
    std::stringstream ss;
    ss << "Draw Pile: " << pileToString(draw_);
    return ss.str();
}
std::string Game::discardToString() const
{
    std::stringstream ss;
    ss << "Discard Pile: " << pileToString(discard_);
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
