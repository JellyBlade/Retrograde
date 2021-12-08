/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef LOG_H
#define LOG_H

#include "Object.h"
#include <string>

/**
* Represents embodies a type of object that is centered around the plot
* of the game. This will read a text file and output it to the screen
*/
class Log : public Object {
 public:
  /**
  * Constructor
  * @param n string that the name will be set to. Default value is "Log".
  * @param d string that the description will be set to.
  * Default value is "This is a log.".
  * @param h Whether it can be picked up by the Player. Default is true.
  * @param s the path of the file to read when interacting with this log.
  */
  Log(std::string n = "Log", std::string d = "This is a log.",
  bool h = true, std::string s = "text/logs/error_no_given_path.txt");

  /**
  * Reads the .txt file at bookPath and outputs to the screen
  */
  void interact();

 private:
  std::string textPath;
};

#endif
