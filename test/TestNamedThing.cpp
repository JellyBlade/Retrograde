/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>
#include <string>
#include "NamedThing.h"
#include "gtest/gtest.h"

TEST(TestNamedThing, ConstructorTest) {
  NamedThing* n1 = new NamedThing("Object", "Loves to hug");
  NamedThing* n2 = new NamedThing();

  EXPECT_EQ(n1->getName(), "Object");
  EXPECT_EQ(n1->getName().size(), 6);
  EXPECT_EQ(n1->getDescription(), "Loves to hug");
  EXPECT_EQ(n1->getDescription().size(), 12);
  EXPECT_EQ(n2->getName(), "Thing");
  EXPECT_EQ(n2->getName().size(), 5);
  EXPECT_EQ(n2->getDescription(), "Does nothing");
  EXPECT_EQ(n2->getDescription().size(), 12);

  delete n1;
  delete n2;
}

TEST(TestNamedThing, settersTest) {
  NamedThing* n1 = new NamedThing("Object", "Loves to hug");
  std::string s = "Map";
  std::string d = "This astronomical map is loaded with wondering creatures.";

  EXPECT_EQ(n1->getName(), "Object");
  EXPECT_EQ(n1->getDescription(), "Loves to hug");
  n1->setName(s);
  n1->setDescription(d);
  EXPECT_EQ(n1->getName(), "Map");
  EXPECT_EQ(n1->getDescription(),
  "This astronomical map is loaded with wondering creatures.");

  delete n1;
}
