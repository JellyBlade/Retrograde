/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>
#include <string>

#include "Puzzle.h"
#include "TextHelper.h"

Puzzle::Puzzle() : solved{false} {}

bool Puzzle::isPuzzleSolved() {
  return solved;
}

bool Puzzle::setSolved(std::istream& input) {
  solved = true;
  std::string puzzleText = "text/puzzles/"
  + TextHelper::tolower(TextHelper::trimAll(getName())) + ".txt";
  if (TextHelper::fileExists(puzzleText)) {
    TextHelper::readFile(puzzleText, input);
    return true;
  }
  return false;
}
