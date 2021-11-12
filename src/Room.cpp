/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <vector>
#include <string>
#include <map>
#include "Room.h"
#include "Door.h"
#include "NamedThing.h"
#include "Globals.h"
#include "ObjectContainer.h"

Room::Room(std::string n, std::string d) : roomOxygen{1.0} {
  setName(n);
  setDescription(d);
  roomObjects = new ObjectContainer();
}

Room::~Room() {
  delete roomObjects;
  doors.clear();
}

ObjectContainer* Room::getRoomObjects() {
  return roomObjects;
}

double Room::getRoomOxygen() {
  return roomOxygen;
}

void Room::setRoomOxygen(double oxygen) {
  roomOxygen = oxygen;
}

Door* Room::getDoor(Globals::Direction direction) {
  return doors.count(direction) == 1 ? doors[direction] : nullptr;
}

void Room::setDoors(std::map<Globals::Direction, Door*> d) {
  doors = d;
}

void Room::changeDoor(Door* door, Globals::Direction direction) {
  delete doors[direction];
  doors[direction] = door;
}
