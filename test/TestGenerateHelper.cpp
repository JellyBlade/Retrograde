/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <string>

#include "GenerateHelper.h"
#include "Object.h"
#include "Room.h"
#include "Door.h"
#include "Map.h"
#include "Box.h"
#include "gtest/gtest.h"

TEST(TestGenerateHelper, objectGenerationTest) {
  Object* o1 = new Object("Apple", "It's an apple.", true);
  Object* o2 = GenerateHelper::generateObject("apple");
  EXPECT_EQ(o2->getName(), o1->getName());

  Box* o3 = dynamic_cast<Box*>(GenerateHelper::generateObject("locker"));
  EXPECT_EQ(o3->getBoxObjects()->size(), 3);
  EXPECT_TRUE(o3->getBoxObjects()->isObjectInContainer("apple"));
  EXPECT_FALSE(o3->getBoxObjects()->isObjectInContainer("bluekeycard"));

  delete o1;
  delete o2;
  delete o3;
}

TEST(TestGenerateHelper, roomGenerationTest) {
  Room* r1 = GenerateHelper::generateRoom("engineeringbay");
  EXPECT_EQ(r1->getRoomObjects()->size(), 5);
  EXPECT_TRUE(r1->getRoomObjects()->isObjectInContainer("locker"));
  EXPECT_EQ(r1->getRoomOxygen(), 10000);

  Room* r2 = GenerateHelper::generateRoom("ruined hallway");
  EXPECT_EQ(r2->getRoomObjects()->size(), 4);
  EXPECT_TRUE(r2->getRoomObjects()->isObjectInContainer("hull debris"));
  EXPECT_EQ(r2->getRoomOxygen(), 2500);

  Room* r3 = GenerateHelper::generateRoom("bridge");
  EXPECT_EQ(r3->getRoomObjects()->size(), 2);
  EXPECT_TRUE(r3->getRoomObjects()->isObjectInContainer("admiral's log"));
  EXPECT_TRUE(r3->getRoomObjects()->isObjectInContainer("admirals log"));
  EXPECT_TRUE(r3->getRoomObjects()->isObjectInContainer("admiral'slog"));
  EXPECT_TRUE(r3->getRoomObjects()->isObjectInContainer("Admiral's Log"));
  EXPECT_TRUE(r3->getRoomObjects()->isObjectInContainer("AdmiralsLog"));
  EXPECT_EQ(r3->getRoomOxygen(), 10000);

  delete r1;
  delete r2;
  delete r3;
}
