/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <vector>
#include <string>

#include "InteractHelper.h"
#include "Game.h"
#include "Map.h"
#include "NPC.h"
#include "PlayerHandler.h"
#include "Inventory.h"

// Value is declared in main.cpp
Game* InteractHelper::game;
int InteractHelper::chapter = 0;

Map* InteractHelper::getMap() {
  return game->getMap();
}

PlayerHandler* InteractHelper::getPlayerHandler() {
  return game->getPlayerHandler();
}

Inventory* InteractHelper::getPlayerInventory() {
  return getPlayerHandler()->getPlayer()->getInventory();
}

NPC* InteractHelper::getNPC(std::string name) {
  for (NPC* n : getNPCs()) {
    if (TextHelper::tolower(TextHelper::trimAll(n->getName()))
    == TextHelper::tolower(TextHelper::trimAll(name))) {
      return n;
    }
  }
  return nullptr;
}

bool InteractHelper::npcInRoom(NPC* npc, Room* room) {
  return (npc->getCurrentRoom() == room);
}

bool InteractHelper::npcInRoom(std::string npcName, Room* room) {
  NPC* npc = getNPC(npcName);
  if (npc != nullptr) {
    return npcInRoom(npc, room);
  }
  return false;
}

std::vector<NPC*> InteractHelper::getNPCs() {
  return game->getNPCs();
}
