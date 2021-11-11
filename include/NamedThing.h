/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

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
  NamedThing(std::string n = "Thing", std::string d = "Does nothing");

  /**
  * Returns this thing's name.
  * @return a string containing this thing's name.
  */
  std::string getName();

  /**
  * Changes this thing's name to the given string.
  * @param newName the name to change to.
  */
  void setName(std::string newName);

  /**
  * Returns this thing's description.
  * @return a string describing this thing.
  */
  std::string getDescription();

  /**
  * Changes this thing's description to the given string.
  * @param newDescription the description to change to.
  */
  void setDescription(std::string newDescription);

 private:
  std::string name;
  std::string description;
};

#endif // NAMED_THING_H
