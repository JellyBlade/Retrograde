/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef NPC_H
#define NPC_H

#include "Room.h"

class NPC : public NamedThing {
 public:
  /**
  * Displays dialogue from text based on NPC name.
  */
  void talk();

  /**
  * Ask for information based on a specific set of questions.
  */
  void ask();

  /**
  * Kills the NPC, preventing them from using oxygen, and disabling interaction.
  * Does not delete the NPC.
  */
  void stab();

  /**
  * Gets and returns the room the NPC is currently in.
  * @return the room the NPC is in.
  */
  Room* getCurrentRoom();

  /**
  * Moves the NPC to the given room.
  * @param room the room to move to.
  */
  void moveNPC(Room* room);

  /**
  * Reduces the oxygen in the current room.
  * Kills the NPC if the room is a vacuum.
  */
  void useOxygen();

 private:
  Room* currentRoom;
};

#endif // NPC_H
