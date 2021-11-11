/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>
#include <string>
#include "Object.h"
#include "gtest/gtest.h"

TEST(TestObject, ConstructorTest) {
  Object* o1 = new Object("Object", "Loves to hug", true);
  Object* o2 = new Object();

  EXPECT_EQ(o1->getName(), "Object");
  EXPECT_EQ(o1->getName().size(), 6);
  EXPECT_EQ(o1->getDescription(), "Loves to hug");
  EXPECT_EQ(o1->getDescription().size(), 12);
  EXPECT_EQ(o1->isHoldable(), true);
  EXPECT_EQ(o2->getName(), "Thing");
  EXPECT_EQ(o2->getName().size(), 5);
  EXPECT_EQ(o2->getDescription(), "Does nothing");
  EXPECT_EQ(o2->getDescription().size(), 12);
  EXPECT_EQ(o2->isHoldable(), false);

  delete o1;
  delete o2;
}

TEST(TestObject, setHoldableTest) {
  Object* o1 = new Object("Object", "Loves to hug", true);

  EXPECT_EQ(o1->isHoldable(), true);
  o1->setHoldable(false);
  EXPECT_EQ(o1->isHoldable(), false);

  delete o1;
}

TEST(TestObject, interactDefaultTest) {
  Object* o1 = new Object("Object", "Loves to hug", true);

  EXPECT_NO_THROW(o1->interact());

  delete o1;
}
