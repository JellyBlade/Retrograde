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
  blocked = true;
  blockedReason = "This is a wall.";
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

Room* getOtherRoom(Room* room) {
  return rooms.second;
}

bool isConnectedTo(Room* room) {
  /*
  TODO(Mart2720): This probably wont work becuase ==operator isnt overloaded
  will have to fix later if this doesnt work
  */
  if (rooms->first == room || rooms->second == room)
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
  //TODO(mart2720): After the Room class has been implmented.
  /*if(!blocked) {
    double temp = rooms.first->getRoomOxygen() +
    rooms.second->getRoomOxygen() / 2;
    if(rooms.first->getRoomOxygen() == 0 ||
    rooms.second->getRoomOxygen() == 0) {
      rooms.first->setRoomOxygen(temp * 0.95);
      rooms.first->setRoomOxygen(temp * 0.95);
    }
    rooms.first->setRoomOxygen(temp);
    rooms.first->setRoomOxygen(temp);
  }*/ //THese comments can be removed after the Room has been implemented.
}
