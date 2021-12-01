/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/
#include <iostream>
#include <string>

#include "LockedBox.h"

LockedBox::LockedBox(std::string n, std::string d, bool h, Puzzle* p)
: puzzle{p} {
  setName(n);
  setDescription(d);
  setHoldable(h);
}

LockedBox::~LockedBox() {
  delete puzzle;
}

void LockedBox::interact() {
  if (puzzle->isPuzzleSolved()) {
    Box::interact();
  } else {
    std::cout << "This box is locked, gotta find a way to unlock it."
    << std::endl;
  }
}

Puzzle* LockedBox::getPuzzle() {
  return puzzle;
}
