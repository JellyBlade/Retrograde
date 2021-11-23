/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include "NPC.h"
#include <iostream>
#include <string>
#include "gtest/gtest.h"

/*
TODO(mart2720): To be tested after implementation
TEST(TestNPC, talkTest){}
*/

/*
TODO(mart2720): To be tested after implementation
TEST(TestNPC, askTest){}
*/

TEST(TestNPC, stabTest) {
  NPC* n = new NPC();

  EXPECT_EQ(n->isAlive(), true);
  n->stab();
  EXPECT_EQ(n->isAlive(), false);

  delete n;
}

TEST(TestNPC, moveNPCTest) {
  NPC* n = new NPC();
  Room* r1 = new Room();
  Room* r2 = new Room();

  n->moveNPC(r1);
  EXPECT_EQ(n->getCurrentRoom(), r1);
  n->moveNPC(r2);
  EXPECT_EQ(n->getCurrentRoom(), r2);

  delete n;
  delete r1;
  delete r2;
}

TEST(TestNPC, useOxygenTest) {
  NPC* n = new NPC();
  Room* r1 = new Room();

  n->moveNPC(r1);
  EXPECT_EQ(n->getCurrentRoom->getRoomOxygen(), 10000);
  n->useOxygen();
  EXPECT_EQ(n->getCurrentRoom->getRoomOxygen(), 9500);

  n->getCurrentRoom->setRoomOxygen(500);
  n->useOxygen();
  EXPECT_EQ(n->getCurrentRoom->getRoomOxygen(), 0);

  n->getCurrentRoom->setRoomOxygen(499);
  n->useOxygen();
  EXPECT_EQ(n->getCurrentRoom->getRoomOxygen(), 0);
  EXPECT_EQ(n->isAlive(), false);


  delete n;
  delete r1;
}
