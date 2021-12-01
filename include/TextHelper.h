/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef TEXT_HELPER_H
#define TEXT_HELPER_H

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "Object.h"
#include "Room.h"

/**
* Provides functions for handling file reading, command strings, and modifying
* strings.
*/
namespace TextHelper {
  extern std::map<std::string, bool> rgScriptFlags;
  /**
  * Outputs dialogue from file to screen,
  * calling commandProcessor if it encounters a script command to execute.
  * @param textPath to the path of the file to read from.
  */
  void readFile(std::string textPath, std::istream& input = std::cin);

  /**
  * Performs functions based on the inputted command string read
  * from a dialogue file.
  * @param command the script command to parse and execute.
  * @param file the file currently being read.
  * @param input the istream to use for user-input.
  * an fstream is used for automated testing, and std::cin is for user-input.
  * @return true if the file being read should be closed, false if it should
  * continue to be read.
  */
  bool commandProcessor(std::string command, std::istream& file,
    std::istream& input = std::cin);

  /**
  * Checks if the file at the given path exists.
  * @return true if the file exists, false otherwise.
  */
  bool fileExists(std::string path);

  /**
  * Turns the given integer into a fake percentage with two decimals of
  * precision by adding a decimal place two places from the last digit.
  * (10000 -> 100.00, 5500 -> 55.00)
  * @param i int to turn into a fake percentage.
  * @return a fake percentage version of the input integer.
  */
  std::string makePercent(int i);

  /**
  * Formats all of the object names in the list into a cohesive sentence.
  * @param objects the objects to list off.
  * @return a drop-in sentence that lists off all of the objects given, ending
  * with appropriate punctuation and grammar.
  */
  std::string listObjects(std::vector<Object*> objects);

  /**
  * Formats all of the room's doors into a cohesive sentence, listing doors
  * going clockwise from north.
  * @param room the room to list doors for.
  * @return a drop-in sentence that lists off all of the doors in the room,
  * ending with appropriate punctuation and grammar.
  */
  std::string listDoors(Room* room);

  /**
  * Determines if the string starts with a vowel.
  * @param s the string to check.
  * @return true if the string starts with a vowel, false otherwise.
  */
  bool startsWithVowel(std::string s);

  /**
  * Replaces all characters in the string with their lowercase counterparts.
  * @param s the string to turn into lowercase
  * @return a lowercase version of the input string.
  */
  std::string tolower(std::string s);

  /**
  * Replaces all characters in the string with their uppercase counterparts.
  * @param s the string to turn into uppercase.
  * @return an uppercase version of the input string.
  */
  std::string toupper(std::string s);

  /**
  * Removes leading/trailing whitespace from the string.
  * @param s the string to trim.
  * @return a string without whitespace at the beginning or end.
  */
  std::string trim(std::string s);

  /**
  * Removes all whitespace from the string.
  * @param s the string to remove all whitespace from.
  * @return a string without any whitespace.
  */
  std::string trimAll(std::string s);

} // namespace TextHelper

#endif // TEXT_HELPER_H
