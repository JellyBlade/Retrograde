/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <vector>

#include "InteractHelper.h"
#include "Game.h"
#include "Map.h"
#include "NPC.h"
#include "PlayerHandler.h"
#include "Inventory.h"

// Value is declared in main.cpp
Game* InteractHelper::game;

Map* InteractHelper::getMap() {
  return game->getMap();
}

PlayerHandler* InteractHelper::getPlayerHandler() {
  return game->getPlayerHandler();
}

Inventory* InteractHelper::getPlayerInventory() {
  return getPlayerHandler()->getPlayer()->getInventory();
}

std::vector<NPC*> InteractHelper::getNPCs() {
  return game->getNPCs();
}
