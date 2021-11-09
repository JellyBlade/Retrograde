/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef DOOR_H
#define DOOR_H

#include <string>
#include <utility>

#include "Room.h"

class Door {
 public:
  /**
  * Default constructor. Makes this door function like a wall.
  */
  Door();

  /**
  * Constructor
  */
  Door(Room* first, Room* second);

  /**
  * Returns a pair of rooms for which this door connects.
  * @return the rooms this door connects.
  */
  pair<Room*, Room*> getRooms();

  /**
  * Returns the room opposing the given Room in the pair.
  * @param room one part of the pair.
  */
  Room* getOtherRoom(Room* room);

  /**
  * Checks if the given room is part of the pair of rooms.
  * @param room the room to check.
  */
  bool isConnectedTo(Room* room);

  /**
  * Checks if the door is able to be moved through.
  * @return true if the door is blocked, false otherwise.
  */
  bool isDoorBlocked();

  /**
  * Returns the reason the door is blocked.
  * @return a string for why the door is blocked.
  */
  string getBlockedReason();

  /**
  * Blocks the door for the given reason.
  * @param blockedReason the reason the door is blocked.
  */
  void blockDoor(string blockedReason);

  /**
  * Unblocks the door, allowing for travel between the room pair.
  */
  void unblockDoor();

  /**
  * Averages oxygen levels between the rooms in the pair,
  * setting both to 0 if the average is <= 0.01.
  * Will not propagate if the door is blocked.
  */
  void propagateOxygen();

 private:
  bool blocked;
  string blockedReason;
  pair<Room*, Room*> rooms;
}

#endif // DOOR_H
