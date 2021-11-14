/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <vector>
#include <string>
#include <utility>
#include "Door.h"

Door::Door(Room* first, Room* second) : blocked{false}, blockedReason{""} {
  rooms.first = first;
  rooms.second = second;
}

Door::~Door() {}

std::pair<Room*, Room*> Door::getRooms() {
  return rooms;
}

Room* Door::getOtherRoom(Room* room) {
  if (!isConnectedTo(room)) { return nullptr; }
  return room == rooms.first ? rooms.second : rooms.first;
}

bool Door::isConnectedTo(Room* room) {
  if (rooms.first == room || rooms.second == room)
    return true;
  else
    return false;
}

bool Door::isDoorBlocked() {
  return blocked;
}

std::string Door::getBlockedReason() {
  return blockedReason;
}

void Door::blockDoor(std::string b) {
  blocked = true;
  blockedReason = b;
}

void Door::unblockDoor() {
  blocked = false;
  blockedReason.clear();
}

void Door::propagateOxygen() {
  if (!blocked) {
    int firOxy = rooms.first->getRoomOxygen();
    int secOxy = rooms.second->getRoomOxygen();
    if (firOxy == 0 && secOxy == 0) { return; }

    int avg = (firOxy + secOxy) / 2;
    if (avg <= 100) { avg = 0; }

    if (firOxy == 0) {
      rooms.second->setRoomOxygen(avg);
    } else if (secOxy == 0) {
      rooms.first->setRoomOxygen(avg);
    } else {
      rooms.first->setRoomOxygen(avg);
      rooms.second->setRoomOxygen(avg);
    }
  }
}
