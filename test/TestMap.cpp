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

  std::cout << "Past the construction" << endl;

  EXPECT_EQ(m->getRoom("Room"), nullptr);
  m->getRooms().push_back(r);
  EXPECT_EQ(m->getRoom("Room")->getName(), "Room");

  std::cout << "Past the first tests" << endl;

  m->getRoom("Room")->setName("Master Chief's Man Cave");
  EXPECT_EQ(m->getRoom("Master Chief's Man Cave")->getName(),
  "Master Chief's Man Cave");
  EXPECT_EQ(m->getRoom("Room"), nullptr);

  std::cout << "Past the second tests" << endl;

  delete m;
  std::cout << "Past delete m" << endl;

  delete r;
  std::cout << "Past delete r" << endl;

}
