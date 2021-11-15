/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <string>

#include "Door.h"
#include "gtest/gtest.h"

TEST(TestDoor, constructorTest) {
  Room* r1 = new Room();
  Room* r2 = new Room();
  Door* d1 = new Door(r1, r2);

  delete r1;
  delete r2;
  delete d1;
}

TEST(TestDoor, getRoomsTest) {
  Room* r1 = new Room();
  Room* r2 = new Room();
  Room* r3 = new Room();
  Door* d1 = new Door(r1, r2);

  EXPECT_EQ(d1->getRooms().first, r1);
  EXPECT_EQ(d1->getRooms().second, r2);
  EXPECT_NE(d1->getRooms().first, r3);
  EXPECT_NE(d1->getRooms().second, r3);

  delete r1;
  delete r2;
  delete r3;
  delete d1;
}

TEST(TestDoor, roomConnectionsTest) {
  Room* r1 = new Room();
  Room* r2 = new Room();
  Room* r3 = new Room();
  Door* d1 = new Door(r1, r2);

  EXPECT_EQ(d1->getOtherRoom(r3), nullptr);
  EXPECT_EQ(d1->getOtherRoom(r1), r2);
  EXPECT_EQ(d1->getOtherRoom(r2), r1);
  EXPECT_NE(d1->getOtherRoom(r1), r1);
  EXPECT_NE(d1->getOtherRoom(r2), r2);
  EXPECT_NE(d1->getOtherRoom(r2), r2);

  EXPECT_TRUE(d1->isConnectedTo(r1));
  EXPECT_TRUE(d1->isConnectedTo(r2));
  EXPECT_FALSE(d1->isConnectedTo(r3));

  delete r1;
  delete r2;
  delete r3;
  delete d1;
}

TEST(TestDoor, blockedTest) {
  Room* r1 = new Room();
  Room* r2 = new Room();
  Door* door = new Door(r1, r2);
  EXPECT_FALSE(door->isDoorBlocked());
  EXPECT_EQ(door->getBlockedReason(), "");

  door->blockDoor("Paul spilled his drink on the console.");
  EXPECT_TRUE(door->isDoorBlocked());
  EXPECT_EQ(door->getBlockedReason(), "Paul spilled his drink on the console.");

  delete door;
  delete r1;
  delete r2;
}

TEST(TestDoor, propagateOxygenTest) {
  Room* r1 = new Room();
  Room* r2 = new Room();
  Door* d1 = new Door(r1, r2);

  // Blocked door
  r1->setRoomOxygen(5000);
  d1->blockDoor("test");
  d1->propagateOxygen();
  EXPECT_EQ(r1->getRoomOxygen(), 5000);
  EXPECT_EQ(r2->getRoomOxygen(), 10000);

  // Unblocked
  d1->unblockDoor();
  d1->propagateOxygen();
  EXPECT_EQ(r1->getRoomOxygen(), r2->getRoomOxygen());
  EXPECT_EQ(r1->getRoomOxygen(), 7500);
  EXPECT_EQ(r2->getRoomOxygen(), 7500);

  d1->propagateOxygen();
  EXPECT_EQ(r1->getRoomOxygen(), 7500);
  EXPECT_EQ(r2->getRoomOxygen(), 7500);

  r1->setRoomOxygen(5000);
  d1->propagateOxygen();
  EXPECT_EQ(r1->getRoomOxygen(), 6250);
  EXPECT_EQ(r2->getRoomOxygen(), 6250);

  // One room is vacuum
  r1->setRoomOxygen(0);
  r2->setRoomOxygen(10000);
  d1->propagateOxygen();
  EXPECT_EQ(r1->getRoomOxygen(), 0);
  EXPECT_EQ(r2->getRoomOxygen(), 5000);

  r1->setRoomOxygen(5000);
  r2->setRoomOxygen(0);
  d1->propagateOxygen();
  EXPECT_EQ(r1->getRoomOxygen(), 2500);
  EXPECT_EQ(r2->getRoomOxygen(), 0);

  // Both rooms are vacuum.
  r1->setRoomOxygen(0);
  r2->setRoomOxygen(0);
  d1->propagateOxygen();
  EXPECT_EQ(r1->getRoomOxygen(), 0);
  EXPECT_EQ(r2->getRoomOxygen(), 0);

  // Round down to vacuum
  r1->setRoomOxygen(0);
  r2->setRoomOxygen(150);
  d1->propagateOxygen();
  EXPECT_EQ(r1->getRoomOxygen(), 0);
  EXPECT_EQ(r2->getRoomOxygen(), 0);

  delete r1;
  delete r2;
  delete d1;
}
