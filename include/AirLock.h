/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef AIRLOCK_H
#define AIRLOCK_H

#include <string>
#include "Puzzle.h"

/**
* Represents the airlock puzzle, must have a certain amount of oxygen to
* solve the puzzle.
*/
class AirLock : public Puzzle {
 public:
  /**
  * Constructor, sets the name, desciption and password of the object.
  * @param n string that the name will be set to. Default value is "Object".
  * @param d string that the description will be set to.
  * Default value is "This object does nothing".
  * @param h bool that holdable will be set to.  Default value is true.
  * @param o double value that the oxygenTarget will be set to.
  * Default value is 0.0.
  */
  AirLock(string n = "Object", string d = "This object does nothing",
  bool h = false, double o = 0.0);

  /**
  * Check if the roomOxygen >= oxygenTarget
  */
  void interact();

 private:
  double oxygenTarget;
};

#endif
