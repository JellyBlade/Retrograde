/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <fstream>

#include "Puzzle.h"
#include "gtest/gtest.h"

TEST(TestPuzzle, everythingTest) {
  Puzzle* p = new Puzzle();
  std::ifstream file("test/text/puzzleTest_empty.txt");

  EXPECT_EQ(p->isPuzzleSolved(), false);
  p->setSolved(file);
  EXPECT_EQ(p->isPuzzleSolved(), true);

  delete p;
}
