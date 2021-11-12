/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <vector>
#include <string>
#include <map>
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

TEST(TestRoom, setterGetterTest) {
  Room* r1 = new Room();
  Room* r2 = new Room("Boiler Room", "Casually boiling stuff");
  Object* o1 = new Object();
  Door* d1 = new Door(r1, r2);
  std::map<Globals::Direction, Door*> temp;
  std::cout << "Past Objects" << std::endl;

  EXPECT_EQ(r1->getRoomObjects()->size(), 0);
  r1->getRoomObjects()->addObject(o1);
  EXPECT_EQ(r1->getRoomObjects()->size(), 1);
  std::cout << "Past Room Objects" << std::endl;

  EXPECT_EQ(r1->getRoomOxygen(), 1.0);
  r1->setRoomOxygen(0.45);
  EXPECT_EQ(r1->getRoomOxygen(), 0.45);
  std::cout << "Past room oxygen tests" << std::endl;

  r1->changeDoor(d1, Globals::Direction::NORTH);
  EXPECT_EQ(r1->getDoor(Globals::Direction::NORTH)->getBlockedReason(),
  "This is a wall.");
  d1->blockDoor("There is PH -7 acid behind this door");
  std::cout << "before assigning d1 to NORTH" << std::endl;
  temp[Globals::Direction::NORTH] = d1;
  std::cout << "Before set doors" << std::endl;
  r1->setDoors(temp);
  EXPECT_EQ(r1->getDoor(Globals::Direction::NORTH)->getBlockedReason(),
  "There is PH -7 acid behind this door");
  std::cout << "Past last tests" << std::endl;

  delete r1;
  std::cout << "Past r1" << std::endl;
  delete r2;
  std::cout << "Past r2" << std::endl;
  delete o1;
  std::cout << "Past o1" << std::endl;
  delete d1;
}

TEST(TestRoom, changeDoorTest) {
  Room* r1 = new Room();
  Room* r2 = new Room("Boiler Room", "Casually boiling stuff");
  Door* d1 = new Door(r1, r2);

  d1->blockDoor("There is PH -7 acid behind this door");
  EXPECT_EQ(r2->getDoor(Globals::Direction::NORTH), nullptr);
  r2->changeDoor(d1, Globals::Direction::NORTH);
  EXPECT_EQ(r2->getDoor(Globals::Direction::NORTH)->getBlockedReason(),
"There is PH -7 acid behind this door");

  delete r1;
  delete r2;
  delete d1;
}
