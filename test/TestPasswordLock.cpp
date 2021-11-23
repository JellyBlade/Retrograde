/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include "PasswordLock.h"
#include "gtest/gtest.h"

TEST(TestPasswordLock, constructorTest) {
  PasswordLock* p = new PasswordLock();
  PasswordLock* p1 = new PasswordLock("IPhone", "Requires password to unlock",
false, "9863HiTheRe");

  EXPECT_EQ(p->getName(), "Object");
  EXPECT_EQ(p->getDescription(), "This object does nothing");
  EXPECT_EQ(p->isHoldable(), true);
  EXPECT_EQ(p->isPuzzleSolved(), false);

  //p->interact();
  //After the interact has been solved
  //EXPECT_EQ(p->isPuzzleSolved(), true);

  EXPECT_EQ(p1->getName(), "IPhone");
  EXPECT_EQ(p1->getDescription(), "Requires password to unlock");
  EXPECT_EQ(p1->isHoldable(), false);
  EXPECT_EQ(p1->isPuzzleSolved(), false);

  //p1->interact();
  //After the interact has been solved
  //EXPECT_EQ(p1->isPuzzleSolved(), true);
  delete p;
  delete p1;
}

TEST(TestPasswordLock, interactTest) {
  PasswordLock* p = new PasswordLock();
  PasswordLock* p1 = new PasswordLock("IPhone", "Requires password to unlock",
false, "9863HiTheRe");

  EXPECT_EQ(p->isPuzzleSolved(), false);
  //p->interact();
  //After the interact has been solved
  //EXPECT_EQ(p->isPuzzleSolved(), true);

  EXPECT_EQ(p1->isPuzzleSolved(), false);
  //p1->interact();
  //After the interact has been solved
  //EXPECT_EQ(p1->isPuzzleSolved(), true);

  delete p;
  delete p1;
}
