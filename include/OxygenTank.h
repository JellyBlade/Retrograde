/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef OXYGENTANK_H
#define OXYGENTANK_H

#include <string>

#include "Object.h"

/**
* Represents the oxygenTank object in the game.
*/
class OxygenTank : public Object {
 public:
  /**
  * Constructor, sets the name, desciption and matchingName of the object.
  * @param n string that the name will be set to.
  * Default value is "Oxygen Tank".
  * @param d string that the description will be set to.
  * Default value is "Refills the room or space suit oxygen".
  * @param h bool that holdable will be set to.  Default value is false.
  */
  OxygenTank(std::string n = "Object", std::string d =
  "This object does nothing", bool h = false);

  /**
  * Refills the oxygen spaceSuits oxygen tank
  */
  void interact();
};

#endif
