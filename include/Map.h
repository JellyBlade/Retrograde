/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>

#include "Room.h"
#include "Door.h"

class Map {
 public:
  /**
  * Destructor. Deletes all rooms and doors in the game environment.
  */
  ~Map();

  /**
  * Returns the Room matching the given name.
  * @return the Room with the same name given, or a nullptr.
  */
  Room* getRoom(std::string name);

  /**
  * Determines if there exists a door linking the two given rooms.
  * @return true if a door exists between the two, false otherwise.
  */
  bool doesDoorExistBetween(Room* r1, Room* r2);

  /**
  * Returns all rooms in the game's environment.
  * @return a vector of all rooms.
  */
  std::vector<Room*> getRooms();

  /**
  * Returns all doors in the game's environment.
  * @return a vector of all doors.
  */
  std::vector<Door*> getDoors();

  /**
  * Adds a room onto the rooms vector
  * @param r Room* to be added to rooms
  */
  void addRoom(Room* r);

  /**
  * Adds a Door onto the doors vector
  * @param d Door* to be added to doors
  */
  void addDoor(Door* d);

  /**
  * Returns the map's average oxygen level.
  * @return double representing the mean of every room's oxygen.
  */
  int getMapOxygen();

  /**
  * Sets every room in the environment's oxygen value to the given double.
  * Also sets mapOxygen to the same.
  */
  void setAllRoomOxygen(int oxygen);

  /**
  * Propagates oxygen throughout the game map, and calculated mean oxygen level.
  */
  void calculateMapOxygen();

 private:
  std::vector<Room*> rooms;
  std::vector<Door*> doors;
  int mapOxygen;
};

#endif // MAP_H
