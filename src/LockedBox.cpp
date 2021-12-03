/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/
#include <iostream>
#include <string>
#include <stdexcept>

#include "LockedBox.h"
#include "GenerateHelper.h"

LockedBox::LockedBox(std::string n, std::string d, bool h, Puzzle* p)
: puzzle{p} {
  setName(n);
  setDescription(d);
  setHoldable(h);
}

LockedBox::LockedBox(std::string n, std::string d, bool h,
std::string puzzleName) {
  setName(n);
  setDescription(d);
  setHoldable(h);
  puzzle = dynamic_cast<Puzzle*>(GenerateHelper::generateObject(puzzleName));
  if (puzzle == nullptr) {
    throw std::runtime_error("Puzzle with name: '" + puzzleName + "' not found"
    " when creating LockedBox with name: '" + n + "'.");
  }
}

LockedBox::~LockedBox() {
  delete puzzle;
}

void LockedBox::interact() {
  if (puzzle->isPuzzleSolved()) {
    Box::interact();
  } else {
    std::cout << "This box is locked by a " << puzzle->getName() << std::endl;
    puzzle->interact();
    if (puzzle->isPuzzleSolved()) {
      Box::interact();
    }
  }
}

Puzzle* LockedBox::getPuzzle() {
  return puzzle;
}
