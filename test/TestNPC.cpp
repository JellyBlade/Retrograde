/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>
#include <fstream>
#include <string>

#include "NPC.h"
#include "InteractHelper.h"
#include "gtest/gtest.h"


TEST(TestNPC, talkTest) {
  Game* game = new Game();
  InteractHelper::game = game;
  InteractHelper::chapter = 0;
  NPC* n1 = new NPC("Test NPC");
  NPC* n2 = new NPC("Fake NPC");
  std::ifstream input("test/text/npcTest_empty_input.txt");

  n1->talk(input);
  InteractHelper::chapter = 1;
  n1->talk(input);
  InteractHelper::chapter = 2;
  n1->talk(input);
  n2->talk(input);
  input.close();

  delete n1;
  delete n2;
  delete game;
}

TEST(TestNPC, askTest) {
  Game* game = new Game();
  InteractHelper::game = game;
  InteractHelper::chapter = 0;
  NPC* n1 = new NPC("testNPC");
  NPC* n2 = new NPC("Fake NPC");

  std::ifstream input1("test/text/npcTest_ask_input1.txt");
  n1->ask(input1);
  input1.close();

  std::ifstream input2("test/text/npcTest_ask_input2.txt");
  n2->ask(input2);
  input2.close();
  input2.open("test/text/npcTest_ask_input2.txt");
  InteractHelper::chapter = 1;
  n2->ask(input2);
  input2.close();

  delete n1;
  delete n2;
  delete game;
}

TEST(TestNPC, stabTest) {
  NPC* n = new NPC("Test NPC");
  std::ifstream input("test/text/npcTest_empty_input.txt");
  EXPECT_EQ(n->isAlive(), true);
  n->stab(input);
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
  EXPECT_EQ(n->getCurrentRoom()->getRoomOxygen(), 10000);
  n->useOxygen();
  EXPECT_EQ(n->getCurrentRoom()->getRoomOxygen(), 9500);

  n->getCurrentRoom()->setRoomOxygen(500);
  n->useOxygen();
  EXPECT_EQ(n->getCurrentRoom()->getRoomOxygen(), 0);

  n->getCurrentRoom()->setRoomOxygen(499);
  n->useOxygen();
  EXPECT_EQ(n->getCurrentRoom()->getRoomOxygen(), 0);
  EXPECT_EQ(n->isAlive(), false);


  delete n;
  delete r1;
}
