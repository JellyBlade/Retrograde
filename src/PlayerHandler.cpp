/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>
#include <string>
#include <vector>

#include "PlayerHandler.h"
#include "InteractHelper.h"
#include "TextHelper.h"
#include "Room.h"
#include "Door.h"
#include "NPC.h"

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

bool PlayerHandler::input(std::istream& input) {
  std::string action, param;
  cout << "> ";
  input >> action;
  std::getline(input, param);

  action = TextHelper::tolower(TextHelper::trimAll(action));
  param = TextHelper::tolower(TextHelper::trimAll(param));

  // TODO(hipt2720): Replace these string comps with a cast to an enum of
  // options in the future.
  if (action == "pickup") {
    return pickUp(param);
  } else if (action == "move") {
    try {
      return movePlayer(Globals::stringToDirection(param));
    } catch ( ... ) {
      cout << "You cannot move that way." << endl;
      return false;
    }
  } else if (action == "status") {
    status();
    return false;
  } else if (action == "talk") {
    if (InteractHelper::npcInRoom(param, player->getCurrentRoom())) {
      InteractHelper::getNPC(param)->talk(input);
      return false;
    }
    cout << "That person is not here right now." << endl;
    return false;
  } else if (action == "ask") {
    if (InteractHelper::npcInRoom(param, player->getCurrentRoom())) {
      InteractHelper::getNPC(param)->ask(input);
      return false;
    }
    cout << "That person is not here right now." << endl;
    return false;
  } else if (action == "stab") {
    if (InteractHelper::npcInRoom(param, player->getCurrentRoom())) {
      InteractHelper::getNPC(param)->stab(input);
      return false;
    }
    cout << "That person is not here right now." << endl;
    return false;
  } else if (action == "look") {
    look();
    return false;
  } else if (action == "examine") {
    try {
      examine(Globals::stringToDirection(param));
      return false;
    } catch ( ... ) {
      NPC* npc = InteractHelper::getNPC(param);
      if (npc != nullptr) {
        examine(npc);
      }
      examine(param);
      return false;
    }
  } else if (action == "bag") {
    showInventory();
    return false;
  } else if (action == "help") {
    TextHelper::readFile("text/help.txt");
    return false;
  } else if (action == "drop") {
    return drop(param);
  } else {
    cout << "You cannot do that here." << endl;
    return false;
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
  for (NPC* n : InteractHelper::getNPCs()) {
    if (InteractHelper::npcInRoom(n, currentRoom)) {
      // TODO(hipt2720): Make a TextHelper function like listObjects for NPC
      // names.
      cout << n->getName() << " is here." << endl;
    }
  }
}

void PlayerHandler::status() {
  Room* currentRoom = player->getCurrentRoom();
  cout << "Spacesuit: " << (player->hasSpaceSuit() ? "ONLINE" : "NOT FOUND");
  cout << endl;
  cout << "Spacesuit Oxygen: ";
  cout << TextHelper::makePercent(player->getInventory()->getOxygen());
  cout << endl;
  cout << currentRoom->getName() << " Oxygen: ";
  cout << TextHelper::makePercent(currentRoom->getRoomOxygen()) << endl;
}

void PlayerHandler::showInventory() {
  std::vector<Object*> objects = player->getInventory()->getObjects();
  cout << "You look into your bag and find";
  if (objects.size() == 0) {
    cout << " nothing." << endl;
    return;
  }
  cout << ":" << endl;
  for (Object* o : objects) {
    cout << " - " << o->getName() << endl;
  }
}

bool PlayerHandler::examine(std::string examine) {
  Room* currentRoom = player->getCurrentRoom();
  Object* object;
  if (!currentRoom->getRoomObjects()->isObjectInContainer(examine)
      && !player->getInventory()->isObjectInContainer(examine)) {
    cout << "You cannot find that here." << endl;
    return false;
  }

  if (currentRoom->getRoomObjects()->isObjectInContainer(examine)) {
    object = currentRoom->getRoomObjects()->getObject(examine);
  } else {
    object = player->getInventory()->getObject(examine);
  }
  cout << object->getDescription() << endl;
  return true;
}

bool PlayerHandler::examine(Globals::Direction direction) {
  Room* currentRoom = player->getCurrentRoom();
  Door* exDoor = currentRoom->getDoor(direction);
  if (exDoor != nullptr) {
    cout << "Looking " << Globals::directionToString(direction);
    cout << ", you see a door that leads to the ";
    cout << exDoor->getOtherRoom(currentRoom)->getName() << endl;
    if (exDoor->isDoorBlocked()) {
      cout << "It is currently blocked: " << exDoor->getBlockedReason();
      cout << endl;
    }
    return true;
  }
  cout << "Looking " << Globals::directionToString(direction);
  cout << ", you see a wall, with no way through." << endl;;
  return false;
}

bool PlayerHandler::examine(NPC* npc) {
  Room* room = player->getCurrentRoom();
  if (InteractHelper::npcInRoom(npc, room)) {
    cout << npc->getDescription() << endl;
    return true;
  } else {
    cout << npc->getName() << " is not in this room." << endl;
    return false;
  }
}

bool PlayerHandler::pickUp(std::string pickUp) {
  Room* room = player->getCurrentRoom();
  if (!room->getRoomObjects()->isObjectInContainer(pickUp)) {
    cout << "You cannot find that here." << endl;
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
