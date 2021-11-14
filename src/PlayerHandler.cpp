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
    cout << "What would you like to do?" << endl;
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
    } else if (action == "examine") {
      examine();
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
  return true;
}

void PlayerHandler::examine() {
  Room* currentRoom = player->getCurrentRoom();
  cout << "You are in the " << currentRoom->getName() << "." << endl;
  cout << currentRoom->getDescription() << endl;

  cout << "Looking around the room, you see";
  cout << TextHelper::listObjects(currentRoom->getRoomObjects()->getObjects());
  cout << endl;
  // List NPCs here
}

bool PlayerHandler::pickUp(std::string pickUp) {
  Room* room = player->getCurrentRoom();
  if (!room->getRoomObjects()->isObjectInContainer(pickUp)) {
    cout << "You can't find that here." << endl;
    return false;
  }
  // TODO(hipt2720): Refactor Inventory::addObject(), move the isHoldable check
  // here so that we don't need to do this inventory size hack.
  int size = player->getInventory()->size();
  player->getInventory()->addObject(room->getRoomObjects()->getObject(pickUp));
  return player->getInventory()->size() > size ? true : false;
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
