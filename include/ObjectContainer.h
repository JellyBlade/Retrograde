/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef OBJECT_CONTAINER_H
#define OBJECT_CONTAINER_H

#include <vector>
#include <string>

#include "Object.h"

/**
* Provides implementation for storing and interacting with a group of objects.
*/
class ObjectContainer {
 public:
  /**
  * Default constructor.
  */
  ObjectContainer();

  /**
  * Destructor.
  */
  virtual ~ObjectContainer() = 0;

  /**
  * Returns an int for the number of objects held in this container.
  * @return the size of this container.
  */
  int size();

  /**
  * Removes all objects in this container.
  */
  void clear();

  /**
  * Adds the given Object to this container.
  * @param object the Object to add.
  */
  void addObject(Object* object);

  // TODO(hipt2720): Should this throw something if the object is null?
  /**
  * Removes the given Object to this container. Does nothing if the objects
  * is not in the container.
  * @param object the Object to remove.
  */
  void removeObject(Object* object);

  // NOTE: Is this function even useful? It requires the object itself to
  // get it, so it's pretty useless.
  Object* getObject(Object* object);

  /**
  * Returns the Object in the container with the same name.
  * Calls isObjectInContainer(string).
  * @return the Object if found, or a nullptr.
  */
  Object* getObject(string objectName);

  /**
  * Returns a vector containing all of the objects in this container.
  * @return a vector<Object*> of this container's contents.
  */
  vector<Object*> getObjects();

  /**
  * Checks if the given object is in this container.
  * @param object the Object to look for.
  * @return true if object is in the container, false otherwise.
  */
  bool isObjectInContainer(Object* object);

  /**
  * Checks if an object with the given name is in this container.
  * Not guaranteed to be the exact same Object.
  * @param objectName the name of the object to search for.
  * @return true if an object with the same name is in the container,
  * false otherwise.
  */
  bool isObjectInContainer(string objectName);

 private:
  Vector<Object*> objects;
}

#endif // OBJECT_CONTAINER_H
