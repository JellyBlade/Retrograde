/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/
#include <iostream>

#include "OxygenTank.h"
#include "Game.h"
#include "InteractHelper.h"

void OxygenTank::interact() {
  if (InteractHelper::getPlayerInventory()->hasSpaceSuit()) {
    InteractHelper::getPlayerInventory()->setOxygen(10000);
  } else {
    std::cout << "No space suit to restore oxygen." << std::endl;
  }
}
