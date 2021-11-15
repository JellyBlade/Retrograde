/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "Inventory.h"
#include "Room.h"

/**
* The game's representation of the user. Keeps track of inventory,
* room position, oxygen usage, and player name.
*/
class Player {
 public:
  /**
  * Default constructor, creates a new inventory.
  */
  Player();

  /**
  * Destructor.
  */
  virtual ~Player();

  /**
  * Returns the player's current room.
  * @return the Room the player is in.
  */
  Room* getCurrentRoom();

  /**
  * Returns the player's inventory.
  * @return the player's Inventory class
  */
  Inventory* getInventory();

  /**
  * Gets the player's name.
  * @return a string of the player's name.
  */
  std::string getPlayerName();

  /**
  * Checks if the player has unlocked the spacesuit. Used for survival in a
  * vacuum, and to solve certain puzzles.
  * @return true if the player has unlocked the spacesuit, false otherwise.
  */
  bool hasSpaceSuit();

  /**
  * Moves the player to the given Room.
  * @param room the Room to move to.
  */
  void setCurrentRoom(Room* room);

  /**
  * Changes the player's name
  * @param name the string to set the player's name to.
  */
  void setPlayerName(std::string name);

  /**
  * Reduces the oxygen of the player's current room, or (if unlocked) from
  * their spacesuit's oxygen level if the room has none.
  * @return true if the player has used oxygen successfully, or false if there
  * wasn't enough oxygen to breathe, and the player should be killed.
  */
  bool useOxygen();

 private:
  Room* currentRoom;
  Inventory* inventory;
  std::string playerName;
};

#endif // PLAYER_H
