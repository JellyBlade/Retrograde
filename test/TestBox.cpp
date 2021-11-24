/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>
#include <string>

#include "Box.h"
#include "gtest/gtest.h"

TEST(TestBox, constructorTest) {
  ObjectContainer* ObCon = new ObjectContainer();
  Object* o = new Object();
  Object* o1 = new Object();
  ObCon->addObject(o);
  ObCon->addObject(o1);

  Box* b = new Box(ObCon);
  std::cout << "ObCOn size is " << ObCon->size() << std::endl;

  EXPECT_EQ(b->getBoxObjects()->getObjects().size(), 2);
  EXPECT_TRUE(b->getBoxObjects()->isObjectInContainer(o));
  EXPECT_TRUE(b->getBoxObjects()->isObjectInContainer(o1));
  EXPECT_FALSE(b->getBoxObjects()->isObjectInContainer("You're a Harry Wizard"));

  //delete ObCon;
  delete b;
}

/*
TEST(TestBox, interactTest) {
  Box* b = new Box();
}
*/
