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
  std::string item;
  cout << "You look into the box and find" << endl;
  TextHelper::listObjects(objects->getObjects());
  cout << "Which item did you want to pick up?" << endl;
  cout << "> ";
  std::cin >> item;

  if (objects->isObjectInContainer(item)) {
    //TODO(mart2720): how do i add it to the specific player's inventory?
    // (hipt2720): Use InteractHelper like so
    // We could probably add a function to InteractHelper to directly
    // add/remove objects to the player's inventory too.
    InteractHelper::getPlayerHandler()->getPlayer()->getInventory()
      ->addObject(objects->getObject(item));
    objects->removeObject(objects->getObject(item));

  } else {
    cout << "Could not find item." << endl;
  }
}
