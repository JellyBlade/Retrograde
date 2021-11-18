/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

#include "TextHelper.h"
#include "InteractHelper.h"
#include "Globals.h"
#include "Room.h"
#include "Door.h"
#include "Player.h"

std::map<std::string, bool> TextHelper::rgScriptFlags;

void TextHelper::readFile(std::string textPath, std::istream& input) {
  std::string s;
  std::ifstream file(textPath);
  while (std::getline(file, s)) {
    if (!s.empty() && trim(s)[0] == '/') { continue; }
    if (!s.empty() && trim(s)[0] == ':') {
      try {
        if (commandProcessor(tolower(trim(s)), file)) {
          TextHelper::rgScriptFlags.clear();
          file.close();
          return;
        }
        continue;
      } catch (...) {
        throw;
      }
    }
    std::cout << s << std::endl;
  }
  TextHelper::rgScriptFlags.clear();
  file.close();
}

bool TextHelper::commandProcessor(std::string command, std::istream& file,
    std::istream& input) {
  std::string cmd, param;
  std::vector<std::string> params;
  std::stringstream ss;
  ss.str(command.substr(1));
  ss >> cmd;
  while (ss >> param) {
    params.push_back(param);
  }

  if (cmd == "if") {
    if (params.size() == 0) {
      std::cout << "Not enough parameters for RGScript if";
      // Not enough parameters for RGScript if
      throw std::exception{};
    }
    std::string dialog;
    bool readIf = false;
    bool skip = false;
    Player* player = InteractHelper::getPlayerHandler()->getPlayer();
    if (params.size() == 1 && params[0] == "spacesuit") {
      readIf = player->hasSpaceSuit();
    } else {
      std::string criterion;
      std::string criterionType = params.front();
      params.erase(params.begin());
      for (std::string s : params) {
        criterion += s;
      }
      if (criterionType == "holding") {
        readIf = player->getInventory()->isObjectInContainer(criterion);
      } else if (criterionType == "inroom") {
        readIf = player->getCurrentRoom()->getRoomObjects()
        ->isObjectInContainer(criterion);
      } else if (criterionType == "flag" || criterionType == "flagtrue") {
        if (TextHelper::rgScriptFlags.count(criterion) == 1) {
          if (TextHelper::rgScriptFlags[criterion]) {
            readIf = true;
          }
        }
      } else if (criterionType == "flagfalse") {
        if (TextHelper::rgScriptFlags.count(criterion) == 1) {
          if (!TextHelper::rgScriptFlags[criterion]) {
            readIf = true;
          }
        }
      } else {
        std::cout << "Unknown RGScript if criterion.";
        // Unknown RGScript if criterion.
        throw std::exception{};
      }
    }
    skip = !readIf;
    while (std::getline(file, dialog)) {
      dialog = trim(dialog);
      if (!dialog.empty() && dialog[0] == '/') { continue; }
      if (dialog == ":endif") {
        return false;
      }
      if (dialog == ":else" && readIf) {
        skip = true;
      } else if (!readIf) {
        skip = false;
      }
      if (!dialog.empty() && dialog[0] == ':') {
         commandProcessor(dialog, file, input);
      }
      std::cout << (skip ? "" : dialog) << (skip ? "" : "\n");
    }
  } else if (cmd == "mc") {
    std::string dialog;
    std::string choice = "";
    bool skip = false;
    std::streampos topOfMC = file.tellg();

    while (std::getline(file, dialog)) {
      dialog = trim(dialog);
      if (!dialog.empty() && dialog[0] == '/') { continue; }
      if (dialog == ":endmc") {
        return false;
      } else if (dialog == ":back" && !skip) {
        file.seekg(topOfMC);
      } else if (dialog == ":continue" && !skip) {
        skip = true;
        choice == ":skip";
      } else if (dialog == ":endmcdef") {
        std::cout << "Select an option." << std::endl << "> ";
        input >> choice;
        choice = ":" + choice;
        continue;
      } else if (dialog == choice) {
        skip = false;
      } else if (dialog[0] == ':' && ::isdigit(dialog[1]) && dialog != choice) {
        skip = true;
      } else if (dialog[0] == ':' && !skip && !::isdigit(dialog[1])) {
        commandProcessor(dialog, file, input);
      }
      std::cout << (skip ? "" : dialog) << (skip ? "" : "\n");
    }
  } else if (cmd == "give") {
    // TODO(hipt2720): This requires a list of all possible objects.
    return false;
  } else if (cmd == "setflag") {
    if (params.size() <= 1) {
      std::cout << "Not enough parameters for RGScript setflag";
      // Not enough parameters for RGScript setflag
      throw std::exception{};
    }
    std::string flagName;
    bool flagValue = (params.back() == "true" || params.back() == "1");
    params.pop_back();
    for (std::string s : params) {
      flagName += s;
    }
    flagName = tolower(trimAll(flagName));
    TextHelper::rgScriptFlags[flagName] = flagValue;
    return false;
  } else if (cmd == "move") {
    std::string roomName;
    for (std::string s : params) {
      roomName += s;
    }
    for (Room* room : InteractHelper::getMap()->getRooms()) {
      if (tolower(trimAll(room->getName())) == trimAll(roomName)) {
        InteractHelper::getPlayerHandler()->getPlayer()->setCurrentRoom(room);
        return false;
      }
    }
    // Room not found for RGScript move
    throw std::exception{};
  } else if (cmd == "movenpc") {
    std::string roomName;
    std::string npcName = params.front();
    params.erase(params.begin());
    for (std::string s : params) {
      roomName += s;
    }
    for (Room* room : InteractHelper::getMap()->getRooms()) {
      if (tolower(trimAll(room->getName())) == trimAll(roomName)) {
        for (NPC* npc : InteractHelper::getNPCs()) {
          if (tolower(trimAll(npc->getName())) == trimAll(npcName)) {
            // TODO(hipt2720): Uncomment this when NPC is implemented.
            // npc->moveNPC(room);
            return false;
          }
        }
        // NPC not found for RGScript movenpc
        throw std::exception{};
      }
    }
    // Room not found for RGScript movenpc
    throw std::exception{};
  } else if (cmd == "quit") {
    return true;
  } else if (cmd == "askquit") {
    std::string response;
    std::cout << "Would you like to continue?" << std::endl << "> ";
    input >> response;
    std::cout << response;
    response = trim(tolower(response));
    std::cout << response;
    std::cout << response[0];
    return response[0] == 'y' ? false : true;
  } else if (cmd == "pause") {
    std::cout << "Press enter to continue...";
    std::cin.ignore();
    return false;
  } else {
    // RGScript command not recognized.
    throw std::exception{};
  }
}

std::string TextHelper::makePercent(int i) {
  std::string s = std::to_string(i);
  if (i < 100) {
    s.insert(s.begin(), '0');
  }
  if (i < 10) {
    s.insert(s.begin(), '0');
  }
  s.insert(s.end() - 2, '.');
  return s + "%";
}

std::string TextHelper::listObjects(std::vector<Object*> objects) {
  std::string s = "";
  switch (objects.size()) {
    case 0:
      s = " it is empty.";
      return s;
    case 1:
      s = startsWithVowel(objects[0]->getName()) ? " an " : " a ";
      s += objects[0]->getName() + ".";
      return s;
    default:
      for (Object* o : objects) {
        if (o == objects.back()) {
          s += startsWithVowel(o->getName()) ? " and an " : " and a ";
          s += o->getName() + ".";
          continue;
        }
        s += startsWithVowel(o->getName()) ? " an " : " a ";
        s += o->getName() + ",";
      }
      return s;
  }
}

std::string TextHelper::listDoors(Room* room) {
  std::string s = "";
  std::map<Globals::Direction, Door*> doors = room->getDoors();
  int size = doors.size();
  if (size == 0) {
    s = "There are no doors.";
    return s;
  } else if (size == 1) {
    s = "There is a door to the ";
    if (doors.count(Globals::Direction::NORTH) == 1) {
      s += "north.";
    } else if (doors.count(Globals::Direction::EAST) == 1) {
      s += "east.";
    } else if (doors.count(Globals::Direction::SOUTH) == 1) {
      s += "south.";
    } else if (doors.count(Globals::Direction::WEST) == 1) {
      s += "west.";
    }
    return s;
  } else {
    s = "There are doors to the ";
    if (doors.count(Globals::Direction::NORTH) == 1) {
      s += "north, ";
      size--;
    }
    if (doors.count(Globals::Direction::EAST) == 1) {
      if (--size == 0) {
        s += "and east.";
      } else {
        s += "east, ";
      }
    }
    if (doors.count(Globals::Direction::SOUTH) == 1) {
      if (--size == 0) {
        s += "and south.";
      } else {
        s += "south, ";
      }
    }
    if (doors.count(Globals::Direction::WEST) == 1) {
      if (--size == 0) {
        s += "and west.";
      } else {
        s += "west, ";
      }
    }
    return s;
  }
}

bool TextHelper::startsWithVowel(std::string s) {
  char c = tolower(trim(s))[0];
  if (!isalpha(c)) { c = tolower(trim(s))[1]; }
  return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

std::string TextHelper::tolower(std::string s) {
  if (s.size() <= 0 ) { return ""; }
  for (auto& c : s) {
    c = std::tolower(c);
  }
  return s;
}

std::string TextHelper::toupper(std::string s) {
  if (s.size() <= 0 ) { return ""; }
  for (auto& c : s) {
    c = std::toupper(c);
  }
  return s;
}

std::string TextHelper::trim(std::string s) {
  if (s.size() <= 0 ) { return ""; }
  s.erase(0, s.find_first_not_of(" \t\r\n"));
  s.erase(s.find_last_not_of(" \t\r\n") + 1, s.size() - 1);
  return s;
}

std::string TextHelper::trimAll(std::string s) {
  if (s.size() <= 0 ) { return ""; }
  s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
  return s;
}
