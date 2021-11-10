/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>
#include <string>
#include "Object.h"
using namespace std;

Object::Object(string n, string d, bool h) : holdable{h} {
  setName(n);
  setDescription(d);
}

bool Object::isHoldable() {
  return holdable;
}

void Object::setHoldable(bool ob) {
  holdable = ob;
}

void Object::interact() {
  cout << "This object does nothing." << endl;
}
