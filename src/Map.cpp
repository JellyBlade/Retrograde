/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <vector>
#include <string>
#include <iostream>

#include "Map.h"
#include "TextHelper.h"

//TODO: Should this funciton and setAllRoomOxygen throw exceptions if there are
// no elements in the vectors?
Room* Map::getRoom(std::string n) {
  /*This may need to happen if we include the exceptions being thrown
  if (this->rooms.size() < 1)
    throw exception;
  */
  for (int i = 0; i < rooms.size(); i++) {
    if (TextHelper::tolower(TextHelper::trimAll(rooms.at(i)->getName())) ==
    TextHelper::tolower(TextHelper::trimAll(n))) {
      return rooms.at(i);
    }
  }
  return nullptr;
}

std::vector<Room*> Map::getRooms() {
  return rooms;
}

std::vector<Door*> Map::getDoors() {
  return doors;
}

double Map::getMapOxygen() {
  return mapOxygen;
}

void Map::setAllRoomOxygen(double oxygen) {
  /*
  if(rooms.size() == 0)
    throw exception
  */
  for (Room* r : rooms) {
    r->setRoomOxygen(oxygen);
  }
  mapOxygen = oxygen;
}

void Map::calculateMapOxygen() {
  //TODO(mart2720): This function will need to
  //                change if we do oxygen propagation
  double temp = 0;
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
