/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>
#include <string>

#include "ItemLock.h"

ItemLock::ItemLock(std::string n, std::string d, bool h, std::string m)
: matchingName{m} {
  setName(n);
  setDescription(d);
  setHoldable(h);
}

void ItemLock::interact() {
  //TODO(mart2720): Implement later
}
