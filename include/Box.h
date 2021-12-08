/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef BOX_H
#define BOX_H

#include <iostream>
#include <string>

#include "Object.h"
#include "ObjectContainer.h"

/**
* Represents an object that has objects inside them
*/
class Box : public Object {
 public:
  /**
  * Constructor
  * @param n string that the name will be set to. Default value is "Box".
  * @param d string that the description will be set to.
  * Default value is "This is a box.".
  * @param h bool Whether it can be picked up by the Player. Default is false.
  */
  Box(std::string n = "Box", std::string d = "This is a box.",
  bool h = false);

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
  * Displays objects inside the container, asks user which one to take.
  * Calls displayBoxObjects, and playerInput if there are any items to take.
  */
  void interact();

  /**
  * Asks for user input on which object from the box to grab, if any.
  * @param input istream to use for input. cin for user, fstream for testing.
  */
  bool playerInput(std::istream& input);

  /**
  * Lists the objects in the box to the screen in a formatted way, using
  * TextHelper::listObjects.
  */
  void displayBoxObjects();

 private:
  ObjectContainer* objects;
};

#endif
