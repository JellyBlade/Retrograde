/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include "NPC.h"

NPC::NPC() : alive{true} {}

void NPC::talk() {
  // implement later
}

void NPC::ask() {
  // implement later
}

void NPC::stab() {
  // implement later
  alive = false;
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
  } else {
    currentRoom->setRoomOxygen(currentRoom->getRoomOxygen() - 500);
  }
}
