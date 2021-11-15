/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>
#include <string>
#include <vector>

#include "PlayerHandler.h"
#include "TextHelper.h"
#include "Room.h"

using std::cout;
using std::cin;
using std::endl;

PlayerHandler::PlayerHandler() {
  player = new Player();
}

PlayerHandler::~PlayerHandler() {
  delete player;
}

Player* PlayerHandler::getPlayer() {
  return player;
}

void PlayerHandler::input() {
  std::string action, param;
  bool turnEnded = false;
  while (!turnEnded) {
    cout << "> ";
    cin >> action;
    std::getline(std::cin, param);

    action = TextHelper::tolower(TextHelper::trimAll(action));
    param = TextHelper::tolower(TextHelper::trimAll(param));

    // TODO(hipt2720): Replace these string comps with a cast to an enum of
    // options in the future.
    if (action == "pickup") {
      if (pickUp(param)) {
        turnEnded = true;
      }
    } else if (action == "move") {
      try {
        if (movePlayer(Globals::stringToDirection(param))) {
          turnEnded = true;
        }
      } catch (std::exception e) {
        cout << "You cannot move that way." << endl;
      }
    } else if (action == "look") {
      look();
    } else if (action == "examine") {
      examine(param);
    } else if (action == "bag") {
      showInventory();
    } else if (action == "help") {
      cout << "No help for you!" << endl;
    } else if (action == "drop") {
      if (drop(param)) {
        turnEnded = true;
      }
    } else {
      cout << "You can't do that here." << endl;
    }
  }
}

bool PlayerHandler::movePlayer(Globals::Direction direction) {
  // TODO(hipt2720): Handle if the player's currentRoom doesn't exist.
  // No door, just a wall.
  Room* currentRoom = player->getCurrentRoom();
  if (currentRoom->getDoor(direction) == nullptr) {
    cout << "You cannot go that way." << endl;
    return false;
  }

  // Door is blocked.
  if (currentRoom->getDoor(direction)->isDoorBlocked()) {
    cout << "You cannot go that way: ";
    cout << currentRoom->getDoor(direction)->getBlockedReason() << endl;
    return false;
  }

  Room* newRoom = currentRoom->getDoor(direction)->getOtherRoom(currentRoom);
  player->setCurrentRoom(newRoom);
  cout << "You move " << Globals::directionToString(direction) << ", entering ";
  cout << "into the " << newRoom->getName() << "." << endl;
  return true;
}

void PlayerHandler::look() {
  Room* currentRoom = player->getCurrentRoom();
  cout << "You are in the " << currentRoom->getName() << "." << endl;
  cout << currentRoom->getDescription() << endl;

  cout << "Looking around the room, you see";
  cout << TextHelper::listObjects(currentRoom->getRoomObjects()->getObjects());
  cout << endl;
  cout << TextHelper::listDoors(currentRoom) << endl;
  // List NPCs here
}

void PlayerHandler::showInventory() {
  cout << "You look into your bag and find:" << endl;
  for (Object* o : player->getInventory()->getObjects()) {
    cout << " - " << o->getName() << endl;
  }
}

bool PlayerHandler::examine(std::string examine) {
  Room* currentRoom = player->getCurrentRoom();
  if (!currentRoom->getRoomObjects()->isObjectInContainer(examine)) {
    cout << "You can't find that here." << endl;
    return false;
  }
  Object* object = currentRoom->getRoomObjects()->getObject(examine);
  if (object->getDescription().back() == '.') {
    cout << object->getDescription() << endl;
    return true;
  }
  cout << object->getDescription() << "." << endl;
  return true;
}

bool PlayerHandler::pickUp(std::string pickUp) {
  Room* room = player->getCurrentRoom();
  if (!room->getRoomObjects()->isObjectInContainer(pickUp)) {
    cout << "You can't find that here." << endl;
    return false;
  }
  // TODO(hipt2720): Refactor Inventory::addObject(), move the isHoldable check
  // here so that we don't need to do this inventory size hack.
  Object* object = room->getRoomObjects()->getObject(pickUp);
  int size = player->getInventory()->size();
  player->getInventory()->addObject(object);
  if (player->getInventory()->size() > size) {
      room->getRoomObjects()->removeObject(object);
      return true;
  }
  return false;
}

bool PlayerHandler::drop(std::string drop) {
  // TODO(hipt2720): Check for the player's room existing
  if (!player->getInventory()->isObjectInContainer(drop)) {
    cout << "You are not carrying that item." << endl;
    return false;
  }
  Object* obj = player->getInventory()->getObject(drop);
  player->getInventory()->removeObject(obj);
  player->getCurrentRoom()->getRoomObjects()->addObject(obj);
  cout << "You dropped " << obj->getName() << " into the room." << endl;
  return true;
}

std::vector<NPC*> getNPCsInCurrentRoom() {
  // TODO(hipt2720): This requires NPCs and Game to be implemented first.
}
