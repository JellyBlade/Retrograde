/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef OXYGENTANK_H
#define OXYGENTANK_H

#include "Object.h"

/**
* Represents the oxygenTank object in the game.
*/
class OxygenTank : public Object {
 public:
  /**
  * Refills the oxygen spaceSuits oxygen tank
  */
  void interact();
};

#endif
