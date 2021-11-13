/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <vector>
#include <string>
#include <map>
#include <cmath>

#include "Room.h"
#include "Door.h"
#include "NamedThing.h"
#include "Globals.h"
#include "ObjectContainer.h"

Room::Room(std::string n, std::string d) : roomOxygen{10000} {
  setName(n);
  setDescription(d);
  roomObjects = new ObjectContainer();
}

Room::~Room() {
  delete roomObjects;
}

ObjectContainer* Room::getRoomObjects() {
  return roomObjects;
}

int Room::getRoomOxygen() {
  return roomOxygen;
}

void Room::setRoomOxygen(int oxygen) {
  //TODO(mart2720): Throw exception if oxygen is out of range?
  if (oxygen <= 0)
    roomOxygen = 0;
  else if (oxygen >= 10000)
    roomOxygen = 10000;
  else
    roomOxygen = oxygen;
}

Door* Room::getDoor(Globals::Direction direction) {
  return doors.count(direction) == 1 ? doors[direction] : nullptr;
}

void Room::setDoors(std::map<Globals::Direction, Door*> d) {
  doors = d;
}

void Room::changeDoor(Door* door, Globals::Direction direction) {
  doors[direction] = door;
}
