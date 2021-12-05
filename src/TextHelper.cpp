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
#include <stdexcept>

#include "TextHelper.h"
#include "InteractHelper.h"
#include "GenerateHelper.h"
#include "Globals.h"
#include "NPC.h"
#include "Room.h"
#include "Door.h"
#include "Player.h"

std::map<std::string, bool> TextHelper::rgScriptLocalFlags;
std::map<std::string, bool> TextHelper::rgScriptGlobalFlags;
int TextHelper::line = 0;

void TextHelper::readFile(std::string textPath, std::istream& input) {
  TextHelper::line = 0;
  std::string s;
  std::ifstream file(textPath);
  while (std::getline(file, s)) {
    TextHelper::line++;
    if (!s.empty() && trim(s)[0] == '/') { continue; }
    if (!s.empty() && trim(s)[0] == ':') {
      try {
        if (commandProcessor(tolower(trim(s)), file, input)) {
          TextHelper::rgScriptLocalFlags.clear();
          file.close();
          return;
        }
        continue;
      } catch (std::runtime_error& e) {
        std::cout << "Error while reading '" << textPath << "':" << std::endl;
        std::cout << e.what() << std::endl;
        throw(e);
      } catch (std::invalid_argument& e) {
        std::cout << "Error while reading '" << textPath << "':" << std::endl;
        std::cout << e.what() << std::endl;
        throw(e);
      }
    }
    std::cout << s << std::endl;
  }
  TextHelper::rgScriptLocalFlags.clear();
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
    return cpIf(params, file, input);
  } else if (cmd == "mc") {
    return cpMC(file, input);
  } else if (cmd == "chapter") {
    return cpChapter(params);
  } else if (cmd == "give") {
    return cpGive(params);
  } else if (cmd == "block") {
    return cpBlock(params);
  } else if (cmd == "unblock") {
    return cpUnblock(params);
  } else if (cmd == "setflag") {
    return cpSetFlag(params);
  } else if (cmd == "setgflag" || cmd == "setflagg") {
    return cpSetGlobalFlag(params);
  } else if (cmd == "move") {
    return cpMovePlayer(params);
  } else if (cmd == "movenpc") {
    return cpMoveNPC(params);
  } else if (cmd == "kill") {
    rgScriptGlobalFlags["lose"] = true;
    return true;
  } else if (cmd == "killnpc") {
    return cpKillNPC(params);
  } else if (cmd == "quit") {
    return true;
  } else if (cmd == "askquit") {
    std::string response;
    std::cout << "Would you like to continue? (y/n)" << std::endl << "> ";
    input >> response;
    response = trim(tolower(response));
    input.ignore(256, '\n');
    if (response[0] != 'y') {
      std::cout << "[Exited Dialog]" << std::endl;
      return true;
    }
    return false;
  } else if (cmd == "pause") {
    std::cout << "Press enter to continue...";
    input.ignore(256, '\n');
    return false;
  } else {
    if (cmd == "back" || cmd == "endmc" || cmd == "endmcdef"
    || cmd == "continue" || ::isdigit(cmd[0])) {
      throw std::invalid_argument(std::string("RGScript command: '")
      + cmd + "' encountered outside of MC block on line: "
      + std::to_string(TextHelper::line));
    } else if (cmd == "endif" || cmd == "else") {
      throw std::invalid_argument(std::string("RGScript command: '")
      + cmd + "' encountered outside of if statement on line: "
      + std::to_string(TextHelper::line));
    } else {
      throw std::invalid_argument(std::string("RGScript command: '")
      + cmd + "' not recognized on line: " + std::to_string(TextHelper::line));
    }
  }
}

bool TextHelper::cpIf(std::vector<std::string> params, std::istream& file,
std::istream& input) {
  if (params.size() == 0) {
    throw std::invalid_argument(std::string("Not enough parameters for")
    + " RGScript if on line: " + std::to_string(TextHelper::line));
  }
  std::string dialog;
  bool readIf = false;
  bool skip = false;
  int nestedCount = 0;
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
    } else if (criterionType == "chapter") {
      readIf = std::stoi(criterion) == InteractHelper::chapter;
    } else if (criterionType == "inroom") {
      readIf = player->getCurrentRoom()->getRoomObjects()
      ->isObjectInContainer(criterion);
    } else if (criterionType == "flag" || criterionType == "flagtrue") {
      if (TextHelper::rgScriptLocalFlags.count(criterion) == 1) {
        readIf = TextHelper::rgScriptLocalFlags[criterion];
      } else if (TextHelper::rgScriptGlobalFlags.count(criterion) == 1) {
        readIf = TextHelper::rgScriptGlobalFlags[criterion];
      }
    } else if (criterionType == "flagfalse") {
      if (TextHelper::rgScriptLocalFlags.count(criterion) == 1) {
        readIf = !TextHelper::rgScriptLocalFlags[criterion];
      } else if (TextHelper::rgScriptGlobalFlags.count(criterion) == 1) {
        readIf = !TextHelper::rgScriptGlobalFlags[criterion];
      }
    } else {
      throw std::invalid_argument(std::string("Unknown RGScript if criteria: ")
      + criterion + " on line: " + std::to_string(TextHelper::line));
    }
  }
  skip = !readIf;
  while (std::getline(file, dialog)) {
    TextHelper::line++;
    dialog = trim(dialog);
    if (!dialog.empty() && dialog[0] == '/') { continue; }
    if (dialog == ":endif") {
      if (nestedCount-- > 0) { continue; }
      return false;
    } else if (dialog == ":else") {
      if (nestedCount > 0) { continue; }
      skip = readIf;
      continue;
    } else if (!dialog.empty() && dialog[0] == ':') {
      if (skip && dialog.substr(0, dialog.find(' ')) == ":if") {
         nestedCount += 1;
      }
      if (!skip) {
        if (TextHelper::rgScriptGlobalFlags.count("debugmode") == 1) {
          std::cout << "[DEBUG_if]: L: " << TextHelper::line << "; Sending: "
          << dialog << std::endl;
        }
        if (commandProcessor(dialog, file, input)) { return true; }
        continue;
      }
    }
    std::cout << (skip ? "" : dialog) << (skip ? "" : "\n");
  }
  return false;
}

bool TextHelper::cpMC(std::istream& file, std::istream& input) {
  std::string dialog;
  std::string choice = "";
  int nestedCount = 0;
  int prevLine = TextHelper::line;
  bool skip = false;
  bool validChoice = false;
  std::streampos topOfMC = file.tellg();

  while (std::getline(file, dialog)) {
    TextHelper::line++;
    dialog = trim(dialog);
    if (!dialog.empty() && dialog[0] == '/') { continue; }
    if (dialog == ":mc" && skip) { nestedCount++; }
    if (dialog == ":endmc" && validChoice && nestedCount-- <= 0) {
      return false;
    } else if (dialog == ":endmc" && !validChoice && nestedCount-- <= 0) {
      std::cout << "Please enter a valid option." << std::endl;
      choice = "";
      skip = false;
      file.seekg(topOfMC);
      TextHelper::line = prevLine;
      continue;
    } else if (dialog == ":back" && !skip) {
      choice = "";
      validChoice = false;
      file.seekg(topOfMC);
      TextHelper::line = prevLine;
      continue;
    } else if (dialog == ":continue" && !skip) {
      skip = true;
      choice == ":skip";
      continue;
    } else if (dialog == ":endmcdef" && !skip) {
      std::cout << (skip ? "" : "Select an option.\n") << "> ";
      input >> choice;
      choice = ":" + trim(choice);
      input.ignore(256, '\n');
      continue;
    } else if (dialog == choice && nestedCount <= 0) {
      skip = false;
      validChoice = true;
      continue;
    } else if (dialog[0] == ':' && ::isdigit(dialog[1]) && dialog != choice
      && !skip) {
      skip = true;
      continue;
    } else if (dialog[0] == ':' && !::isdigit(dialog[1]) && !skip) {
      if (TextHelper::rgScriptGlobalFlags.count("debugmode") == 1) {
        std::cout << "[DEBUG_mc]: L: " << TextHelper::line << "; Sending: "
        << dialog << std::endl;
      }
      if (commandProcessor(dialog, file, input)) { return true; }
      continue;
    }
    std::cout << (skip ? "" : dialog) << (skip ? "" : "\n");
  }
}

bool TextHelper::cpChapter(std::vector<std::string> params) {
  if (params.size() == 0) {
    throw std::invalid_argument(std::string("Not enough parameters for")
    + " RGScript chapter on line: " + std::to_string(TextHelper::line));
  }
  if (params[0][0] == '+') {
    InteractHelper::chapter++;
  } else if (params[0][0] == '-') {
    InteractHelper::chapter--;
  } else if (std::all_of(params[0].begin(), params[0].end(), ::isdigit)) {
    InteractHelper::chapter = std::stoi(params[0]);
  } else {
    throw std::invalid_argument(std::string("RGScript chapter parameter is")
    + " not -+ or int. on line: " + std::to_string(TextHelper::line));
  }
  return false;
}

bool TextHelper::cpGive(std::vector<std::string> params) {
  if (params.size() == 0) {
    throw std::runtime_error(std::string("Not enough parameters for ")
    + " RGScript give on line: " + std::to_string(TextHelper::line));
  }
  std::string objectName;
  for (std::string s : params) {
    objectName += s;
  }
  objectName = tolower(trimAll(objectName));
  if (objectName == "spacesuit") {
    InteractHelper::getPlayerInventory()->giveSpaceSuit();
  } else {
    InteractHelper::getPlayerInventory()
    ->addObject(GenerateHelper::generateObject(objectName));
  }
  return false;
}

bool TextHelper::cpBlock(std::vector<std::string> params) {
  if (params.size() <= 1) {
    throw std::invalid_argument(std::string("Not enough parameters for")
    + " RGScript block on line: " + std::to_string(TextHelper::line));
  }
  std::string direction = params.front();
  params.erase(params.begin());
  std::string blockedReason;
  for (std::string s : params) {
    blockedReason += s;
  }
  Room* r = InteractHelper::getPlayerHandler()->getPlayer()->getCurrentRoom();
  Door* d = r->getDoor(Globals::stringToDirection(direction));
  if (d == nullptr) {
    throw std::runtime_error(std::string("RGScript: Attempt to block ")
    + direction + " door in " + r->getName()
    + " failed, as the door does not exist." + " on line: "
    + std::to_string(TextHelper::line));
  }
  d->blockDoor(blockedReason);
  return false;
}

bool TextHelper::cpUnblock(std::vector<std::string> params) {
  if (params.size() == 0) {
    throw std::invalid_argument(std::string("Not enough parameters for")
    + " RGScript block on line: " + std::to_string(TextHelper::line));
  }
  std::string direction = params.front();
  Room* r = InteractHelper::getPlayerHandler()->getPlayer()->getCurrentRoom();
  Door* d = r->getDoor(Globals::stringToDirection(direction));
  if (d == nullptr) {
    throw std::runtime_error(std::string("RGScript: Attempt to unblock ")
    + direction + " door in " + r->getName()
    + " failed, as the door does not exist." + " on line: "
    + std::to_string(TextHelper::line));
  }
  d->unblockDoor();
  return false;
}

bool TextHelper::cpSetFlag(std::vector<std::string> params) {
  if (params.size() <= 1) {
    throw std::invalid_argument(std::string("Not enough parameters for")
    + " RGScript setflag on line: " + std::to_string(TextHelper::line));
  }
  std::string flagName;
  bool flagValue = (params.back()[0] == 't' || params.back() == "1");
  params.pop_back();
  for (std::string s : params) {
    flagName += s;
  }
  flagName = tolower(trimAll(flagName));
  TextHelper::rgScriptLocalFlags[flagName] = flagValue;
  return false;
}

bool TextHelper::cpSetGlobalFlag(std::vector<std::string> params) {
  if (params.size() <= 1) {
    throw std::invalid_argument(std::string("Not enough parameters for")
    + " RGSCript setgflag on line: " + std::to_string(TextHelper::line));
  }
  std::string flagName;
  bool flagValue = (params.back()[0] == 't' || params.back() == "1");
  params.pop_back();
  for (std::string s : params) {
    flagName += s;
  }
  flagName = tolower(trimAll(flagName));
  TextHelper::rgScriptGlobalFlags[flagName] = flagValue;
  return false;
}

bool TextHelper::cpMovePlayer(std::vector<std::string> params) {
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
  throw std::runtime_error(std::string("Room with name: '") + roomName
  + "' not found for RGScript move on line: "
  + std::to_string(TextHelper::line));
}

bool TextHelper::cpMoveNPC(std::vector<std::string> params) {
  std::string roomName;
  std::string npcName = params.front();
  params.erase(params.begin());
  for (std::string s : params) {
    roomName += s;
  }
  for (Room* room : InteractHelper::getMap()->getRooms()) {
    if (tolower(trimAll(room->getName())) == trimAll(roomName)) {
      NPC* npc = InteractHelper::getNPC(npcName);
      if (npc != nullptr) {
        npc->moveNPC(room);
        return false;
      }
      throw std::runtime_error(std::string("NPC with name: '") + npcName
      + "' not found for RGScript movenpc on line: "
      + std::to_string(TextHelper::line));
    }
  }
  throw std::runtime_error(std::string("Room with name: '") + roomName
  + "' not found for RGScript movenpc on line: "
  + std::to_string(TextHelper::line));
}

bool TextHelper::cpKillNPC(std::vector<std::string> params) {
  std::string npcName;
  for (std::string s : params) {
    npcName += s;
  }
  NPC* npc = InteractHelper::getNPC(npcName);
  if (npc != nullptr) {
    npc->setAlive(false);
    return false;
  }
  throw std::runtime_error(std::string("NPC with name '") + npcName
  + "' not found for RGScript killnpc on line: "
  + std::to_string(TextHelper::line));
}

bool TextHelper::fileExists(std::string path) {
  std::ifstream file(path);
  return file.good();
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
      s = " nothing useful.";
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

std::string TextHelper::listNPCs(std::vector<NPC*> npcs) {
  std:: string s = "";
  switch (npcs.size()) {
    case 0:
      s = "There is nobody else in the room with you.";
      return s;
    case 1:
      s = npcs[0]->getName() + " is here.";
      return s;
    default:
      for (NPC* n : npcs) {
        if (n == npcs.back()) {
          s += "and " + n->getName() + " are here.";
          continue;
        }
        s += n->getName() + ", ";
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
  if (s.size() == 0 ) { return ""; }
  s.erase(0, s.find_first_not_of(" \t\r\n"));
  s.erase(s.find_last_not_of(" \t\r\n") + 1, s.size() - 1);
  return s;
}

std::string TextHelper::trimAll(std::string s) {
  if (s.size() == 0 ) { return ""; }
  s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
  return s;
}

std::string TextHelper::keyify(std::string s) {
  if (s.size() == 0) { return ""; }
  s = tolower(trim(s));
  std::replace(s.begin(), s.end(), ' ', '_');
  return s;
}
