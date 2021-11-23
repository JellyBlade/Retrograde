/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include "NPC.h"

NPC::NPC() : alive{true} {}

void NPC::talk() {
  if (alive) {
    // implement later
  }
}

void NPC::ask() {
  if (alive) {
    // implement later
  }
}

void NPC::stab() {
  alive = false;
}

bool NPC::isAlive() {
  return alive;
}

Room* NPC::getCurrentRoom() {
  return currentRoom;
}

void NPC::moveNPC(Room* room) {
  currentRoom = room;
}

void NPC::useOxygen() {
  if (currentRoom->getRoomOxygen() < 500) {
    alive = false;
    currentRoom->setRoomOxygen(0);
  }
  if (alive) {
    currentRoom->setRoomOxygen(currentRoom->getRoomOxygen() - 500);
  }
}
