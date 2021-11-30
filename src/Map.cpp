/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <vector>
#include <string>
#include <iostream>

#include "Map.h"
#include "TextHelper.h"

Map::~Map() {
  for (int i = 0; i < rooms.size(); i++) {
    delete rooms[i];
  }
  for (int i = 0; i < doors.size(); i++) {
    delete doors[i];
  }
  rooms.clear();
  doors.clear();
}

//TODO(mart2720): Should this funciton and setAllRoomOxygen throw
// exceptions if there are no elements in the vectors?
Room* Map::getRoom(std::string n) {
  // if (this->rooms.size() == 0) { throw exception; }
  for (int i = 0; i < rooms.size(); i++) {
    if (TextHelper::tolower(TextHelper::trimAll(rooms.at(i)->getName())) ==
    TextHelper::tolower(TextHelper::trimAll(n))) {
      return rooms.at(i);
    }
  }
  return nullptr;
}

bool Map::doesDoorExistBetween(Room* r1, Room* r2) {
  for (Door* d : doors) {
    if (d->isConnectedTo(r1) && d->isConnectedTo(r2)) {
      return true;
    }
  }
  return false;
}

std::vector<Room*> Map::getRooms() {
  return rooms;
}

std::vector<Door*> Map::getDoors() {
  return doors;
}

int Map::getMapOxygen() {
  return mapOxygen;
}

void Map::setAllRoomOxygen(int oxygen) {
  // if(rooms.size() == 0) { throw exception; }
  for (Room* r : rooms) {
    r->setRoomOxygen(oxygen);
  }
  mapOxygen = oxygen;
}

void Map::calculateMapOxygen() {
  // if (room.size() == 0) { throw exception; }
  // if (doors.size() == 0) { throw exception; }
  int temp = 0;
  for (Door* d : doors) {
    d->propagateOxygen();
  }
  for (Room* r : rooms) {
    temp += r->getRoomOxygen();
  }
  temp /= rooms.size();
  mapOxygen = temp;
}

void Map::addRoom(Room* r) {
  rooms.push_back(r);
}

void Map::addDoor(Door* d) {
  doors.push_back(d);
}
