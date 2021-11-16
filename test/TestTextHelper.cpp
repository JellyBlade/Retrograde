/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <string>
#include <vector>

#include "TextHelper.h"
#include "gtest/gtest.h"

TEST(TestTextHelper, readFileTest) {
  TextHelper::readFile("WIP");
}

TEST(TestTextHelper, commandProcessorTest) {
  TextHelper::commandProcessor("WIP");
}

TEST(TestTextHelper, makePercentTest) {
  int i = 10000;
  EXPECT_EQ(TextHelper::makePercent(i), "100.00%");

  i = 5000;
  EXPECT_EQ(TextHelper::makePercent(i), "50.00%");

  i = 500;
  EXPECT_EQ(TextHelper::makePercent(i), "5.00%");

  i = 50;
  EXPECT_EQ(TextHelper::makePercent(i), "0.50%");

  i = 5;
  EXPECT_EQ(TextHelper::makePercent(i), "0.05%");

  i = 4839;
  EXPECT_EQ(TextHelper::makePercent(i), "48.39%");

  i = 4839;
  EXPECT_EQ(TextHelper::makePercent(i / 2), "24.19%");
}

TEST(TestTextHelper, listObjectsTest) {
  std::vector<Object*> vo;
  Object* o1 = new Object("Fire Extinguisher", "Pew pew, fire go boom!");
  Object* o2 = new Object("Umbrella", "I'm Mary Poppins y'all.");
  Object* o3 = new Object("Boomstick", "This... is my boomstick.");
  Object* o4 = new Object("Uber box", "Beyond mortal comprehension.");

  EXPECT_EQ(TextHelper::listObjects(vo), " it is empty.");

  vo.push_back(o1);
  EXPECT_EQ(TextHelper::listObjects(vo), " a Fire Extinguisher.");

  vo.push_back(o2);
  EXPECT_EQ(TextHelper::listObjects(vo),
  " a Fire Extinguisher, and an Umbrella.");

  vo.push_back(o3);
  EXPECT_EQ(TextHelper::listObjects(vo),
  " a Fire Extinguisher, an Umbrella, and a Boomstick.");

  vo.push_back(o4);
  EXPECT_EQ(TextHelper::listObjects(vo),
  " a Fire Extinguisher, an Umbrella, a Boomstick, and an Uber box.");

  delete o1;
  delete o2;
  delete o3;
  delete o4;
}
TEST(TestTextHelper, listDoorTest) {
  Room* r = new Room();
  Room* r1 = new Room();
  Room* r2 = new Room();
  Door* d = new Door(r1, r2);

  r->changeDoor(d, Globals::Direction::NORTH);
  EXPECT_EQ(TextHelper::listDoors(r), "There is a door to the north.");
  r->getDoors().clear();

  r->changeDoor(d, Globals::Direction::EAST);
  EXPECT_EQ(TextHelper::listDoors(r), "There is a door to the east.");
  r->getDoors().clear();

  delete r;
  delete r1;
  delete r2;
  delete d;
}

TEST(TestTextHelper, startsWithVowelTest) {
  EXPECT_TRUE(TextHelper::startsWithVowel("iguana"));
  EXPECT_TRUE(TextHelper::startsWithVowel("umbrella"));
  EXPECT_TRUE(TextHelper::startsWithVowel("opera"));
  EXPECT_TRUE(TextHelper::startsWithVowel("apple"));
  EXPECT_TRUE(TextHelper::startsWithVowel("elephant"));
  EXPECT_TRUE(TextHelper::startsWithVowel("    elephant    "));
  EXPECT_TRUE(TextHelper::startsWithVowel(" e l e p h ant"));

  EXPECT_FALSE(TextHelper::startsWithVowel(""));
  EXPECT_FALSE(TextHelper::startsWithVowel("consonant"));
  EXPECT_FALSE(TextHelper::startsWithVowel("vowel"));
  EXPECT_FALSE(TextHelper::startsWithVowel("papaya"));
  EXPECT_FALSE(TextHelper::startsWithVowel("yttrium"));
  EXPECT_FALSE(TextHelper::startsWithVowel(" b a l a b a l o o "));
  EXPECT_FALSE(TextHelper::startsWithVowel("357"));
  EXPECT_FALSE(TextHelper::startsWithVowel("  357"));
}

TEST(TestTextHelper, tolowerTest) {
  std::string s = "Test";
  EXPECT_NE(s, "test");
  EXPECT_EQ(TextHelper::tolower(s), "test");
}

TEST(TestTextHelper, toupperTest) {
  std::string s = "Test";
  EXPECT_NE(s, "TEST");
  EXPECT_EQ(TextHelper::toupper(s), "TEST");
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
