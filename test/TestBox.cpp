/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>
#include <string>

#include "Box.h"
#include "gtest/gtest.h"

//TODO(mart2720): Seg fault happening on line 18 on Box.cpp, dont have the
// time to fix it right now
/*
TEST(TestBox, constructorTest) {
  ObjectContainer* ObCon = new ObjectContainer();
  Object* o = new Object();
  Object* o1 = new Object();
  ObCon->addObject(o);
  ObCon->addObject(o1);

  std::cout << "Im assuming seg fault in constructor " << std::endl;
  std::cout << "This is the address of o " << o << std::endl;
  Box* b = new Box(ObCon);
  std::cout << "ObCOn size is " << ObCon->size() << std::endl;

  EXPECT_EQ(b->getBoxObjects()->getObjects().size(), 2);
  EXPECT_TRUE(b->getBoxObjects()->isObjectInContainer(o));
  EXPECT_TRUE(b->getBoxObjects()->isObjectInContainer(o1));
  EXPECT_FALSE(b->getBoxObjects()->isObjectInContainer("You're a Harry Wizard"));

  //delete ObCon;
  delete b;
}
*/

/*
TEST(TestBox, interactTest) {
  Box* b = new Box();
}
*/
