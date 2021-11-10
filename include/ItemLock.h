/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef ITEMLOCK_H
#define ITEMLOCK_H

#include <string>
#include "Puzzle.h"

/**
* Represents the puzzle that requires a certain object to in the inventory to
* be solved
*/
class ItemLock : public Puzzle {
 public:
  /**
  * Constructor, sets the name, desciption and matchingName of the object.
  * @param n string that the name will be set to. Default value is "Object".
  * @param d string that the description will be set to.
  * Default value is "This object does nothing".
  * @param h bool that holdable will be set to.  Default value is true.
  * @param p string that the password will be set to. Default value is "1234".
  */
  ItemLock(string n = "Object", string d = "This object does nothing",
  bool h = false, string m = "");

  /**
  * Checks if the player has the item in their inventory
  */
  void interact();

 private:
  string matchingName;
};

#endif
