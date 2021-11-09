/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef LOCKEDBOX_H
#define LOCKEDBOX_H

#include "Object.h"
#include "Puzzle.h"

/**
* A box that will show it's object to the user if the puzzle has been solved.
*/
class LockedBox : Object {
public:
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
