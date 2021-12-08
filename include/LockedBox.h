/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef LOCKEDBOX_H
#define LOCKEDBOX_H

#include <iostream>
#include <string>

#include "Puzzle.h"
#include "PasswordLock.h"
#include "Box.h"

/**
* A box that will show its objects to the user if the puzzle has been solved.
* LockedBox handles its own puzzle, and will generate it if one is not given.
*/
class LockedBox : public Box {
 public:
  /**
  * Constructor, sets the puzzle to p;
  * @param p Puzzle* that puzzle will be set to.
  */
  LockedBox(std::string n = "Locked Box", std::string d =
  "This is a locked box.", bool h = false, Puzzle* p = new PasswordLock());

  /**
  * Alternate constructor, which generates the Puzzle with the same name as the
  * given puzzleName string using GenerateHelper.
  * @param puzzleName the name of the puzzle to generate for this locked box.
  * @throws runtime_error if puzzleName isn't a valid puzzle name;
  */
  LockedBox(std::string n, std::string d, bool h, std::string puzzleName);

  /**
  * Destructor.
  */
  ~LockedBox();

  /**
  *
  */
  void interact();

  /**
  * Checks puzzle::isSolved() before displaying the box contents.
  * Will ask the player if they want to look when solving for the first time.
  * @param input istream to use for input. std::cin for player input,
  * fstream for testing.
  */
  bool playerInput(std::istream& input);

  /**
  * returns the puzzle object
  * @return puzzle Puzzle* in the Locked Box
  */
  Puzzle* getPuzzle();

 private:
  Puzzle* puzzle;
};

#endif
