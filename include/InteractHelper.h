/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef INTERACT_HELPER_H
#define INTERACT_HELPER_H

#include <vector>

#include "Game.h"
#include "PlayerHandler.h"
#include "Map.h"
#include "NPC.h"

/**
* Provides functions for handling file reading, command strings, and modifying
* strings.
*/
namespace InteractHelper {

  extern Game* game;

  /**
  * Returns this game's Map environment for accessing all rooms/doors.
  * @return the map of all rooms and doors for this game.
  */
  Map* getMap();

  /**
  * Returns this game's PlayerHandler for accessing player inventory/position.
  * @return the PlayerHandler class for this game's player.
  */
  PlayerHandler* getPlayerHandler();

  /**
  * Returns all of the NPCs in the game.
  * @return a vector containing all NPCs.
  */
  std::vector<NPC*> getNPCs();

  /**
  * Returns a vector of NPCs that are in the given room. May be empty.
  * @param room The room to get the NPCs of.
  * @return every NPC in the given room as a vector.
  */
  std::vector<NPC*> getNPCsInRoom(Room* room);

} // namespace InteractHelper

#endif // INTERACT_HELPER_H
