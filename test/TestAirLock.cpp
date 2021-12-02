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
  Room* r = new Room();
  AirLock* a = new AirLock("test", "test", false, 5000);
  InteractHelper::getPlayerHandler()->getPlayer()->setCurrentRoom(r);

  EXPECT_EQ(a->isPuzzleSolved(), false);
  a->interact();
  EXPECT_EQ(a->isPuzzleSolved(), false);
  InteractHelper::getPlayerInventory()->giveSpaceSuit();
  InteractHelper::getPlayerHandler()->getPlayer()->getCurrentRoom()
  ->setRoomOxygen(0);
  a->interact();
  EXPECT_EQ(a->isPuzzleSolved(), false);
  InteractHelper::getPlayerHandler()->getPlayer()->getCurrentRoom()
  ->setRoomOxygen(1000);
  a->interact();
  EXPECT_EQ(a->isPuzzleSolved(), true);

  delete game;
  delete a;
}
