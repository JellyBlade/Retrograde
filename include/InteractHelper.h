/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef INTERACT_HELPER_H
#define INTERACT_HELPER_H

#include <vector>
#include <string>

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
  extern int chapter;

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
  * Returns the player's inventory.
  * Shortcut for getPlayerHandler()->getPlayer()->getInventory()
  * @return the player's Inventory class, containing bag items and oxygen.
  */
  Inventory* getPlayerInventory();

  /**
  * Returns the NPC with the given name.
  * @return NPC class associated with that name, or a nullptr.
  */
  NPC* getNPC(std::string name);

  /**
  * Checks if the NPC is in the given room.
  * @return true if the NPC is in the room, false otherwise.
  */
  bool npcInRoom(NPC* npc, Room* room);

  /**
  * Checks if the NPC with the given name is in the given room.
  * Calls getNPC and npcInRoom(NPC*, Room*)
  * @return true if the NPC with that name is in the room,false otherwise.
  */
  bool npcInRoom(std::string npcName, Room* room);

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
