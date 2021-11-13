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
  delete r;
}

//TODO(mart2720): Exceptions could maybe thrown in the next two sets of tests

TEST(TestMap, setAllRoomOxygenTest) {
  Map* m = new Map();
  Room* r1 = new Room();
  Room* r2 = new Room();

  m->addRoom(r1);
  m->addRoom(r2);
  m->calculateMapOxygen();
  EXPECT_EQ(m->getMapOxygen(), 1.0);
  EXPECT_EQ(m->getRooms().at(0)->getRoomOxygen(), 1.0);
  m->setAllRoomOxygen(0.55);
  EXPECT_EQ(m->getMapOxygen(), 0.55);
  EXPECT_EQ(m->getRooms().at(0)->getRoomOxygen(), 0.55);

  delete m;
  delete r1;
  delete r2;
}

TEST(TestMap, calculateMapOxygenTest) {
  Map* m = new Map();
  Room* r1 = new Room();
  Room* r2 = new Room();

  r2->setRoomOxygen(0.5);
  m->addRoom(r1);
  m->addRoom(r2);
  m->calculateMapOxygen();
  EXPECT_EQ(m->getMapOxygen(), 0.75);
  EXPECT_EQ(m->getRooms().at(0)->getRoomOxygen(), 1.0);
  EXPECT_EQ(m->getRooms().at(1)->getRoomOxygen(), 0.5);

  r2->setRoomOxygen(-0.1);
  EXPECT_EQ(m->getMapOxygen(), 0.75);
  EXPECT_EQ(m->getRooms().at(0)->getRoomOxygen(), 1.0);
  EXPECT_EQ(m->getRooms().at(1)->getRoomOxygen(), 0.5);

  r2->setRoomOxygen(100.01);
  EXPECT_EQ(m->getMapOxygen(), 0.75);
  EXPECT_EQ(m->getRooms().at(0)->getRoomOxygen(), 1.0);
  EXPECT_EQ(m->getRooms().at(1)->getRoomOxygen(), 0.5);

  delete m;
  delete r1;
  delete r2;
}
