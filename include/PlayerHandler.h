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
  * Returns true if the action performed is expected to use up oxygen supply.
  * @param input istream to use for player-input. Use std::cin for player input,
  * or an ifstream for automated testing.
  * @return true if the action performed consumed oxygen and was successful.
  * Will return false if the action was invalid.
  */
  bool input(std::istream& input);

  /**
  * Moves the player between rooms using the door in the given direction.
  * @param direction the cardinal direction to go.
  * @return true if the player has successfully been moved, false otherwise.
  */
  bool movePlayer(Globals::Direction direction);

  /**
  * Interacts with the given object in the room/inventory.
  * @see Object::interact()
  * @param interact the name of the object to interact with.
  * @return true if the object was successfully interacted with, false otherwise
  */
  bool interact(std::string interact);

  /**
  * Outputs the room's name and description to the screen, and lists off
  * the objects in the room, and possible directions to travel.
  */
  void look();

  /**
  * Outputs spacesuit and room oxygen levels to the screen.
  */
  void status();

  /**
  * Examines the given object in the room/inventory, giving a description of it.
  * @param examine the name of the object to examine.
  * @return true if the object was successfully examined, false otherwise.
  */
  bool examine(std::string examine);

  /**
  * Examines the given direction, displaying the blocked status of the Door
  * and which room is in that direction, if possible.
  */
  bool examine(Globals::Direction direction);

  /**
  * Examines the given NPC, providing their description and name.
  * @param examine the NPC to examine.
  * @return true if the NPC was successfully examined, false otherwise.
  */
  bool examine(NPC* npc);

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

 private:
  Player* player;
};

#endif // PLAYER_HANDLER_H
