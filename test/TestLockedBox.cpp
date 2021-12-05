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
#include "LockedBox.h"
#include "PasswordLock.h"
#include "gtest/gtest.h"

TEST(LockedBoxTest, ConstructorTest) {
  Object* o = new Object("test", "test", false);
  Object* o1 = new Object("test2", "test2", false);
  Object* o2 = new Object("You're a Harry Wizard", "yer a wezrd hry", false);
  Puzzle* p = new Puzzle();
  LockedBox* b = new LockedBox();
  std::ifstream file("test/text/puzzleTest_empty.txt");
  p->setSolved(file);
  LockedBox* b2 = new LockedBox("Treasure Chest", "Gold inside", true, p);
  b->addObject(o);
  b->addObject(o1);

  EXPECT_EQ(b->getBoxObjects()->size(), 2);
  EXPECT_TRUE(b->getBoxObjects()->isObjectInContainer(o));
  EXPECT_TRUE(b->getBoxObjects()->isObjectInContainer(o1));
  EXPECT_FALSE(b->getBoxObjects()->isObjectInContainer(o2));

  EXPECT_EQ(b2->getBoxObjects()->size(), 0);
  EXPECT_FALSE(b2->getBoxObjects()->isObjectInContainer(o));
  EXPECT_FALSE(b2->getBoxObjects()->isObjectInContainer(o1));
  EXPECT_FALSE(b2->getBoxObjects()->isObjectInContainer(o2));

  delete b;
  delete b2;
  delete o2;
}

TEST(LockedBoxTest, interactTest) {
  Game* game = new Game();
  InteractHelper::game = game;
  PasswordLock* p = new PasswordLock();
  LockedBox* b = new LockedBox("Treasure Chest", "Just some gold", false, p);
  Object* o1 = new Object("Test", "Test!", true);
  Object* o2 = new Object("Better test", "It really is just better.", true);
  std::ifstream file1("test/text/boxTest.txt");
  std::ifstream file2("test/text/puzzleTest_empty.txt");

  b->playerInput(file1);

  EXPECT_EQ(b->getBoxObjects()->size(), 0);
  b->interact();
  b->addObject(o1);
  b->addObject(o2);
  EXPECT_EQ(b->getBoxObjects()->size(), 2);

  EXPECT_FALSE(b->playerInput(file1));
  EXPECT_TRUE(b->playerInput(file1));
  EXPECT_EQ(b->getBoxObjects()->size(), 1);
  EXPECT_EQ(InteractHelper::getPlayerHandler()->getPlayer()
  ->getInventory()->size(), 1);

  delete game;
  delete b;
}
