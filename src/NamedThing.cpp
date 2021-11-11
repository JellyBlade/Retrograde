/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>
#include <string>
#include "NamedThing.h"

NamedThing::NamedThing(std::string n, std::string d) : name{n}, description{d}
{}

std::string NamedThing::getName() {
  return name;
}

void NamedThing::setName(std::string newName) {
  name = newName;
}

std::string NamedThing::getDescription() {
  return description;
}

void NamedThing::setDescription(std::string newDescription) {
  description = newDescription;
}
