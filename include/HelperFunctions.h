#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <string>
#include <iostream>

/**
* Provides global functions for reading and interpreting dialogue files,
* and enums.
*/
namespace HelperFunctions {
  enum Direction { NORTH, EAST, SOUTH, WEST };

  /**
  * Outputs dialogue from file to screen,
  * calling commandProcessor if it encounters a script command to execute.
  * @param textPath to the path of the file to read from.
  */
  void readFile(string textPath);

  /**
  * Performs functions based on the inputted command string, usually read
  * from a dialogue file.
  * @param command the script command to parse and execute.
  */
  void commandProcessor(string command);

  /**
  * Converts a string into a Direction.
  * @param s the string to convert.
  * @return a Direction corresponding to the given string.
  */
  Direction stringToDirection(string s);

  /**
  * Converts a Direction into a string.
  * @param d the Direction to convert.
  * @return a string corresponding to the given Direction.
  */
  string directionToString(Direction d);
}

#endif // HELPER_FUNCTIONS_H
