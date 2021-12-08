/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include "Log.h"
#include "gtest/gtest.h"

TEST(TestLog, interactTest) {
  Log* l = new Log("test/text/log.txt");

  l->interact();

  delete l;
}
