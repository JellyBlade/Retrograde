/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <map>
#include <string>
#include <fstream>
#include <stdexcept>

#include "GenerateHelper.h"
#include "TextHelper.h"
#include "Globals.h"
#include "Map.h"
#include "Door.h"
#include "Object.h"
#include "Log.h"
#include "OxygenTank.h"
#include "ItemLock.h"
#include "PasswordLock.h"
#include "Box.h"
#include "LockedBox.h"
#include "AirLock.h"
#include "NPC.h"

using json = nlohmann::json;

std::map<std::string, json> GenerateHelper::jsonObjects;
std::map<std::string, json> GenerateHelper::jsonRooms;
std::map<std::string, json> GenerateHelper::jsonNPCs;

void GenerateHelper::setup() {
  if (jsonObjects.size() < 1) {
    std::ifstream file("text/json/objects.json");
    if (!file.is_open()) {
      // Not testable
      throw std::runtime_error("objects.json not found!");
    }
    try {
      json j = json::parse(file);
      for (auto it = j.begin(); it != j.end(); ++it) {
        jsonObjects[it.key()] = it.value();
      }
      // Not testable
    } catch (json::parse_error& e) {
      std::cout << "Error occurred while reading objects.json" << std::endl;
      throw(e);
    }
    file.close();
  }
  if (jsonRooms.size() < 1) {
    std::ifstream file("text/json/rooms.json");
    if (!file.is_open()) {
      // Not testable
      throw std::runtime_error("rooms.json not found!");
    }
    try {
      json j = json::parse(file);
      for (auto it = j.begin(); it != j.end(); ++it) {
        jsonRooms[it.key()] = it.value();
      }
      // Not testable
    } catch (json::parse_error& e) {
      std::cout << "Error occurred while reading rooms.json" << std::endl;
      throw(e);
    }
    file.close();
  }
  if (jsonNPCs.size() < 1) {
    std::ifstream file("text/json/npcs.json");
    if (!file.is_open()) {
      // Not testable
      throw std::runtime_error("npcs.json not found!");
    }
    try {
      json j = json::parse(file);
      for (auto it = j.begin(); it != j.end(); ++it) {
        jsonNPCs[it.key()] = it.value();
      }
      // Not testable
    } catch (json::parse_error& e) {
      std::cout << "Error occurred while reading npcs.json" << std::endl;
      throw(e);
    }
    file.close();
  }
}

Object* GenerateHelper::generateObject(std::string objectName) {
  try {
    if (jsonObjects.size() < 1) { setup(); }
    // Not testable
  } catch (std::runtime_error& e) {
    throw(e);
  }
  for (auto& o : jsonObjects) {
    if (TextHelper::keyify(objectName) == o.first
    || TextHelper::tolower(TextHelper::trimAll(o.second["name"]))
    == TextHelper::tolower(TextHelper::trimAll(objectName))) {
      if (o.second.contains("box")) {
        Box* box;
        if (o.second.contains("reqPuzzle")) {
          box = new LockedBox(o.second["name"], o.second["desc"],
          o.second["holdable"], o.second["reqPuzzle"]);
        } else {
          box = new Box(o.second["name"], o.second["desc"],
          o.second["holdable"]);
        }
        for (auto& boxObj : o.second["box"]) {
          box->addObject(generateObject(boxObj.get<std::string>()));
        }
        return box;
      } else if (o.second.contains("password")) {
        return new PasswordLock(o.second["name"], o.second["desc"],
        o.second["holdable"], o.second["password"]);
      } else if (o.second.contains("oxygenTankReuse")) {
        return new OxygenTank(o.second["name"], o.second["desc"],
        o.second["holdable"]);
      } else if (o.second.contains("reqItem")) {
        return new ItemLock(o.second["name"], o.second["desc"],
        o.second["holdable"], o.second["reqItem"]);
      } else if (o.second.contains("reqOxygen")) {
        return new AirLock(o.second["name"], o.second["desc"],
        o.second["holdable"], o.second["reqOxygen"]);
      } else if (o.second.contains("logFile")) {
        return new Log(o.second["name"], o.second["desc"],
        o.second["holdable"], o.second["logFile"]);
      } else {
        return new Object(o.second["name"], o.second["desc"],
        o.second["holdable"]);
      }
    }
  }
  throw std::runtime_error("Invalid Object with name: " + objectName
  + ". Check spelling and ensure this object is defined in objects.json!");
}

NPC* GenerateHelper::generateNPC(std::string npcName) {
  try {
    if (jsonNPCs.size() < 1) { setup(); }
  // Not testable
  } catch (std::runtime_error& e) {
    throw(e);
  } catch (json::parse_error& e) {
    throw(e);
  }
  for (auto& n : jsonNPCs) {
    if (TextHelper::keyify(npcName) == n.first
    || TextHelper::tolower(TextHelper::trimAll(n.second["name"]))
    == TextHelper::tolower(TextHelper::trimAll(npcName))) {
      return new NPC(n.second["name"], n.second["desc"]);
    }
  }
  throw std::runtime_error("Invalid NPC with name: " + npcName
  + ". Check spelling and ensure this object is defined in npcs.json!");
}

Room* GenerateHelper::generateRoom(std::string roomName) {
  try {
    if (jsonRooms.size() < 1) { setup(); }
  // Not testable
  } catch (std::runtime_error& e) {
    throw(e);
  } catch (json::parse_error& e) {
    throw(e);
  }
  for (auto& r : jsonRooms) {
    if (TextHelper::keyify(roomName) == r.first
    || TextHelper::tolower(TextHelper::trimAll(r.second["name"]))
    == TextHelper::tolower(TextHelper::trimAll(roomName))) {
      Room* room = new Room(r.second["name"], r.second["desc"]);
      room->setRoomOxygen(r.second["oxygen"]);
      for (auto& roomObject : r.second["objects"]) {
        room->getRoomObjects()->addObject(
          generateObject(roomObject.get<std::string>()));
      }
      return room;
    }
  }
  throw std::runtime_error("Invalid Room with name: " + roomName
  + ". Check spelling and ensure this object is defined in rooms.json!");
}

Map* GenerateHelper::generateMap(std::string mapName) {
  try {
    if (jsonObjects.size() < 1 || jsonRooms.size() < 1) { setup(); }
  // Not testable
  } catch (std::runtime_error& e) {
    throw(e);
  } catch (json::parse_error& e) {
    throw(e);
  }
  std::ifstream file("text/json/" + mapName + ".json");
  if (!file.is_open()) {
    throw std::runtime_error(mapName + ".json not found!");
  }
  Map* map = new Map();
  json mapJSON = json::parse(file);
  for (auto it = mapJSON.begin(); it != mapJSON.end(); ++it) {
    for (auto& r : jsonRooms) {
      if (it.key() == r.first
      || TextHelper::tolower(TextHelper::trimAll(it.value()["name"]))
      == TextHelper::tolower(TextHelper::trimAll(r.second["name"]))) {
        Room* origin = map->getRoom(r.second["name"]);
        if (origin == nullptr) {
          origin = generateRoom(r.second["name"]);
          map->addRoom(origin);
        }
        if (it.value().contains("north")) {
          Room* dest = map->getRoom(it.value()["north"]["link"]);
          if (dest == nullptr) {
            dest = generateRoom(it.value()["north"]["link"]);
            map->addRoom(dest);
          }
          if (!map->doesDoorExistBetween(origin, dest)) {
            Door* link = new Door(origin, dest);
            if (it.value()["north"].contains("blocked")) {
              link->blockDoor(it.value()["north"]["blockedReason"]);
            }
            map->addDoor(link);
            origin->changeDoor(link, Globals::Direction::NORTH);
            dest->changeDoor(link, Globals::Direction::SOUTH);
          }
        }
        if (it.value().contains("east")) {
          Room* dest = map->getRoom(it.value()["east"]["link"]);
          if (dest == nullptr) {
            dest = generateRoom(it.value()["east"]["link"]);
            map->addRoom(dest);
          }
          if (!map->doesDoorExistBetween(origin, dest)) {
            Door* link = new Door(origin, dest);
            if (it.value()["east"].contains("blocked")) {
              link->blockDoor(it.value()["east"]["blockedReason"]);
            }
            map->addDoor(link);
            origin->changeDoor(link, Globals::Direction::EAST);
            dest->changeDoor(link, Globals::Direction::WEST);
          }
        }
        if (it.value().contains("south")) {
          Room* dest = map->getRoom(it.value()["south"]["link"]);
          if (dest == nullptr) {
            dest = generateRoom(it.value()["south"]["link"]);
            map->addRoom(dest);
          }
          if (!map->doesDoorExistBetween(origin, dest)) {
            Door* link = new Door(origin, dest);
            if (it.value()["south"].contains("blocked")) {
              link->blockDoor(it.value()["south"]["blockedReason"]);
            }
            map->addDoor(link);
            origin->changeDoor(link, Globals::Direction::SOUTH);
            dest->changeDoor(link, Globals::Direction::NORTH);
          }
        }
        if (it.value().contains("west")) {
          Room* dest = map->getRoom(it.value()["west"]["link"]);
          if (dest == nullptr) {
            dest = generateRoom(it.value()["west"]["link"]);
            map->addRoom(dest);
          }
          if (!map->doesDoorExistBetween(origin, dest)) {
            Door* link = new Door(origin, dest);
            if (it.value()["west"].contains("blocked")) {
              link->blockDoor(it.value()["west"]["blockedReason"]);
            }
            map->addDoor(link);
            origin->changeDoor(link, Globals::Direction::WEST);
            dest->changeDoor(link, Globals::Direction::EAST);
          }
        }
      }
    }
  }
  return map;
}
