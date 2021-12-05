/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <string>

#include "InteractHelper.h"
#include "Game.h"
#include "NPC.h"
#include "Room.h"
#include "gtest/gtest.h"

TEST(TestInteractHelper, basicGetTests) {
  Game* game = new Game();
  InteractHelper::game = game;

  EXPECT_EQ(InteractHelper::chapter, 0);
  EXPECT_EQ(InteractHelper::getMap(), game->getMap());
  EXPECT_EQ(InteractHelper::getPlayerHandler(), game->getPlayerHandler());
  EXPECT_EQ(InteractHelper::getPlayerInventory(),
  game->getPlayerHandler()->getPlayer()->getInventory());

  delete game;
}

TEST(TestInteractHelper, getNPCTest) {
  Game* game = new Game();
  InteractHelper::game = game;
  NPC* n1 = new NPC("joe", "it's joe!");

  EXPECT_EQ(InteractHelper::getNPCs().size(), 0);
  game->addNPC(n1);
  EXPECT_EQ(InteractHelper::getNPCs().size(), 1);
  EXPECT_EQ(game->getNPCs().size(), 1);

  EXPECT_EQ(InteractHelper::getNPC("joe"), n1);
  EXPECT_EQ(InteractHelper::getNPC("nobody special"), nullptr);

  delete game;
}

TEST(TestInteractHelper, npcInRoomTest) {
  Game* game = new Game();
  InteractHelper::game = game;
  NPC* n1 = new NPC("joe", "it's joe!");
  NPC* n2 = new NPC("not joe", "it's not joe :(");
  Room* r1 = new Room("test", "test");
  Room* r2 = new Room("test2", "test2");
  InteractHelper::getMap()->addRoom(r1);
  InteractHelper::getMap()->addRoom(r2);
  game->addNPC(n1);
  game->addNPC(n2);
  n1->moveNPC(r1);
  n2->moveNPC(r2);

  EXPECT_TRUE(InteractHelper::npcInRoom(n1, r1));
  EXPECT_TRUE(InteractHelper::npcInRoom("joe", r1));
  EXPECT_FALSE(InteractHelper::npcInRoom(n2, r1));
  EXPECT_FALSE(InteractHelper::npcInRoom("notjoe", r1));

  EXPECT_TRUE(InteractHelper::npcInRoom(n2, r2));
  EXPECT_TRUE(InteractHelper::npcInRoom("notjoe", r2));
  EXPECT_FALSE(InteractHelper::npcInRoom(n1, r2));
  EXPECT_FALSE(InteractHelper::npcInRoom("joe", r2));

  delete game;
}
