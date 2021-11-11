/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <string>

#include "Door.h"
#include "gtest/gtest.h"

TEST(TestDoor, constructorTest) {
  Door* door = new Door();
  // add non-default when Room is implemented.

  delete door;
}

TEST(TestDoor, RoomTest) {
  // do later
}

TEST(TestDoor, blockedTest) {
  Door* door = new Door();
  EXPECT_TRUE(door->isDoorBlocked());
  EXPECT_NE(door->getBlockedReason(), "");

  door->unblockDoor();
  EXPECT_FALSE(door->isDoorBlocked());
  EXPECT_EQ(door->getBlockedReason(), "");

  door->blockDoor("Paul spilled his drink on the console.");
  EXPECT_TRUE(door->isDoorBlocked());
  EXPECT_EQ(door->getBlockedReason(), "Paul spilled his drink on the console.");

  delete door;
}

TEST(TestDoor, propagateOxygenTest) {
  // do later
}
