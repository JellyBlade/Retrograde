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
class Box : public Object {
 public:

  /**
  * Default Constructor
  */
  Box();

  /**
  * Destructor
  */
  ~Box();

  /**
  * Returns the objectContainer of the box
  * @return objects ObjectContainer that the box has
  */
  ObjectContainer* getBoxObjects();

  /**
  * Adds the given Object to this container.
  * @param object the Object to add.
  */
  void addObject(Object* object);

  /**
  * Displays objects inside the container, asks user which one to take
  */
  void interact();

 private:
  ObjectContainer* objects;
};

#endif
