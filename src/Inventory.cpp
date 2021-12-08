/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>

#include "Inventory.h"

Inventory::Inventory() {
  spaceSuitAcquired = false;
  oxygen = 0;
}

Inventory::~Inventory() {
  this->clear();
}

void Inventory::giveSpaceSuit() {
  std::cout << "Spacesuit acquired!" << std::endl;
  spaceSuitAcquired = true;
  oxygen = 10000;
  std::cout << "You can now survive in a vacuum!" << std::endl;
}

bool Inventory::hasSpaceSuit() {
  return spaceSuitAcquired;
}

int Inventory::getOxygen() {
  return oxygen;
}

void Inventory::setOxygen(int o) {
  if (o < 0) { oxygen = 0; }
  if (o > 10000) { oxygen = 10000; }
  oxygen = o;
}

void Inventory::addObject(Object* object) {
  if (!object->isHoldable()) {
    std::cout << "You cannot pick that up." << std::endl;
    return;
  }
  ObjectContainer::addObject(object);
  std::cout << object->getName() << " has been added to your inventory.";
  std::cout << std::endl;
}
