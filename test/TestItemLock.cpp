/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include "InteractHelper.h"
#include "ItemLock.h"
#include "gtest/gtest.h"

TEST(TestItemLock, interactTest) {
  Game* game = new Game();
  InteractHelper::game = game;
  Object* o = new Object("Key", "unlocks someting", true);
  ItemLock* i = new ItemLock("Locker", "Something is inside", false, "Key");

  EXPECT_EQ(i->isPuzzleSolved(), false);
  i->interact();
  EXPECT_EQ(i->isPuzzleSolved(), false);
  InteractHelper::getPlayerInventory()->addObject(o);
  i->interact();
  EXPECT_EQ(i->isPuzzleSolved(), true);

  delete game;
  delete i;
}
