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
  * @param s string that textPath will be set to
  */
  Log(std::string s);

  /**
  * Reads the .txt file at bookPath and outputs to the screen
  */
  void interact();

 private:
  std::string textPath;
};

#endif
