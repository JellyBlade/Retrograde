/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>
#include <string>

#include "TextHelper.h"
#include "PasswordLock.h"

using std::cout;
using std::endl;

PasswordLock::PasswordLock(std::string n, std::string d, bool h, std::string p)
: password{p} {
  setName(n);
  setDescription(d);
  setHoldable(h);
}

//This is untestable
void PasswordLock::interact() {
  playerInput(std::cin);
}

bool PasswordLock::playerInput(std::istream& input) {
  if (isPuzzleSolved()) {
    cout << "This " << getName() << " is already solved." << endl;
    return true;
  }
  std::string item = "";
  cout << "Enter the password. It's case-sensitive." << endl;
  cout << "> ";
  std::getline(input, item);

  if (item == password) {
    if (setSolved(input)) { return true; }
    cout << "Password accepted." << endl;
    return true;
  } else {
    cout << "Incorrect password." << endl;
    return false;
  }
}
