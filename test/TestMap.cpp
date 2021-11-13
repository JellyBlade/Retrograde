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
