/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <vector>
#include <string>
#include <utility>
#include "Door.h"

Door::Door() {
  blocked = true;
  blockedReason = "This is a wall.";
}

Door::Door(Room* first, Room* second) {
  rooms.first = first;
  rooms.second = second;
}

Door::~Door() {
  delete rooms.first;
  delete rooms.second;
}

std::pair<Room*, Room*> Door::getRooms() {
  return rooms;
}

Room* Door::getOtherRoom(Room* room) {
  if (!isConnectedTo(room)) { return nullptr; }
  if (room == rooms.first) {
    return rooms.second;
  }
  return rooms.first;
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
  // if (!blocked) {
  //   double firOxy = rooms.first->getRoomOxygen();
  //   double secOxy = rooms.second->getRoomOxygen();
  //   if (firOxy == 0 && secOxy == 0) { return; }
  //
  //   double avg = (firOxy + secOxy) / 2;
  //   if (avg <= 0.01) { avg = 0; }
  //
  //   if (firOxy == 0) {
  //     rooms.second->setRoomOxygen(avg);
  //   } else if (secOxy == 0) {
  //     rooms.first->setRoomOxygen(avg);
  //   } else {
  //     rooms.first->setRoomOxygen(avg);
  //     rooms.second->setRoomOxygen(avg);
  //   }
  // }
}
