/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include "Puzzle.h"
#include "gtest/gtest.h"

TEST(TestPuzzle, everythingTest) {
  Puzzle* p = new Puzzle();

  EXPECT_EQ(p->isPuzzleSolved(), false);
  p->setSolved();
  EXPECT_EQ(p->isPuzzleSolved(), true);

  delete p;
}
