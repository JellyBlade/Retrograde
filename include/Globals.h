/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>

/**
* Provides enums, and functions for handling said enums.
*/
namespace Globals {
  enum Direction { NORTH, EAST, SOUTH, WEST };

  /**
  * Converts a string into a Direction.
  * @param s the string to convert.
  * @return a Direction corresponding to the given string.
  */
  Direction stringToDirection(std::string s);

  /**
  * Converts a Direction into a string.
  * @param d the Direction to convert.
  * @return a string corresponding to the given Direction.
  */
  std::string directionToString(Direction d);
} // namespace Globals

#endif // GLOBALS_H
