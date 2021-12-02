/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include "InteractHelper.h"
#include "AirLock.h"
#include "gtest/gtest.h"

TEST(TestAirLock, interactTest) {
  Game* game = new Game();
  InteractHelper::game = game;
  AirLock* a = AirLock(5000);

  EXPECT_EQ(a->isSolved(), false);
  a->interact();
  EXPECT_EQ(a->isSolved(), false);
  InteractHelper::getPlayerInventory()->giveSpaceSuit();
  InteractHelper::getPlayerHandler()->getPlayer()->getCurrentRoom()
  ->setRoomOxygen(0)
  a->interact();
  EXPECT_EQ(a->isSolved(), false);
  InteractHelper::getPlayerHandler()->getPlayer()->getCurrentRoom()
  ->setRoomOxygen(1000);
  a->interact();
  EXPECT_EQ(a->isSolved(), true);

  delete game;
  delete a;
}
