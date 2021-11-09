/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef LOG_H
#define LOG_H

#include "Object.h"
#include <string>

Class Log : Object {
public:
  /**
  * Reads the .txt file at bookPath and outputs to the screen
  */
  void interact();

private:
  string textPath;
};

#endif
