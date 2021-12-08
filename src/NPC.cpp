/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <string>
#include <iostream>

#include "NPC.h"
#include "TextHelper.h"
#include "InteractHelper.h"

NPC::NPC(std::string n, std::string d) : alive{true} {
  setName(n);
  setDescription(d);
}

void NPC::talk(std::istream& input) {
  if (alive) {
    std::string filePath = "text/dialog/"
    + TextHelper::tolower(TextHelper::trimAll(getName())) + "/"
    + std::to_string(InteractHelper::chapter) + ".txt";
    if (TextHelper::fileExists(filePath)) {
      TextHelper::readFile(filePath, input);
    } else {
      for (int i = InteractHelper::chapter; i >= 0; i--) {
        filePath = "text/dialog/"
        + TextHelper::tolower(TextHelper::trimAll(getName())) + "/"
        + std::to_string(i) + ".txt";
        if (TextHelper::fileExists(filePath)) {
          TextHelper::readFile(filePath, input);
          return;
        }
      }
      TextHelper::readFile("text/dialog/"
      + TextHelper::tolower(TextHelper::trimAll(getName()))
      + "/default.txt", input);
    }
  } else {
    std::cout << "You cannot talk to " << getName() << ", as they are dead.";
    std::cout << std::endl;
  }
}

void NPC::ask(std::istream& input) {
  if (alive) {
    std::string filePath = "text/dialog/"
    + TextHelper::tolower(TextHelper::trimAll(getName())) + "/"
    + std::to_string(InteractHelper::chapter) + "_ask.txt";
    if (TextHelper::fileExists(filePath)) {
      TextHelper::readFile(filePath, input);
    } else {
      for (int i = InteractHelper::chapter; i >= 0; i--) {
        filePath = "text/dialog/"
        + TextHelper::tolower(TextHelper::trimAll(getName())) + "/"
        + std::to_string(i) + "_ask.txt";
        if (TextHelper::fileExists(filePath)) {
          TextHelper::readFile(filePath, input);
          return;
        }
      }
      TextHelper::readFile("text/dialog/"
      + TextHelper::tolower(TextHelper::trimAll(getName()))
      + "/default_ask.txt", input);
    }
  } else {
    std::cout << "You cannot ask " << getName();
    std::cout << " anything, as they are dead." << std::endl;
  }
}

void NPC::stab(std::istream& input) {
  if (alive) {
    std::string stabFilePath = "text/dialog/"
    + TextHelper::tolower(TextHelper::trimAll(getName())) + "/stab.txt";
    if (TextHelper::fileExists(stabFilePath)) {
      TextHelper::readFile(stabFilePath, input);
    } else {
      std::cout << "You stab " << getName() << ", killing them." << std::endl;
    }
    alive = false;
  } else {
    std::cout << "You stab " << getName() << "'s corpse. Their body doesn't";
    std::cout << " need additional convincing of its demise, you monster.";
    std::cout << std::endl;
  }
}

bool NPC::isAlive() {
  return alive;
}

void NPC::setAlive(bool newVal) {
  alive = newVal;
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
