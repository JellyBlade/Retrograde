/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef PUZZLE_H
#define PUZZLE_H

#include "Object.h"

/**
* Interface for the different puzzles.
*/
class Puzzle : Object {
 public:
  /**
  * Default constructor sets solved to false.
  */
  Puzzle();

  /**
  * returns the boolean value of solved.
  * @return bool solved the boolean value of the Puzzle
  */
  bool isPuzzleSolved();

  /**
  * sets the solved boolean value of the puzzle to true.
  */
  void setSolved();

 private:
  bool solved;
};

#endif
