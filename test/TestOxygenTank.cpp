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
  OxygenTank* o = new OxygenTank("test", "test", true);
  Room* r = new Room();
  InteractHelper::getPlayerHandler()->getPlayer()->setCurrentRoom(r);

  r->addObject(o);
  r->setRoomOxygen(5000);
  EXPECT_EQ(r->getRoomOxygen(), 5000);
  o->interact();
  EXPECT_EQ(r->getRoomOxygen(), 10000);
  EXPECT_FALSE(InteractHelper::getPlayerInventory()->hasSpaceSuit());

  InteractHelper::getPlayerInventory()->giveSpaceSuit();
  InteractHelper::getPlayerInventory()->addObject(o);
  EXPECT_TRUE(InteractHelper::getPlayerInventory()->hasSpaceSuit());
  EXPECT_TRUE(InteractHelper::getPlayerInventory()->isObjectInContainer(o));
  EXPECT_EQ(InteractHelper::getPlayerInventory()->getOxygen(), 10000);

  InteractHelper::getPlayerInventory()->setOxygen(0);
  EXPECT_EQ(InteractHelper::getPlayerInventory()->getOxygen(), 0);
  std::cout << "Testing if it gets past interact" << std::endl;
  o->interact();
  std::cout << "Yes it did" << std::endl;
  EXPECT_EQ(InteractHelper::getPlayerInventory()->getOxygen(), 10000);

  delete game;
  std::cout << "Testing if its delete r function" << std::endl;
  std::cout << "Testing if it gets function" << std::endl;
}
