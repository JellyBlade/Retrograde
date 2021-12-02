/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef PUZZLE_H
#define PUZZLE_H

#include <string>
#include <iostream>

#include "Object.h"

/**
* Interface for the different puzzles.
*/
class Puzzle : public Object {
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
  * Sets the solved value to true.
  * Also reads a puzzle text file if it exists for this puzzle's name.
  */
  void setSolved(std::istream& input);

  /**
  * Handles any player input required, and provides an istream source for
  * TextHelper::readFile() for setSolved()
  * @return true if the puzzle was solved, false otherwise.
  */
  virtual bool playerInput(std::istream& input) {}

 private:
  bool solved;
};

#endif
