/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>

#include "Door.h"
#include "NamedThing.h"
#include "Globals.h"
#include "ObjectContainer.h"

class Room : public NamedThing {
 public:
  /**
  * Default constructor
  */
  Room();

  /**
  * Constructor
  */
  Room(string name, string description);

  /**
  * Returns this room's ObjectContainer containing all of its contents.
  * @return this room's ObjectContainer.
  */
  ObjectContainer* getRoomObjects();

  /**
  * Returns the amount of oxygen remaining in this room.
  * @return a double for the oxygen level.
  */
  double getRoomOxygen();

  /**
  * Sets the room's oxygen level to the given double.
  */
  void setRoomOxygen(double oxygen);

  /**
  * Returns this room's doors.
  * @return a vector of four doors for each cardinal direction.
  */
  vector<Door*> getDoors();

  /**
  * Replaces this room's doors with the given vector.
  */
  void setDoors(vector<Door*> doors);

  /**
  * Replaces the door at the given direction with the given door.
  */
  void changeDoor(Door* door, Globals::Direction);

 private:
  double roomOxygen;
  ObjectContainer* roomObjects;
  vector<Door*> doors;
}

#endif // ROOM_H
