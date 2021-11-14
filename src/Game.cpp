/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include "Game.h"
#include "Room.h"
#include "Door.h"
#include "Globals.h"

Game::Game() {
  player = new PlayerHandler();
  map = new Map();
}

Game::~Game() {
  delete player;
  delete map;
}

std::vector<NPC*> Game::getNPCs() {
  // TODO(hipt2720): implement
}

void Game::playerTurn() {
  // awful win condition, check to see if gray orb/activated gray orbofdark
  // is still in the Steam Room.
  while (map->getRooms()[2]->getRoomObjects()->isObjectInContainer("grayorb")
  || map->getRooms()[2]->getRoomObjects()
  ->isObjectInContainer("activatedgrayorb")) {
    // Do player actions
    player->input();
    // Check to see if gray orb can be activated
    if (map->getRooms()[0]->getRoomObjects()->isObjectInContainer("orbofdark")
    && map->getRooms()[1]->getRoomObjects()
    ->isObjectInContainer("orboflight")
    && !map->getRooms()[2]->getRoomObjects()
    ->isObjectInContainer("activatedgrayorb")
    && !player->getPlayer()->getInventory()
    ->isObjectInContainer("activatedgrayorb")) {
      // Activate gray orb
      map->getRooms()[2]->getRoomObjects()->getObject("grayorb")
      ->setDescription("The once-lifeless orb is now shimmering with a "
      "pulsating mixture of lights and darks.");
      map->getRooms()[2]->getRoomObjects()->getObject("grayorb")
      ->setHoldable(true);
      map->getRooms()[2]->getRoomObjects()->getObject("grayorb")
      ->setName("Activated Gray Orb");
    }
  }
  playerWin();
}

void Game::playerWin() {
  std::cout << "Congratulations, you win!" << std::endl;
}

void Game::playerLose() {
  std::cout << "Congratulations, you lose! :)" << std::endl;
}

void Game::generateMap() {
  Room* r1 = new Room("Pure White Room", "Everything is white. It's blinding.");
  Room* r2 = new Room("Pure Black Room", "All is dark. It's terrifying.");
  Room* r3 = new Room("Steam Room",
  "Full of gadgets, doodads, gizmos, and whirligigs."
  " These must be how the other two rooms exist.");
  Door* d1 = new Door(r1, r2);
  Door* d2 = new Door(r2, r3);
  Object* o1 = new Object("Orb of Light",
  "It's radiance is blinding.", true);
  Object* o2 = new Object("Orb of Dark",
  "It is seemingly devouring all nearby light.", true);
  Object* o3 = new Object("Statue of Light",
  "A statue of some hero carved into marble sits in the center of the room."
  " A plaque on its dais reads: 'Beware the creatures who dwell within.'");
  Object* o4 = new Object("Statue of Dark",
  "A statue of some demon hewn into obsidian sits in the center of the room."
  " A plaque on its dais reads: 'Dwell within, and find inner peace.'");
  Object* o5 = new Object("Gray Orb", "It's dull and lifeless."
  " It is impossible to carry in it's current state.");
  Object* o6 = new Object("Brass Tubing",
  "I don't think this is supposed to be extra.");
  Object* o7 = new Object("Whirligig #482701",
  "It has the logo of some company, but the name is in a language that is "
  "undecipherable.", true);
  Object* o8 = new Object("Apple", "It has a bite taken out of it. Eww!", true);
  Object* o9 = new Object("'Master Gear'", "This is clearly a cog.", true);
  Object* o10 = new Object("'Apprentice Cog'", "This is clearly a flywheel.",
   true);
  Object* o11 = new Object("'Journeyman Flywheel'", "This is clearly a gear.",
   true);
  Object* o12 = new Object("'Architects' Illustrated' Issue #218",
  "There is a bipedal creature on the front, although it looks nothing like a"
  " human.", true);
  Object* o13 = new Object("Suspicious Box", "It is highly suspect.");
  player->getPlayer()->setCurrentRoom(r1);
  r1->changeDoor(d1, Globals::Direction::NORTH);
  r2->changeDoor(d1, Globals::Direction::SOUTH);
  r2->changeDoor(d2, Globals::Direction::NORTH);
  r3->changeDoor(d2, Globals::Direction::SOUTH);
  r1->getRoomObjects()->addObject(o1);
  r1->getRoomObjects()->addObject(o3);
  r2->getRoomObjects()->addObject(o2);
  r2->getRoomObjects()->addObject(o4);
  r3->getRoomObjects()->addObject(o5);
  r3->getRoomObjects()->addObject(o6);
  r3->getRoomObjects()->addObject(o7);
  r3->getRoomObjects()->addObject(o8);
  r3->getRoomObjects()->addObject(o9);
  r3->getRoomObjects()->addObject(o10);
  r3->getRoomObjects()->addObject(o11);
  r3->getRoomObjects()->addObject(o12);
  r3->getRoomObjects()->addObject(o13);

  map->addDoor(d1);
  map->addDoor(d2);
  map->addRoom(r1);
  map->addRoom(r2);
  map->addRoom(r3);
}

void Game::generateNPCs() {
  std::cout << "Generating NPCs..." << std::endl;
  std::cout << "Alright they're totally there ;)" << std::endl;
}
