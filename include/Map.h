#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>

#include "Room.h"
#include "Door.h"

class Map {
 public:
  /**
  * Returns the Room matching the given name.
  * @return the Room with the same name given, or a nullptr.
  */
  Room* getRoom(string name);

  /**
  * Returns all rooms in the game's environment.
  * @return a vector of all rooms.
  */
  vector<Room*> getRooms();

  /**
  * Returns all doors in the game's environment.
  * @return a vector of all doors.
  */
  vector<Door*> getDoors();

  /**
  * Returns the map's average oxygen level.
  * @return double representing the mean of every room's oxygen.
  */
  double getMapOxygen();

  /**
  * Sets every room in the environment's oxygen value to the given double.
  * Also sets mapOxygen to the same.
  */
  void setAllRoomOxygen(double oxygen);

  // TODO(hipt2720): This function could likely handle room oxygen propagation.
  /**
  * Sets mapOxygen to the mean of all room oxygen levels
  */
  void calculateMapOxygen();

 private:
  vector<Room*> rooms;
  vector<Door*> doors;
  double mapOxygen;
}

#endif // MAP_H
