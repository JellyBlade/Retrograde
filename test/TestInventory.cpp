/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include "Inventory.h"
#include "gtest/gtest.h"

TEST(TestInventory, constructorTest) {
  Inventory* i = new Inventory();

  EXPECT_FALSE(i->hasSpaceSuit());
  EXPECT_EQ(i->getOxygen(), 0);

  delete i;
}

TEST(TestInventory, spaceSuitTest) {
  Inventory* i = new Inventory();

  EXPECT_FALSE(i->hasSpaceSuit());
  EXPECT_EQ(i->getOxygen(), 0);

  i->giveSpaceSuit();
  EXPECT_TRUE(i->hasSpaceSuit());
  EXPECT_EQ(i->getOxygen(), 10000);

  i->setOxygen(5000);
  EXPECT_EQ(i->getOxygen(), 5000);

  delete i;
}

TEST(TestInventory, addObjectTest) {
  Inventory* i = new Inventory();
  Object* o1 = new Object("Small key", "It's small and key-ish", true);
  Object* o2 = new Object("Literally a planet", "How is this in here?", false);

  EXPECT_EQ(i->size(), 0);

  i->addObject(o1);
  EXPECT_EQ(i->size(), 1);

  i->addObject(o2);
  EXPECT_EQ(i->size(), 1);

  delete i;
  delete o2;
}
