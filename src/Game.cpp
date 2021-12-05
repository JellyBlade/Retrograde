/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <string>
#include <vector>
#include <algorithm>

#include "Game.h"
#include "Room.h"
#include "Door.h"
#include "Globals.h"
#include "TextHelper.h"
#include "GenerateHelper.h"
#include "InteractHelper.h"

Game::Game() {
  player = new PlayerHandler();
  map = new Map();
}

Game::~Game() {
  delete player;
  delete map;
  for (int i = 0; i < npcs.size(); i++) {
    delete npcs[i];
  }
  npcs.clear();
}

std::vector<NPC*> Game::getNPCs() {
  return npcs;
}

void Game::play() {
  while (TextHelper::rgScriptGlobalFlags.count("win") != 1
  && TextHelper::rgScriptGlobalFlags.count("lose") != 1) {
    if (player->input(std::cin)) {
      map->calculateMapOxygen();
      if (map->getMapOxygen() <= 600) {
        TextHelper::rgScriptGlobalFlags["lose"] = true;
        playerLose();
        return;
      }
    }
  }
  if (TextHelper::rgScriptGlobalFlags.count("win") == 1) {
    playerWin();
    return;
  } else if (TextHelper::rgScriptGlobalFlags.count("lose") == 1) {
    playerLose();
    return;
  }
}

void Game::playerWin() {
  std::cout << "Congratulations, you win!" << std::endl;
}

void Game::playerLose() {
  std::cout << "You lose." << std::endl;
  if (TextHelper::rgScriptGlobalFlags.count("asphyxiated") == 1) {
    std::cout << "The room you were in was devoid of oxygen." << std::endl;
  }
  if (TextHelper::rgScriptGlobalFlags.count("sucked into space") == 1) {
    std::cout << "You were pulled into the void of space." << std::endl;
  }
}

void Game::generateMap() {
  map = GenerateHelper::generateMap("sirona");
  player->getPlayer()->setCurrentRoom(map->getRoom("recreation center"));
}

void Game::generateNPCs() {
  npcs.push_back(GenerateHelper::generateNPC("joe"));
}

void Game::addNPC(NPC* npc) {
  // Check if NPC has already been added.
  if (std::find(npcs.begin(), npcs.end(), npc) != npcs.end()) { return; }
  npcs.push_back(npc);
}

Map* Game::getMap() {
  return map;
}

PlayerHandler* Game::getPlayerHandler() {
  return player;
}
