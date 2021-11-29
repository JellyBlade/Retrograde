/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>
#include <string>

#include "Box.h"
#include "TextHelper.h"
#include "InteractHelper.h"

using std::cout;
using std::endl;

Box::Box() {
  objects = new ObjectContainer();
  setHoldable(false);
}

Box::~Box() {
  delete objects;
}

void Box::addObject(Object* object) {
  objects->addObject(object);
}

ObjectContainer* Box::getBoxObjects() {
  return objects;
}

void Box::interact() {
  displayBoxObjects();
  if (getBoxObjects()->size() > 0) {
    // This line is untestable.
    playerInput(std::cin);
  }
}

void Box::displayBoxObjects() {
  cout << "You look into the box and find" << endl;
  TextHelper::listObjects(objects->getObjects());
}

bool Box::playerInput(std::istream& input) {
  std::string item = "";
  cout << "Which item did you want to pick up?" << endl;
  cout << "> ";
  std::getline(input, item);

  item = TextHelper::tolower(TextHelper::trimAll(item));

  if (objects->isObjectInContainer(item)) {
    InteractHelper::getPlayerHandler()->getPlayer()->getInventory()
      ->addObject(objects->getObject(item));
    objects->removeObject(objects->getObject(item));
    return true;

  } else {
    cout << "Could not find item." << endl;
    return false;
  }
}
