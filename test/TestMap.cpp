/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <vector>
#include <string>
#include <iostream>

#include "Map.h"
#include "gtest/gtest.h"

TEST(TestMap, getRoomTest) {
  Map* m = new Map();
  Room* r = new Room();

  EXPECT_EQ(m->getRoom("Room"), nullptr);
  m->addRoom(r);
  EXPECT_EQ(m->getRoom("Room")->getName(), "Room");

  m->getRoom("Room")->setName("Master Chief's Man Cave");
  EXPECT_EQ(m->getRoom("Master Chief's Man Cave")->getName(),
  "Master Chief's Man Cave");
  EXPECT_EQ(m->getRoom("Room"), nullptr);

  delete m;
}

TEST(TestMap, getDoorsTest) {
  Map* m = new Map();
  Room* r1 = new Room();
  Room* r2 = new Room();
  Room* r3 = new Room();
  Door* d1 = new Door(r1, r2);
  Door* d2 = new Door(r1, r3);
  Door* d3 = new Door(r2, r3);

  m->addRoom(r1);
  m->addRoom(r2);
  m->addRoom(r3);

  m->addDoor(d1);
  m->addDoor(d2);
  m->addDoor(d3);

  EXPECT_TRUE(m->doesDoorExistBetween(r1, r2));
  EXPECT_TRUE(m->doesDoorExistBetween(r1, r3));
  EXPECT_TRUE(m->doesDoorExistBetween(r2, r3));

  EXPECT_EQ(m->getDoors().size(), 3);
  EXPECT_EQ(m->getDoors()[0], d1);
  EXPECT_EQ(m->getDoors()[2], d3);

  delete m;
}

TEST(TestMap, setAllRoomOxygenTest) {
  Map* m = new Map();
  Room* r1 = new Room();
  Room* r2 = new Room();

  m->addRoom(r1);
  m->addRoom(r2);
  m->calculateMapOxygen();
  EXPECT_EQ(m->getMapOxygen(), 10000);
  EXPECT_EQ(m->getRooms().at(0)->getRoomOxygen(), 10000);
  m->setAllRoomOxygen(5500);
  EXPECT_EQ(m->getMapOxygen(), 5500);
  EXPECT_EQ(m->getRooms().at(0)->getRoomOxygen(), 5500);

  delete m;
}

TEST(TestMap, calculateMapOxygenTest) {
  Map* m = new Map();
  Room* r1 = new Room();
  Room* r2 = new Room();
  Room* r3 = new Room();
  Door* d1 = new Door(r1, r2);
  Door* d2 = new Door(r2, r3);
  Door* d3 = new Door(r1, r3);

  r2->setRoomOxygen(5000);
  m->addRoom(r1);
  m->addRoom(r2);
  m->calculateMapOxygen();
  EXPECT_EQ(m->getMapOxygen(), 7500);
  EXPECT_EQ(m->getRooms().at(0)->getRoomOxygen(), 10000);
  EXPECT_EQ(m->getRooms().at(1)->getRoomOxygen(), 5000);

  r2->setRoomOxygen(-1);
  m->calculateMapOxygen();
  EXPECT_EQ(m->getMapOxygen(), 5000);
  EXPECT_EQ(m->getRooms().at(0)->getRoomOxygen(), 10000);
  EXPECT_EQ(m->getRooms().at(1)->getRoomOxygen(), 0);

  r2->setRoomOxygen(10001);
  m->calculateMapOxygen();
  EXPECT_EQ(m->getMapOxygen(), 10000);
  EXPECT_EQ(m->getRooms().at(0)->getRoomOxygen(), 10000);
  EXPECT_EQ(m->getRooms().at(1)->getRoomOxygen(), 10000);

  m->addRoom(r3);
  m->addDoor(d1);
  m->addDoor(d2);
  m->addDoor(d3);
  r3->setRoomOxygen(0);
  m->calculateMapOxygen();
  EXPECT_EQ(m->getMapOxygen(), 3333);
  EXPECT_EQ(m->getRooms().at(0)->getRoomOxygen(), 5000);
  EXPECT_EQ(m->getRooms().at(1)->getRoomOxygen(), 5000);
  EXPECT_EQ(m->getRooms().at(2)->getRoomOxygen(), 0);

  delete m;
}
