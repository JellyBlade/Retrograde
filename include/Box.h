/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef BOX_H
#define BOX_H

#include "Object.h"
#include "ObjectContainer.h"

/**
* Represents an object that has objects inside them
*/
class Box : Object {
 public:
  /**
  * Displays objects inside the container, asks user which one to take
  */
  void interact();

 private:
  ObjectContainer objects;
};

#endif
