/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/
#include <iostream>
#include <string>
#include <stdexcept>

#include "LockedBox.h"
#include "GenerateHelper.h"
#include "TextHelper.h"

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
  playerInput(std::cin);
}

bool LockedBox::playerInput(std::istream& input) {
  if (puzzle->isPuzzleSolved()) {
    Box::displayBoxObjects();
    Box::playerInput(input);
  } else {
    std::cout << "This " << getName() << " is locked by a "
    << puzzle->getName() << std::endl;
    puzzle->interact();
    if (puzzle->isPuzzleSolved()) {
      std::string choice;
      std::cout << "Would you like to take a look inside of the " << getName()
      << "? (y/n)" << std::endl << "> ";
      std::getline(input, choice);
      if (TextHelper::tolower(TextHelper::trimAll(choice))[0] == 'y') {
        Box::displayBoxObjects();
        if (getBoxObjects()->size() > 0) {
          Box::playerInput(input);
        }
      }
    }
  }
}

Puzzle* LockedBox::getPuzzle() {
  return puzzle;
}
