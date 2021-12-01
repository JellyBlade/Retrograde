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

void PasswordLock::interact() {
  //TODO(mart2720): This function probably needs to change
  std::string temp;
  cout << "Enter the password. It's case sensitive" << endl;
  std::getline(std::cin, temp);

  if (password == temp) {
    setSolved();
  } else {
    cout << "Incorrect password." << endl;
  }
}
