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
  virtual ~Inventory() = 0;

  /**
  * Unlocks the spacesuit for the player, allowing them to survive in a vacuum.
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
  double getOxygen();

  /**
  * Sets the spacesuit's internal oxygen tank to the specified value.
  * @param oxygen the value to set the tank's oxygen level to.
  */
  void setOxygen(double oxygen);

  /**
  * Adds the given object to the inventory, if object->isHoldable() is true.
  * @param object the Object to add.
  */
  void addObject(Object* object);

 private:
  bool spaceSuitAcquired;
  double oxygen;
}

#endif // INVENTORY_H
