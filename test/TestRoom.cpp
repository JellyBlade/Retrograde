/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <vector>
#include <string>
#include <map>
#include <typeinfo>
#include "Room.h"
#include "Door.h"
#include "NamedThing.h"
#include "Globals.h"
#include "ObjectContainer.h"
#include "gtest/gtest.h"

TEST(TestRoom, constructorTest) {
  Room* r1 = new Room();
  Room* r2 = new Room("Boiler Room", "Casually boiling stuff");

  EXPECT_EQ(r1->getName(), "Room");
  EXPECT_EQ(r1->getName().size(), 4);
  EXPECT_EQ(r1->getDescription(), "Empty room");
  EXPECT_EQ(r1->getDescription().size(), 10);
  EXPECT_EQ(r1->getDoor(Globals::Direction::NORTH), nullptr);
  EXPECT_EQ(r1->getDoor(Globals::Direction::EAST), nullptr);
  EXPECT_EQ(r1->getDoor(Globals::Direction::SOUTH), nullptr);
  EXPECT_EQ(r1->getDoor(Globals::Direction::WEST), nullptr);
  EXPECT_EQ(r1->getRoomOxygen(), 1);

  EXPECT_EQ(r2->getName(), "Boiler Room");
  EXPECT_EQ(r2->getName().size(), 11);
  EXPECT_EQ(r2->getDescription(), "Casually boiling stuff");
  EXPECT_EQ(r2->getDescription().size(), 22);
  EXPECT_EQ(r2->getDoor(Globals::Direction::NORTH), nullptr);
  EXPECT_EQ(r2->getDoor(Globals::Direction::EAST), nullptr);
  EXPECT_EQ(r2->getDoor(Globals::Direction::SOUTH), nullptr);
  EXPECT_EQ(r2->getDoor(Globals::Direction::WEST), nullptr);
  EXPECT_EQ(r2->getRoomOxygen(), 1);

  delete r1;
  delete r2;
}

TEST(TestRoom, changeDoorTest) {
  Room* r1 = new Room();
  Room* r2 = new Room("Boiler Room", "Casually boiling stuff");
  Door* d1 = new Door(r1, r2);

  d1->blockDoor("There is PH -7 acid behind this door");
  EXPECT_EQ(r2->getDoor(Globals::Direction::NORTH)->getBlockedReason(),
"This is a wall.");
  r2->changeDoor(d1, Globals::Direction::NORTH);
  EXPECT_EQ(r2->getDoor(Globals::Direction::NORTH)->getBlockedReason(),
"There is PH -7 acid behind this door");

  delete r1;
  delete r2;
  delete d1;
}
