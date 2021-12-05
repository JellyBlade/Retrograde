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
  playerInput(std::cin);
}

bool ItemLock::playerInput(std::istream& input) {
  if (isPuzzleSolved()) {
    std::cout << "This " << getName() << " is already solved." << std::endl;
    return true;
  }
  if (InteractHelper::getPlayerInventory()->isObjectInContainer(matchingName)) {
    if (setSolved(input)) { return true; }
    std::cout << "The " << matchingName << " unlocked it." << std::endl;
    return true;
  } else {
    std::cout << "You need to have the " << TextHelper::tolower(matchingName)
    << " in order to access this " <<
    TextHelper::tolower(this->getName()) << std::endl;
    return false;
  }
}
