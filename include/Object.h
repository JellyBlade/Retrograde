/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include "NamedThing.h"

/**
* Describes all objects in the game, some can be picked up and all can be
* interacted with.
*/
class Object : NamedThing {
public:

  /**
  * Constructor, sets the name and desciption of the object.
  */
  Object(string n = "Object", string d = "Does nothing", bool h = true);

  /**
  * Returns the object's holdable value.
  * @return bool holdable value of the objet.
  */
  bool isHoldable();

  /**
  * sets the object's holdable value
  * @param bool ob the value the object's holdable value will be set to
  */
  void setHoldable(bool ob);

  /**
  * interaction of the object depending on what the object is.
  */
  virtual void interact();

private:
  bool holdable;
};

#endif
