/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>
#include <string>

#include "Box.h"
#include "gtest/gtest.h"

TEST(TestBox, constructorTest) {
  std::cout << "Before everything.";
  Object* o = new Object("test", "test", false);
  Object* o1 = new Object("test2", "test2", false);
  Object* o2 = new Object("You're a Harry Wizard", "yer a wezrd hry", false);
  std::cout << "After object instantiations, but before box.";
  Box* b = new Box();
  std::cout << "after instantiations";
  b->addObject(o);
  b->addObject(o1);

  std::cout << "Box size is " << b->getBoxObjects()->size() << std::endl;

  EXPECT_EQ(b->getBoxObjects()->size(), 2);
  std::cout << "after size " << std::endl;
  EXPECT_TRUE(b->getBoxObjects()->isObjectInContainer(o));
  std::cout << "after is o in container " << std::endl;
  EXPECT_TRUE(b->getBoxObjects()->isObjectInContainer(o1));
  std::cout << "after is o1 in container " << std::endl;
  EXPECT_FALSE(b->getBoxObjects()->isObjectInContainer(o2));
  std::cout << "after is Harry Potter in container " << std::endl;

  delete b;
  delete o2;
  std::cout << "After deleting" << std::endl;
}

TEST(TestBox, interactTest) {
  std::cout << "Before second test" << std::endl;
  Box* b = new Box();
}
