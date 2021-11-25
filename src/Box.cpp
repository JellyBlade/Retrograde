/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#include <iostream>
#include <string>

#include "Box.h"

using std::cout;
using std::endl;

Box::Box(/*ObjectContainer* ob*/) {
  /*std::cout << "Im assuming seg fault is here " << std::endl;
  for (int i = 0; i < ob->size(); i++) {
    std::cout << "is it a certain line? " << std::endl;
    std::cout << "Does the vector have objects in it? Size = " << ob->size() << std::endl;
    std::cout << "Does the object have an address? " << ob->getObjects()[i] << std::endl;
    //objects.addObject(ob->getObjects()[i]);
    std::cout << "We got past the line woohoo " << objects.getObjects().size() << std::endl;
  }*/
  setHoldable(false);
}

void Box::addObject(Object* object) {
  std::cout << "Does it call this function? " << std::endl;
  objects.addObject(object);
}

ObjectContainer Box::getBoxObjects() {
  return objects;
}

void Box::interact() {
  std::string item;
  cout << "You look into the box and find";
  for (int i = 0; i < objects.size(); i++) {
    if (objects.size() == 0) {
      cout << " nothing." << endl;
      return;
    }
    cout << ":" << endl;
    for (Object* o : objects.getObjects()) {
      cout << " - " << o->getName() << endl;
    }
  }
  cout << "Which item did you want to pick up?" << endl;
  std::cin >> item;

  if (objects.isObjectInContainer(item)) {
    objects.removeObject(objects.getObject(item));
    //TODO(mart2720): how do i add it to the specific player's inventory?
  } else {
    cout << "Could not find item." << endl;
  }
}
