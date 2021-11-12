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
  doors[Globals::Direction::NORTH] = new Door();
  doors[Globals::Direction::EAST] = new Door();
  doors[Globals::Direction::SOUTH] = new Door();
  doors[Globals::Direction::WEST] = new Door();
}

Room::~Room() {
  delete roomObjects;
  std::map <Globals::Direction, Door*>::iterator it;
  for(it = doors.begin(); it != doors.end(); ++it) {
    //delete (*it).second;
  }
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

std::map<Globals::Direction, Door*> Room::getDoors() {
  return doors;
}

void Room::setDoors(std::map<Globals::Direction, Door*> d) {
  doors = d;
}

void Room::changeDoor(Door* door, Globals::Direction direction) {
  delete doors[direction];
  doors[direction] = door;
}
