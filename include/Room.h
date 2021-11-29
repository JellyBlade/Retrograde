/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include <map>
#include "Door.h"
#include "NamedThing.h"
#include "Globals.h"
#include "ObjectContainer.h"

// Forward declaration (required to prevent issues with circular include)
class Door;

class Room : public NamedThing {
 public:
  /**
  * Constructor
  */
  Room(std::string name = "Room", std::string description = "Empty room");

  /**
  * Destructor
  */
  ~Room();

  /**
  * Adds the given object to the Room.
  * A shorthand for room->getRoomObjects()->addObject();
  * @param object the Object to add to the room.
  */
  void addObject(Object* object);

  /**
  * Returns this room's ObjectContainer containing all of its contents.
  * @return this room's ObjectContainer.
  */
  ObjectContainer* getRoomObjects();

  /**
  * Returns the amount of oxygen remaining in this room.
  * @return a double for the oxygen level.
  */
  int getRoomOxygen();

  /**
  * Sets the room's oxygen level to the given double.
  */
  void setRoomOxygen(int oxygen);

  /**
  * Returns the this room's door in the given direction.
  * Will return a nullptr if there is no door in that direction (it is a wall).
  * @param direction the cardinal direction to get a door from.
  * @return a door, or a nullptr if there isn't a door.
  */
  Door* getDoor(Globals::Direction direction);

  /**
  * Returns all of this room's doors.
  * @return a map of the this room's doors mapped to the cardinal directions.
  */
  std::map<Globals::Direction, Door*> getDoors();

  /**
  * Replaces this room's doors with the given map.
  */
  void setDoors(std::map<Globals::Direction, Door*> d);

  /**
  * Replaces the door at the given direction with the given door.
  */
  void changeDoor(Door* door, Globals::Direction direction);

 private:
  int roomOxygen;
  ObjectContainer* roomObjects;
  std::map <Globals::Direction, Door*> doors;
};

#endif // ROOM_H
