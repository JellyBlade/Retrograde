/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <string>
#include <map>

#include "Globals.h"
#include "TextHelper.h"

using Globals::Direction;

Direction Globals::stringToDirection(std::string s) {
  s = TextHelper::tolower(TextHelper::trimAll(s));
  static std::map<std::string, Direction> const lookup = {
    {"north", Direction::NORTH},
    {"n", Direction::NORTH},
    {"east", Direction::EAST},
    {"e", Direction::EAST},
    {"south", Direction::SOUTH},
    {"s", Direction::SOUTH},
    {"west", Direction::WEST},
    {"w", Direction::WEST}
  };
  auto it = lookup.find(s);
  if (it != lookup.end()) {
    return it->second;
  } else { throw std::exception{}; }
}

std::string Globals::directionToString(Direction d) {
  switch (d) {
    case NORTH: return "north";
    case EAST: return "east";
    case SOUTH: return "south";
    case WEST: return "west";
    default: return "unknown direction";
  }
}
