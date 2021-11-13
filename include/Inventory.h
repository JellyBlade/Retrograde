/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>

#include "Object.h"
#include "ObjectContainer.h"

/**
* The Player's inventory. Extends ObjectContainer to provide support for
* the spacesuit upgrade and oxygen level.
*/
class Inventory : public ObjectContainer {
 public:
  /**
  * Default constructor.
  */
  Inventory();

  /**
  * Destructor.
  */
  ~Inventory();

  /**
  * Unlocks the spacesuit for the player, allowing for survival in a vacuum.
  * Fills oxygen.
  */
  void giveSpaceSuit();

  /**
  * Checks if the player has unlocked the spacesuit.
  * @return true if the player has the spacesuit, false otherwise.
  */
  bool hasSpaceSuit();

  /**
  * Returns the oxygen level of the spacesuit's internal oxygen tank, 0.00-1.00
  * @return a double showing the current oxygen level of the spacesuit.
  */
  int getOxygen();

  /**
  * Sets the spacesuit's internal oxygen tank to the specified value.
  * @param oxygen the value to set the tank's oxygen level to.
  */
  void setOxygen(int o);

  /**
  * Adds the given object to the inventory, if object->isHoldable() is true.
  * @param object the Object to add.
  */
  void addObject(Object* object);

 private:
  bool spaceSuitAcquired;
  int oxygen;
};

#endif // INVENTORY_H
