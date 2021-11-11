/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <vector>
#include <string>
#include <map>
#include <typeinfo>
#include "Room.h"
#include "Door.h"
#include "NamedThing.h"
#include "Globals.h"
#include "ObjectContainer.h"
#include "gtest/gtest.h"

TEST(TestRoom, constructorTest) {
  Room* r1 = new Room();
  Room* r2 = new Room("Boiler Room", "Casually boiling stuff");

  EXPECT_EQ(r1->getName(), "Room");
  EXPECT_EQ(r1->getName().size(), 4);
  EXPECT_EQ(r1->getDescription(), "Empty room");
  EXPECT_EQ(r1->getDescription().size(), 10);
  EXPECT_EQ(typeid(r1->getDoors()[NORTH]), Door);
  EXPECT_EQ(typeid(r1->getDoors()[EAST]), Door);
  EXPECT_EQ(typeid(r1->getDoors()[SOUTH]), Door);
  EXPECT_EQ(typeid(r1->getDoors()[WEST]), Door);

  EXPECT_EQ(r2->getName(), "Boiler Room");
  EXPECT_EQ(r2->getName().size(), 11);
  EXPECT_EQ(r2->getDescription(), "Casually boiling stuff");
  EXPECT_EQ(r2->getDescription().size(), 23);
  EXPECT_EQ(typeid(r2->getDoors()[NORTH]), Door);
  EXPECT_EQ(typeid(r2->getDoors()[EAST]), Door);
  EXPECT_EQ(typeid(r2->getDoors()[SOUTH]), Door);
  EXPECT_EQ(typeid(r2->getDoors()[WEST]), Door);

  delete r1;
  delete r2;
}

TEST(TestRoom, changeDoorTest) {
  

}
