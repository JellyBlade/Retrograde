/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <vector>
#include <string>
#include <iostream>

#include "Map.h"
#include "TextHelper.h"

Room* Map::getRoom(std::string n) {
  if(rooms.size() == 0)
    return nullptr;
  for(Room* r : rooms) {
    if (TextHelper::tolower(TextHelper::trimAll(r->getName())) ==
    TextHelper::tolower(TextHelper::trimAll(n)))
      return r;
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
  for(Room* r : rooms) {
    r->setRoomOxygen(oxygen);
  }
  mapOxygen = oxygen;
}

void Map::calculateMapOxygen() {
  //TODO(mart2720): This function will need to
  //                change if we do oxygen propagation
  double temp = 0;
  for(Room* r : rooms) {
    temp += r->getRoomOxygen();
  }
  temp /= rooms.size();
  mapOxygen = temp;
}
