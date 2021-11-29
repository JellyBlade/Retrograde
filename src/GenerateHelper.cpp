/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

#include "GenerateHelper.h"
#include "TextHelper.h"
#include "Door.h"
#include "Object.h"
#include "Log.h"
#include "OxygenTank.h"
#include "ItemLock.h"
#include "PasswordLock.h"
#include "Box.h"
#include "AirLock.h"

using json = nlohmann::json;

void GenerateHelper::setup() {
  std::ifstream file("text/objects.json");
  if (!file.is_open()) {
    throw std::runtime_error("objects.json not found!");
  }
  json j = json::parse(file);
  for (auto it = j.begin(); it != j.end(); ++it) {
    jsonObjects.push_back(it.value());
  }
  file.open("text/rooms.json");
  if (!file.is_open()) {
    throw std::runtime_error("rooms.json not found!");
  }
  j = json::parse(file);
  for (auto it = j.begin(); it != j.end(); ++it) {
    jsonRooms.push_back(it.value());
  }
}

Object* GenerateHelper::generateObject(std::string objectName) {
  if (jsonObjects.size() < 1) { setup(); }
  objectName = TextHelper::tolower(TextHelper::trimAll(objectName));
  for (auto o : jsonObjects) {
    if (TextHelper::tolower(TextHelper::trimAll(o["name"])) == objectName) {
      if (o.contains("box")) {
        Box* box = new Box(o["name"], o["desc"], o["holdable"]);
        for (auto& boxObj : o["box"]) {
          box->addObject(generateObject(boxObj.get<std::string>()));
        }
        return box;
      } else if (o.contains("password")) {
        return new PasswordLock(o["name"], o["desc"], o["holdable"],
        o["password"]);
      } else if (o.contains("oxygenTankReuse")) {
        //return new OxygenTank(o["name"], o["desc"], o["holdable"],
        //o["oxygenTankReuse"]);
      } else if (o.contains("reqItem")) {
        return new ItemLock(o["name"], o["desc"], o["holdable"], o["reqItem"]);
      } else if (o.contains("reqOxygen")) {
        //return new AirLock(o["name"], o["desc"], o["holdable"], o["reqOxygen"]);
      } else if (o.contains("logFile")) {
        return new Log(o["name"], o["desc"], o["holdable"], o["logFile"]);
      } else {
        return new Object(o["name"], o["desc"], o["holdable"]);
      }
    }
  }
}

Room* GenerateHelper::generateRoom(std::string roomName) {
  if (jsonRooms.size() < 1) { setup(); }
  roomName = TextHelper::tolower(TextHelper::trimAll(roomName));
  for (auto r : jsonRooms) {
    if (TextHelper::tolower(TextHelper::trimAll(r["name"])) == roomName) {
      Room* room = new Room(r["name"], r["desc"]);
      room->setRoomOxygen(r["oxygen"]);
      for (auto& roomObject : r["objects"]) {
        room->getRoomObjects()->addObject(generateObject(roomObject.get<std::string>()));
      }
      return room;
    }
  }
}

Map* GenerateHelper::generateMap(std::string mapName) {
  if (jsonObjects.size() < 1 || jsonRooms.size() < 1) { setup(); }
  mapName = TextHelper::tolower(TextHelper::trimAll(mapName));
  std::ifstream file("text/" + mapName + ".json");
  if (!file.is_open()) {
    throw std::runtime_error(mapName + ".json not found!");
  }
  json mapJSON = json::parse(file);
}
