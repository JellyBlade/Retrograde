/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <string>

#include "Player.h"

Player::Player() {
  inventory = new Inventory();
}

Player::~Player() {
  delete inventory;
}

Room* Player::getCurrentRoom() {
  return currentRoom;
}

Inventory* Player::getInventory() {
  return inventory;
}

std::string Player::getPlayerName() {
  return playerName;
}

bool Player::hasSpaceSuit() {
  return inventory->hasSpaceSuit();
}

void Player::setCurrentRoom(Room* room) {
  // if (room == NULL) { throw exception; }
  currentRoom = room;
}

void Player::setPlayerName(std::string name) {
  playerName = name;
}

bool Player::useOxygen() {
  if (hasSpaceSuit() && currentRoom->getRoomOxygen() == 0) {
    if (inventory->getOxygen() < 500) {
      return false;
    }
    inventory->setOxygen(inventory->getOxygen() - 500);
    return true;
  }
  if (currentRoom->getRoomOxygen() < 500) { return false; }
  currentRoom->setRoomOxygen(currentRoom->getRoomOxygen() - 500);
  return true;
}
