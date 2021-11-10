/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <string>

#include "TextHelper.h"
#include "gtest/gtest.h"

TEST(TestTextHelper, readFileTest) {
  TextHelper::readFile("WIP");
}

TEST(TestTextHelper, commandProcessorTest) {
  TextHelper::commandProcessor("WIP");
}

TEST(TestTextHelper, tolowerTest) {
  std::string s = "Test";
  EXPECT_NE(s, "test");
  EXPECT_EQ(TextHelper::tolower(s), "test");
}

TEST(TestTextHelper, toupperTest) {
  std::string s = "Test";
  EXPECT_NE(s, "TEST");
  EXPECT_EQ(TextHelper::tolower(s), "TEST");
}

TEST(TestTextHelper, trimTest) {
  std::string s = "   test me  ";
  EXPECT_NE(s.size(), 7);
  EXPECT_NE(s, "test me");
  s = TextHelper::trim(s);
  EXPECT_EQ(s.size(), 7);
  EXPECT_EQ(s, "test me");
}

TEST(TestTextHelper, trimAllTest) {
  std::string s = "  t e             s t";
  EXPECT_NE(s.size(), 4);
  EXPECT_NE(s, "test");
  s = TextHelper::trimAll(s);
  EXPECT_EQ(s.size(), 4);
  EXPECT_EQ(s, "test");
}
