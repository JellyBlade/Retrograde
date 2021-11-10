/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef PLAYER_HANDLER_H
#define PLAYER_HANDLER_H

#include <iostream>
#include <vector>

#include "Player.h"
#include "NPC.h"
#include "HelperFunctions.h"

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
  */
  void movePlayer(HelperFunctions::Direction direction);

  /**
  * Picks up the given object from the room, adding it the player's inventory.
  * @param pickUp the object to pick up.
  */
  void pickUp(Object* pickUp);

  /**
  * Drops the given object from the player's inventory into the room.
  * @param drop the object to drop.
  */
  void drop(Object* drop);

  // TODO(hipt2720): Should this function be moved somewhere else?
  /**
  * Returns a list of the NPCs in the player's current room.
  * @return a vector containing all of the NPCs in the player's current room.
  * May be empty.
  */
  vector<NPC*> getNPCsInCurrentRoom();

 private:
  Player* player;
};

#endif // PLAYER_HANDLER_H
