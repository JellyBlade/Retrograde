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
class Object : public NamedThing {
 public:
  /**
  * Constructor, sets the name and desciption of the object.
  * @param n string that the name will be set to. Default value is "Object".
  * @param d string that the description will be set to.
  * Default value is "This object does nothing".
  * @param h bool that holdable will be set to.  Default value is true.
  */
  Object(std::string n = "Thing", std::string d = "Does nothing",
  bool h = false);

  /**
  * Virtual destructor
  */
  virtual ~Object() {}

  /**
  * Returns the object's holdable value.
  * @return bool holdable value of the objet.
  */
  bool isHoldable();

  /**
  * sets the object's holdable value
  * @param ob bool the value of the object's holdable value will be set to
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
