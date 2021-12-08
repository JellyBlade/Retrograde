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
  * @param m string that the object will be set to. Default value is "Key".
  */
  ItemLock(std::string n = "Object", std::string d = "This object does nothing",
  bool h = false, std::string m = "Key");

  /**
  * Checks if the player has the item in their inventory
  */
  void interact();

  /**
  * Handles any player input required, and provides an istream source for
  * TextHelper::readFile() for setSolved()
  * @return true if the puzzle was solved, false otherwise.
  */
  bool playerInput(std::istream& input);

 private:
  std::string matchingName;
};

#endif
