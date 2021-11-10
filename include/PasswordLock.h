/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef PASSWORDLOCK_H
#define PASSWORDLOCK_H

#include <string>
#include "Puzzle.h"


/**
* Represent the passwordLock puzzle, requires a string password to unlock
*/
class PassworkLock : Puzzle {
public:

  /**
  * Constructor, sets the name, desciption and password of the object.
  * @param n string that the name will be set to. Default value is "Object".
  * @param d string that the description will be set to.
  * Default value is "This object does nothing".
  * @param h bool that holdable will be set to.  Default value is true.
  * @param p string that the password will be set to. Default value is "1234".
  */
  PasswordLock(string n = "Object", string d = "This object does nothing",
  bool h = false, string p = "1234");

  /**
  * Prompt the password input to solve
  */
  void interact();

private:
  string password;

};

#endif
