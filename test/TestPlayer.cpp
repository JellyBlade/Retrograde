/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <string>

#include "Player.h"
#include "Room.h"
#include "Door.h"
#include "gtest/gtest.h"

TEST(TestPlayer, playerNameTest) {
  Player* p = new Player();

  EXPECT_EQ(p->getPlayerName(), "");

  p->setPlayerName("P. Sherman");
  EXPECT_EQ(p->getPlayerName(), "P. Sherman");

  p->setPlayerName("Wallaby-42");
  EXPECT_NE(p->getPlayerName(), "P. Sherman");
  EXPECT_NE(p->getPlayerName(), "Sydney Way");
  EXPECT_EQ(p->getPlayerName(), "Wallaby-42");

  std::string name = "Joey 'Big Boy' Kerman";
  p->setPlayerName(name);
  EXPECT_EQ(p->getPlayerName(), name);
  EXPECT_EQ(p->getPlayerName(), "Joey 'Big Boy' Kerman");
  EXPECT_NE(p->getPlayerName(), "Wallaby-42");

  delete p;
}

TEST(TestPlayer, spaceSuitTest) {
  Player* p = new Player();

  EXPECT_FALSE(p->hasSpaceSuit());
  EXPECT_EQ(p->getInventory()->getOxygen(), 0);

  p->getInventory()->giveSpaceSuit();

  EXPECT_TRUE(p->hasSpaceSuit());
  EXPECT_EQ(p->getInventory()->getOxygen(), 10000);

  p->getInventory()->setOxygen(5000);

  EXPECT_EQ(p->getInventory()->getOxygen(), 5000);

  delete p;
}

TEST(TestPlayer, roomTest) {
  Player* p = new Player();
  Room* r1 = new Room("Blank Room", "It's completely empty.");
  Room* r2 = new Room("Testing Room", "It's a room for testing stuff. Cool.");

  p->setCurrentRoom(r1);
  EXPECT_NE(p->getCurrentRoom(), nullptr);
  EXPECT_EQ(p->getCurrentRoom(), r1);
  EXPECT_NE(p->getCurrentRoom(), r2);
  EXPECT_EQ(p->getCurrentRoom()->getName(), r1->getName());
  EXPECT_NE(p->getCurrentRoom()->getName(), r2->getName());
  EXPECT_EQ(p->getCurrentRoom()->getDescription(), r1->getDescription());
  EXPECT_NE(p->getCurrentRoom()->getDescription(), r2->getDescription());

  delete p;
  delete r1;
  delete r2;
}

TEST(TestPlayer, oxygenTest) {
  Player* p = new Player();
  Room* r1 = new Room("Blank Room", "It's completely empty.");
  Room* r2 = new Room("Testing Room", "It's a room for testing stuff. Cool.");
  Door* d1 = new Door(r1, r2);

  p->setCurrentRoom(r1);
  EXPECT_TRUE(p->useOxygen());
  EXPECT_EQ(r1->getRoomOxygen(), 9500);

  r1->setRoomOxygen(500);
  EXPECT_TRUE(p->useOxygen());
  EXPECT_EQ(r1->getRoomOxygen(), 0);

  r1->setRoomOxygen(0);
  EXPECT_FALSE(p->useOxygen());
  EXPECT_EQ(r1->getRoomOxygen(), 0);

  p->getInventory()->giveSpaceSuit();
  EXPECT_EQ(p->getInventory()->getOxygen(), 10000);
  EXPECT_TRUE(p->useOxygen());
  EXPECT_EQ(p->getInventory()->getOxygen(), 9500);

  p->getInventory()->setOxygen(500);
  EXPECT_TRUE(p->useOxygen());
  EXPECT_EQ(p->getInventory()->getOxygen(), 0);

  p->getInventory()->setOxygen(0);
  EXPECT_FALSE(p->useOxygen());

  p->setCurrentRoom(r2);
  d1->propagateOxygen();
  EXPECT_EQ(p->getCurrentRoom()->getRoomOxygen(), 5000);
  EXPECT_TRUE(p->useOxygen());
  EXPECT_EQ(p->getCurrentRoom()->getRoomOxygen(), 4500);

  d1->propagateOxygen();
  EXPECT_EQ(p->getCurrentRoom()->getRoomOxygen(), 2250);
  EXPECT_TRUE(p->useOxygen());
  EXPECT_EQ(p->getCurrentRoom()->getRoomOxygen(), 1750);

  delete p;
  delete d1;
  delete r1;
  delete r2;
}
