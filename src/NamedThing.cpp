/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>
#include <string>
#include "NamedThing.h"

using namespace std;

NamedThing::NamedThing(string n, string d) : name{n}, description{d} {}

string NamedThing::getName() {
  return name;
}

void NamedThing::setName(string newName) {
  name = newName;
}

string NamedThing::getDescription() {
  return description;
}

void NamedThing::setDescription(string newDescription) {
  description = newDescription;
}
