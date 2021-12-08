/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/
#include <iostream>
#include <string>

#include "OxygenTank.h"
#include "Game.h"
#include "InteractHelper.h"

OxygenTank::OxygenTank(std::string n, std::string d, bool h) {
  setName(n);
  setDescription(d);
  setHoldable(h);
}

void OxygenTank::interact() {
  if (InteractHelper::getPlayerInventory()->hasSpaceSuit() &&
InteractHelper::getPlayerInventory()->isObjectInContainer(this)) {
    InteractHelper::getPlayerInventory()->setOxygen(10000);
  } else if (InteractHelper::getPlayerHandler()->getPlayer()->getCurrentRoom()
  ->getRoomObjects()->isObjectInContainer(this)) {
    InteractHelper::getPlayerHandler()->getPlayer()->getCurrentRoom()
    ->setRoomOxygen(10000);
  }
}
