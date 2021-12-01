/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>
#include <fstream>
#include <string>

#include "PasswordLock.h"
#include "gtest/gtest.h"

TEST(TestPasswordLock, interactTest) {
  PasswordLock* p = new PasswordLock();
  PasswordLock* p1 = new PasswordLock("IPhone", "Requires password to unlock",
false, "9863HiTheRe");
  std::ifstream file("test/text/passwordLockTest.txt");


  EXPECT_EQ(p->isPuzzleSolved(), false);
  EXPECT_FALSE(p->playerInput(file));
  EXPECT_EQ(p->isPuzzleSolved(), false);
  EXPECT_TRUE(p->playerInput(file));
  EXPECT_EQ(p->isPuzzleSolved(), true);

  EXPECT_EQ(p1->isPuzzleSolved(), false);
  EXPECT_FALSE(p1->playerInput(file));
  EXPECT_EQ(p1->isPuzzleSolved(), false);
  EXPECT_TRUE(p1->playerInput(file));
  EXPECT_EQ(p1->isPuzzleSolved(), true);

  delete p;
  delete p1;
}
