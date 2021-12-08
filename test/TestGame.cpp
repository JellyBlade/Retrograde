/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <string>

#include "Game.h"
#include "TextHelper.h"
#include "InteractHelper.h"
#include "gtest/gtest.h"

TEST(TestGame, playTest) {
  Game* game = new Game();
  InteractHelper::game = game;
  TextHelper::rgScriptGlobalFlags["win"] = true;
  game->play();
  TextHelper::rgScriptGlobalFlags.clear();
  TextHelper::rgScriptGlobalFlags["lose"] = true;
  game->play();
  TextHelper::rgScriptGlobalFlags["asphyxiated"] = true;
  game->play();
  TextHelper::rgScriptGlobalFlags["asphyxiated"] = false;
  TextHelper::rgScriptGlobalFlags["sucked into space"] = true;
  game->play();

  delete game;
}

TEST(TestGame, generateTest) {
  Game* game = new Game();
  InteractHelper::game = game;
  game->generateMap();
  game->generateNPCs();

  EXPECT_TRUE(game->getMap()->getRoom("recreation center") != nullptr);
  EXPECT_TRUE(InteractHelper::getNPC("joe") != nullptr);

  delete game;
}
