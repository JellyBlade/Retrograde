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

  std::cout << "Past the construction" << std::endl;

  EXPECT_EQ(m->getRoom("Room"), nullptr);
  std::cout << "Past the getRoom statement" << std::endl;
  m->getRooms().push_back(r);
  std::cout << "Past the pushback statement" << std::endl;
  EXPECT_EQ(m->getRoom("Room")->getName(), "Room");

  std::cout << "Past the first tests" << std::endl;

  m->getRoom("Room")->setName("Master Chief's Man Cave");
  EXPECT_EQ(m->getRoom("Master Chief's Man Cave")->getName(),
  "Master Chief's Man Cave");
  EXPECT_EQ(m->getRoom("Room"), nullptr);

  std::cout << "Past the second tests" << std::endl;

  delete m;
  std::cout << "Past delete m" << std::endl;

  delete r;
  std::cout << "Past delete r" << std::endl;

}
