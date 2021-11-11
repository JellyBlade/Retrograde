/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef TEXT_HELPER_H
#define TEXT_HELPER_H

#include <string>
#include <iostream>

/**
* Provides functions for handling file reading, command strings, and modifying
* strings.
*/
namespace TextHelper {

  /**
  * Outputs dialogue from file to screen,
  * calling commandProcessor if it encounters a script command to execute.
  * @param textPath to the path of the file to read from.
  */
  void readFile(std::string textPath);

  /**
  * Performs functions based on the inputted command string, usually read
  * from a dialogue file.
  * @param command the script command to parse and execute.
  */
  void commandProcessor(std::string command);

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
