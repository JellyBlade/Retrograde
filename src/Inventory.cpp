/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>
#include <cmath>

#include "Inventory.h"

Inventory::Inventory() {
  spaceSuitAcquired = false;
  oxygen = 0;
}

Inventory::~Inventory() {
  this->clear();
}

void Inventory::giveSpaceSuit() {
  spaceSuitAcquired = true;
  oxygen = 1;
}

bool Inventory::hasSpaceSuit() {
  return spaceSuitAcquired;
}

double Inventory::getOxygen() {
  return oxygen;
}

void Inventory::setOxygen(double o) {
  if (o < 0) { oxygen = 0; }
  if (o > 1) { oxygen = 1; }
  oxygen = std::round(o * 1000) / 1000;
}

void Inventory::addObject(Object* object) {
  if (!object->isHoldable()) {
    std::cout << "You cannot pick that up.";
    return;
  }
  ObjectContainer::addObject(object);
}
