/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <string>

#include "GenerateHelper.h"
#include "InteractHelper.h"
#include "Game.h"
#include "PlayerHandler.h"
#include "Object.h"
#include "AirLock.h"
#include "Room.h"
#include "NPC.h"
#include "Door.h"
#include "Map.h"
#include "Box.h"
#include "gtest/gtest.h"

using GenerateHelper::generateObject;
using GenerateHelper::generateRoom;
using GenerateHelper::generateMap;
using GenerateHelper::generateNPC;

TEST(TestGenerateHelper, objectGenerationTest) {
  Object* o1 = new Object("Apple", "It's an apple.", true);
  Object* o2 = generateObject("apple");
  EXPECT_EQ(o2->getName(), o1->getName());

  Box* o3 = dynamic_cast<Box*>(generateObject("locker 7"));
  EXPECT_EQ(o3->getBoxObjects()->size(), 3);
  EXPECT_FALSE(o3->getBoxObjects()->isObjectInContainer("apple"));
  EXPECT_FALSE(o3->getBoxObjects()->isObjectInContainer("blue key card"));
  EXPECT_TRUE(o3->getBoxObjects()->isObjectInContainer("redkeycard"));

  Box* o4 = dynamic_cast<Box*>(generateObject("valencia_locker"));
  EXPECT_EQ(o3->getBoxObjects()->size(), 3);
  EXPECT_FALSE(o3->getBoxObjects()->isObjectInContainer("apple"));
  EXPECT_FALSE(o3->getBoxObjects()->isObjectInContainer("blue key card"));
  EXPECT_TRUE(o3->getBoxObjects()->isObjectInContainer("redkeycard"));

  AirLock* o5 = dynamic_cast<AirLock*>(generateObject("airlock_panel"));

  EXPECT_THROW(generateObject("sadijf#(*$%K)"), std::runtime_error);

  delete o1;
  delete o2;
  delete o3;
  delete o4;
  delete o5;
}

TEST(TestGenerateHelper, npcGenerationTest) {
  NPC* n1 = new NPC("Joe", "It's Joe!");
  NPC* n2 = generateNPC("joe");
  EXPECT_EQ(n1->getName(), n2->getName());
  EXPECT_EQ(n1->getDescription(), n2->getDescription());

  EXPECT_THROW(generateNPC("sadijf#(*$%K)"), std::runtime_error);

  delete n1;
  delete n2;
}

TEST(TestGenerateHelper, roomGenerationTest) {
  Room* r1 = generateRoom("medical bay");
  EXPECT_EQ(r1->getRoomObjects()->size(), 4);
  EXPECT_TRUE(r1->getRoomObjects()->isObjectInContainer("locker 7"));
  EXPECT_EQ(r1->getRoomOxygen(), 10000);

  Room* r2 = generateRoom("ruined hallway");
  EXPECT_EQ(r2->getRoomObjects()->size(), 4);
  EXPECT_TRUE(r2->getRoomObjects()->isObjectInContainer("hull debris"));
  EXPECT_EQ(r2->getRoomOxygen(), 0);

  Room* r3 = generateRoom("bridge");
  EXPECT_EQ(r3->getRoomObjects()->size(), 4);
  EXPECT_EQ(r3->getRoomOxygen(), 10000);

  EXPECT_THROW(generateRoom("Totally real room"), std::runtime_error);

  delete r1;
  delete r2;
  delete r3;
}

TEST(TestGenerateHelper, mapGenerationTest) {
  Game* game = new Game();
  InteractHelper::game = game;
  EXPECT_THROW(generateMap("nonExistentMap"), std::runtime_error);
  Map* map = generateMap("testMap");
  PlayerHandler* ph = InteractHelper::getPlayerHandler();
  EXPECT_EQ(map->getRooms().size(), 11);
  EXPECT_EQ(map->getDoors().size(), 9);
  for (Door* d : map->getDoors()) {
    std::cout << "Door connected to: " << d->getRooms().first->getName();
    std::cout << " and " << d->getRooms().second->getName() << std::endl;
  }
  EXPECT_EQ(map->getRoom("fake room that doesn't exist"), nullptr);
  Room* start = map->getRoom("engineering bay");
  ph->getPlayer()->setCurrentRoom(start);
  EXPECT_TRUE(ph->movePlayer(Globals::Direction::NORTH));
  EXPECT_FALSE(ph->movePlayer(Globals::Direction::NORTH));
  EXPECT_TRUE(ph->movePlayer(Globals::Direction::SOUTH));
  EXPECT_TRUE(ph->movePlayer(Globals::Direction::WEST));
  EXPECT_FALSE(ph->movePlayer(Globals::Direction::WEST));
  EXPECT_TRUE(ph->movePlayer(Globals::Direction::SOUTH));
  EXPECT_TRUE(ph->movePlayer(Globals::Direction::SOUTH));
  EXPECT_EQ(ph->getPlayer()->getCurrentRoom(), map->getRoom("reactor room"));

  delete game;
  delete map;
}
