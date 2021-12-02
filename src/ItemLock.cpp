/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>
#include <string>

#include "InteractHelper.h"
#include "ItemLock.h"
#include "TextHelper.h"

ItemLock::ItemLock(std::string n, std::string d, bool h, std::string m)
: matchingName{m} {
  setName(n);
  setDescription(d);
  setHoldable(h);
}

void ItemLock::interact() {
  if (InteractHelper::getPlayerInventory()->isObjectInContainer(matchingName)) {
    setSolved();
    std::cout << "The " << matchingName << " unlocked it." << std::endl;
  } else {
    std::cout << "You need to have the " << TextHelper::tolower(matchingName)
    << " in order to access this " <<
    TextHelper::tolower(this->getName()) << std::endl;
  }
}
