#include "gtest/gtest.h"
#include "logger.hpp"
#include "game.hpp"
#include "human.hpp"
#include <string>

class GameTest : public ::testing::Test
{
protected:
  Game game_;
};
TEST_F(GameTest, addSingleHumanPlayer)
{
  std::string name = "Player1";
  game_.addPlayer<Human>(name);
  auto players = game_.players();

  EXPECT_EQ(players.size(), 1);
  EXPECT_EQ(players.at(0)->name(), name);
}
TEST_F(GameTest, addMultipleHumanPlayers)
{
  std::vector<std::string> names = {"Player1", "Player2"};
  for (auto name : names)
  {
    game_.addPlayer<Human>(name);
  }
  auto players = game_.players();

  EXPECT_EQ(players.size(), names.size());
  for (auto i = 0; i < names.size(); i++)
  {
    EXPECT_EQ(players.at(i)->name(), names.at(i));
  }
}
