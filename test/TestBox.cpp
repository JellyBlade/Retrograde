/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>
#include <fstream>
#include <string>

#include "Box.h"
#include "Game.h"
#include "InteractHelper.h"
#include "gtest/gtest.h"

TEST(TestBox, constructorTest) {
  Object* o = new Object("test", "test", false);
  Object* o1 = new Object("test2", "test2", false);
  Object* o2 = new Object("You're a Harry Wizard", "yer a wezrd hry", false);
  Box* b = new Box();
  b->addObject(o);
  b->addObject(o1);

  EXPECT_EQ(b->getBoxObjects()->size(), 2);
  EXPECT_TRUE(b->getBoxObjects()->isObjectInContainer(o));
  EXPECT_TRUE(b->getBoxObjects()->isObjectInContainer(o1));
  EXPECT_FALSE(b->getBoxObjects()->isObjectInContainer(o2));

  delete b;
  delete o2;
}

TEST(TestBox, interactTest) {
  Game* game = new Game();
  InteractHelper::game = game;
  Box* b = new Box();
  Object* o1 = new Object("Test", "Test!", true);
  Object* o2 = new Object("Better test", "It really is just better.", true);
  std::ifstream file("test/text/boxTest.txt");

  EXPECT_EQ(b->getBoxObjects()->size(), 0);
  b->interact();
  b->addObject(o1);
  b->addObject(o2);
  EXPECT_EQ(b->getBoxObjects()->size(), 2);
  b->interact();

  b->displayBoxObjects();
  EXPECT_FALSE(b->playerInput(file));
  EXPECT_TRUE(b->playerInput(file));
  EXPECT_EQ(b->getBoxObjects()->size(), 1);
  EXPECT_EQ(InteractHelper::getPlayerHandler()->getPlayer()
  ->getInventory()->size(), 1);

  delete game;
  delete b;
}
