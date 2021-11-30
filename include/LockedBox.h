/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef LOCKEDBOX_H
#define LOCKEDBOX_H

#include "Puzzle.h"
#include "PasswordLock.h"
#include "Box.h"

/**
* A box that will show it's object to the user if the puzzle has been solved.
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
  * Destructor.
  */
  ~LockedBox();

  /**
  * Checks puzzle::isSolved() before displaying objects.
  */
  void interact();

 private:
  Puzzle* puzzle;
};

#endif
