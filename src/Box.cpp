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

Box::Box(std::string n, std::string d, bool h) {
  setName(n);
  setDescription(d);
  setHoldable(h);
  objects = new ObjectContainer();
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
    playerInput(std::cin);
  }
}

void Box::displayBoxObjects() {
  cout << "You look into the " << getName() << " and find";
  cout << TextHelper::listObjects(objects->getObjects()) << endl;
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
    cout << "You can't find that in this " << getName() << "." << endl;
    return false;
  }
}
