/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>

#include "Puzzle.h"

Puzzle::Puzzle() : solved{false} {}

bool Puzzle::isPuzzleSolved() {
  return solved;
}

void Puzzle::setSolved() {
  solved = true;
}
