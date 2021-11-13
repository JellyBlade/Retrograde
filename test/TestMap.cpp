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
  EXPECT_EQ(m->getMapOxygen(), 10000);
  EXPECT_EQ(m->getRooms().at(0)->getRoomOxygen(), 10000);
  m->setAllRoomOxygen(5500);
  EXPECT_EQ(m->getMapOxygen(), 5500);
  EXPECT_EQ(m->getRooms().at(0)->getRoomOxygen(), 5500);

  delete m;
  delete r1;
  delete r2;
}

TEST(TestMap, calculateMapOxygenTest) {
  Map* m = new Map();
  Room* r1 = new Room();
  Room* r2 = new Room();

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

  delete m;
  delete r1;
  delete r2;
}
