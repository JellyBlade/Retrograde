/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef PLAYER_HANDLER_H
#define PLAYER_HANDLER_H

#include <iostream>
#include <vector>
#include <string>

#include "Player.h"
#include "NPC.h"
#include "TextHelper.h"
#include "Globals.h"

/**
* Handles user interaction for the game.
*/
class PlayerHandler {
 public:
  /**
  * Default constructor. Creates a new Player.
  */
  PlayerHandler();

  /**
  * Deconstructor. Deletes the Player.
  */
  ~PlayerHandler();

  /**
  * Returns the Player class owned by this PlayerHandler.
  * @return the Player* this class handles.
  */
  Player* getPlayer();

  /**
  * Prompts user for what to do, converting the input into player actions.
  */
  void input();

  /**
  * Moves the player between rooms using the door in the given direction.
  * @param direction the cardinal direction to go.
  * @return true if the player has successfully been moved, false otherwise.
  */
  bool movePlayer(Globals::Direction direction);

  /**
  * Outputs the room's name and description to the screen, and lists off
  * the objects in the room, and possible directions to travel.
  */
  void look();

  /**
  * Examines the given object in the room, giving a description of it.
  * @param examine the name of the object to examine.
  * @return true if the object was successfully examined, false otherwise.
  */
  bool examine(std::string examine);

  /**
  * Displays all of the item's in the player's inventory in a bullet-point list.
  *
  */
  void showInventory();

  /**
  * Picks up the given object from the room, adding it the player's inventory.
  * @param pickUp the name of the object to pick up.
  * @return true if the item was successfully picked up, false otherwise.
  */
  bool pickUp(std::string pickUp);

  /**
  * Drops the given object from the player's inventory into the room.
  * @param drop the name of the object to drop.
  * @return true if the item was successfully dropped, false otherwise.
  */
  bool drop(std::string drop);

  // TODO(hipt2720): Should this function be moved somewhere else?
  /**
  * Returns a list of the NPCs in the player's current room.
  * @return a vector containing all of the NPCs in the player's current room.
  * May be empty.
  */
  std::vector<NPC*> getNPCsInCurrentRoom();

 private:
  Player* player;
};

#endif // PLAYER_HANDLER_H
