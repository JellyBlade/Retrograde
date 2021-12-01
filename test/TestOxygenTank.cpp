/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/
#include <iostream>

#include "OxygenTank.h"
#include "Game.h"
#include "InteractHelper.h"
#include "gtest/gtest.h"

TEST(TestOxygenTank, interactTest) {
  Game* game = new Game();
  InteractHelper::game = game;
  OxygenTank* o = new OxygenTank();

  EXPECT_FALSE(InteractHelper::getPlayerInventory()->hasSpaceSuit());
  o->interact();

  InteractHelper::getPlayerInventory()->giveSpaceSuit();
  EXPECT_TRUE(InteractHelper::getPlayerInventory()->hasSpaceSuit());
  EXPECT_EQ(InteractHelper::getPlayerInventory()->getOxygen(), 10000);

  InteractHelper::getPlayerInventory()->setOxygen(0);
  EXPECT_EQ(InteractHelper::getPlayerInventory()->getOxygen(), 0);
  o->interact();
  EXPECT_EQ(InteractHelper::getPlayerInventory()->getOxygen(), 10000);

  delete game;
  delete o;
}
