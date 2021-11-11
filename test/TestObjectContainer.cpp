/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <string>

#include "Object.h"
#include "gtest/gtest.h"
#include "ObjectContainer.h"

TEST(TestObjectContainer, addRemoveTest) {
  Object* o1 = new Object("Test", "This object loves to test!");
  Object* o2 = new Object();
  ObjectContainer* ob = new ObjectContainer();

  // TODO(hipt2720): Expections.h is needed here
  //EXPECT_THROW(ob->addObject(NULL), invalid_parameter_error);

  EXPECT_EQ(ob->size(), 0);
  ob->addObject(o1);
  EXPECT_EQ(ob->size(), 1);
  ob->addObject(o2);
  EXPECT_EQ(ob->size(), 2);

  ob->removeObject(o1);
  EXPECT_EQ(ob->size(), 1);

  delete o1;
  delete ob;
}

TEST(TestObjectContainer, clearTest) {
  Object* o1 = new Object();
  Object* o2 = new Object();
  ObjectContainer* ob = new ObjectContainer();

  ob->addObject(o1);
  ob->addObject(o2);
  EXPECT_EQ(ob->size(), 2);
  ob->clear();
  EXPECT_EQ(ob->size(), 0);

  delete ob;
}

TEST(TestObjectContainer, getTest) {
  Object* o1 = new Object("Test", "This object loves to test!");
  Object* o2 = new Object("AngryTest", "This object hates to test!");
  Object* o3 = new Object();
  ObjectContainer* ob = new ObjectContainer();

  ob->addObject(o1);
  ob->addObject(o3);

  EXPECT_EQ(ob->getObjects().size(), 2);
  EXPECT_EQ(ob->getObject("Test"), o1);
  EXPECT_EQ(ob->getObject("test"), o1);
  EXPECT_EQ(ob->getObject("  tEsT  "), o1);
  EXPECT_EQ(ob->getObject("  t  e s t"), o1);

  EXPECT_TRUE(ob->isObjectInContainer(o1));
  EXPECT_TRUE(ob->isObjectInContainer("Test"));
  EXPECT_TRUE(ob->isObjectInContainer("test"));
  EXPECT_TRUE(ob->isObjectInContainer("  tEsT   "));
  EXPECT_TRUE(ob->isObjectInContainer("  t e s t"));
  EXPECT_FALSE(ob->isObjectInContainer(o2));
  EXPECT_FALSE(ob->isObjectInContainer("AngryTest"));

  EXPECT_EQ(ob->getObject("AngryTest"), nullptr);
  EXPECT_EQ(ob->getObject(""), nullptr);
  EXPECT_EQ(ob->getObject("#*IK#*fjasd"), nullptr);

  delete ob;
  delete o2;
}
