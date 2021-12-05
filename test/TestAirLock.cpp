/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <fstream>

#include "InteractHelper.h"
#include "AirLock.h"
#include "gtest/gtest.h"

TEST(TestAirLock, interactTest) {
  Game* game = new Game();
  InteractHelper::game = game;
  Room* r = new Room();
  AirLock* a = new AirLock("fake airlck", "test", true, 5000);
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
  ->setRoomOxygen(10000);
  a->interact();
  EXPECT_EQ(a->isPuzzleSolved(), true);

  delete game;
  delete a;
  delete r;
}

TEST(TestAirLock, solvedTextTest) {
  Game* game = new Game();
  InteractHelper::game = game;
  Room* r = new Room();
  AirLock* a = new AirLock("test", "test", true, 5000);
  std::ifstream file("test/text/puzzleTest_input.txt");
  InteractHelper::getPlayerHandler()->getPlayer()->setCurrentRoom(r);

  EXPECT_EQ(a->isPuzzleSolved(), false);
  a->playerInput(file);
  EXPECT_EQ(a->isPuzzleSolved(), false);
  a->playerInput(file);
  InteractHelper::getPlayerInventory()->giveSpaceSuit();
  InteractHelper::getPlayerHandler()->getPlayer()->getCurrentRoom()
  ->setRoomOxygen(0);
  a->playerInput(file);
  EXPECT_EQ(a->isPuzzleSolved(), false);
  InteractHelper::getPlayerHandler()->getPlayer()->getCurrentRoom()
  ->setRoomOxygen(10000);
  a->playerInput(file);
  EXPECT_EQ(a->isPuzzleSolved(), true);
  a->playerInput(file);

  delete game;
  delete a;
  delete r;
}
