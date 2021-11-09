#ifndef NAMED_THING_H
#define NAMED_THING_H

#include <string>

/**
* Provides implementation for things that have names and descriptions, such
* as rooms, NPCs, and all objects.
*/
class NamedThing {
 public:
  /**
  * Constructor
  */
  NamedThing(string name, string description);

  /**
  * Returns this thing's name.
  * @return a string containing this thing's name.
  */
  string getName()

  /**
  * Changes this thing's name to the given string.
  * @param newName the name to change to.
  */
  void setName(string newName);

  /**
  * Returns this thing's description.
  * @return a string describing this thing.
  */
  string getDescription();

  /**
  * Changes this thing's description to the given string.
  * @param newDescription the description to change to.
  */
  void setDescription(string newDescription);
 private:
  string name;
  string description;
}

#endif // NAMED_THING_H
