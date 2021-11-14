/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include "Globals.h"
#include "gtest/gtest.h"

using Globals::Direction;

TEST(TestGlobals, stringToDirectionTest) {
  //EXPECT_THROW(Globals::stringToDirection("nope"), some_exception);
  EXPECT_EQ(Globals::stringToDirection("north"), Direction::NORTH);
  EXPECT_EQ(Globals::stringToDirection("n"), Direction::NORTH);
  EXPECT_EQ(Globals::stringToDirection("east"), Direction::EAST);
  EXPECT_EQ(Globals::stringToDirection("e"), Direction::EAST);
  EXPECT_EQ(Globals::stringToDirection("south"), Direction::SOUTH);
  EXPECT_EQ(Globals::stringToDirection("s"), Direction::SOUTH);
  EXPECT_EQ(Globals::stringToDirection("west"), Direction::WEST);
  EXPECT_EQ(Globals::stringToDirection("w"), Direction::WEST);
  EXPECT_EQ(Globals::stringToDirection("NORTH"), Direction::NORTH);
  EXPECT_EQ(Globals::stringToDirection("nOrTH"), Direction::NORTH);
  EXPECT_EQ(Globals::stringToDirection("  n o r TH  "), Direction::NORTH);
  EXPECT_EQ(Globals::stringToDirection("so u       th"), Direction::SOUTH);
}

TEST(TestGlobals, directionToStringTest) {
  EXPECT_EQ(Globals::directionToString(Globals::NORTH), "north");
  EXPECT_EQ(Globals::directionToString(Globals::EAST), "east");
  EXPECT_EQ(Globals::directionToString(Globals::SOUTH), "south");
  EXPECT_EQ(Globals::directionToString(Globals::WEST), "west");
}
