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
class Log : Object {
 public:
  /**
  * Reads the .txt file at bookPath and outputs to the screen
  */
  void interact();

 private:
  string textPath;
};

#endif
