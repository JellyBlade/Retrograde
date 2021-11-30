/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <string>

#include "GenerateHelper.h"
#include "PlayerHandler.h"
#include "Object.h"
#include "Room.h"
#include "Door.h"
#include "Map.h"
#include "Box.h"
#include "gtest/gtest.h"

TEST(TestGenerateHelper, objectGenerationTest) {
  Object* o1 = new Object("Apple", "It's an apple.", true);
  Object* o2 = GenerateHelper::generateObject("apple");
  EXPECT_EQ(o2->getName(), o1->getName());

  Box* o3 = dynamic_cast<Box*>(GenerateHelper::generateObject("locker"));
  EXPECT_EQ(o3->getBoxObjects()->size(), 3);
  EXPECT_TRUE(o3->getBoxObjects()->isObjectInContainer("apple"));
  EXPECT_FALSE(o3->getBoxObjects()->isObjectInContainer("bluekeycard"));

  delete o1;
  delete o2;
  delete o3;
}

TEST(TestGenerateHelper, roomGenerationTest) {
  Room* r1 = GenerateHelper::generateRoom("engineeringbay");
  EXPECT_EQ(r1->getRoomObjects()->size(), 5);
  EXPECT_TRUE(r1->getRoomObjects()->isObjectInContainer("locker"));
  EXPECT_EQ(r1->getRoomOxygen(), 10000);

  Room* r2 = GenerateHelper::generateRoom("ruined hallway");
  EXPECT_EQ(r2->getRoomObjects()->size(), 4);
  EXPECT_TRUE(r2->getRoomObjects()->isObjectInContainer("hull debris"));
  EXPECT_EQ(r2->getRoomOxygen(), 1000);

  Room* r3 = GenerateHelper::generateRoom("bridge");
  EXPECT_EQ(r3->getRoomObjects()->size(), 2);
  EXPECT_TRUE(r3->getRoomObjects()->isObjectInContainer("admiral's log"));
  EXPECT_TRUE(r3->getRoomObjects()->isObjectInContainer("admiral'slog"));
  EXPECT_TRUE(r3->getRoomObjects()->isObjectInContainer("Admiral's Log"));
  EXPECT_EQ(r3->getRoomOxygen(), 10000);

  delete r1;
  delete r2;
  delete r3;
}

TEST(TestGenerateHelper, mapGenerationTest) {
  Map* map = GenerateHelper::generateMap("testMap");
  PlayerHandler* ph = new PlayerHandler();
  EXPECT_EQ(map->getRooms().size(), 8);
  EXPECT_EQ(map->getDoors().size(), 7);
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

  delete ph;
  delete map;
}
