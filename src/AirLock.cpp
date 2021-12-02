/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>
#include <string>

#include "AirLock.h"
#include "InteractHelper.h"

AirLock::AirLock(std::string n, std::string d, bool h, int o)
: oxygenTarget{o} {
  setName(n);
  setDescription(d);
  setHoldable(h);
}

void AirLock::interact() {
  if (InteractHelper::getPlayerInventory()->hasSpaceSuit() &&
InteractHelper::getPlayerHandler()->getPlayer()->getCurrentRoom()
->getRoomOxygen() >= oxygenTarget) {
  setSolved();
} else {
  if (!InteractHelper::getPlayerInventory()->hasSpaceSuit()) {
    std::cout << "Warning! Need space suit to unlock." << std::endl;
  }
  if (InteractHelper::getPlayerHandler()->getPlayer()->getCurrentRoom()
  ->getRoomOxygen() < oxygenTarget) {
    std::cout << "Warning! The room needs more oxygen for the "
    << "pressure to be stable" << std::endl;
    std::cout << "Interact with a oxygen tank while its on the ground to "
    << "increase the room oxygen" << std::endl;
  }
}
}
