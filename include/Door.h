/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef DOOR_H
#define DOOR_H

#include <string>
#include <utility>
#include "Room.h"

// Forward declaration (required to prevent issues with circular include)
class Room;

/**
* Represents a door that is between two rooms. It will have the two rooms
* which it is connected to, which players can use to switch room
*/
class Door {
 public:
  /**
  * Constructor
  */
  Door(Room* first, Room* second);

  /**
  * Destructor
  */
  ~Door();

  /**
  * Returns a pair of rooms for which this door connects.
  * @return the rooms this door connects.
  */
  std::pair<Room*, Room*> getRooms();

  /**
  * Returns the room opposing the given Room in the pair.
  * Will return a nullptr if the given room is not in the pair.
  * @param room one part of the pair.
  * @return the other room in the pair, or a nullptr if the given room isn't
  * part of the pair.
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
  std::string getBlockedReason();

  /**
  * Blocks the door for the given reason.
  * @param blockedReason the reason the door is blocked.
  */
  void blockDoor(std::string blockedReason);

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
  std::string blockedReason;
  std::pair<Room*, Room*> rooms;
};

#endif // DOOR_H
