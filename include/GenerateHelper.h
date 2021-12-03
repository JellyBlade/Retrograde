/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef GENERATE_HELPER_H
#define GENERATE_HELPER_H

#include <map>
#include <string>

#include "nlohmann/json.hpp"
#include "Object.h"
#include "Room.h"
#include "Map.h"
#include "NPC.h"

using json = nlohmann::json;

/**
* Provides functions for instantiating objects/rooms from JSON.
* @see https://github.com/nlohmann/json
*/
namespace GenerateHelper {

  extern std::map<std::string, json> jsonObjects;
  extern std::map<std::string, json> jsonRooms;
  extern std::map<std::string, json> jsonNPCs;

  /**
  * Populates the objects and rooms vectors for the other functions to use.
  * Does not need to be called independently.
  */
  void setup();

  /**
  * Generates an Object from JSON based on the name.
  * @param objectName The name of the object to generate.
  * @return The JSON-generated object.
  */
  Object* generateObject(std::string objectName);

  /**
  * Generates an NPC from JSON based on the name.
  * @param npcName The name of the NPC to generate.
  * @return the JSON-generated NPC.
  */
  NPC* generateNPC(std::string npcName);

  /**
  * Generates a Room from JSON, with room objects if available.
  * @param roomName the name of the room to generate.
  * @return the JSON-generated room.
  */
  Room* generateRoom(std::string roomName);

  /**
  * Generates all of the rooms, doors, and objects for the map.
  * @param mapName the map to generate, used for the file name.
  */
  Map* generateMap(std::string mapName);

} // namespace GenerateHelper

#endif // GENERATE_HELPER_H
