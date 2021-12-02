/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef NPC_H
#define NPC_H

#include <string>
#include <iostream>

#include "Room.h"
#include "NamedThing.h"

class NPC : public NamedThing {
 public:
  /**
  * constructor
  * @param n Name of the NPC
  * @param d Description of the NPC
  */
  NPC(std::string n = "NPC", std::string d = "This is an NPC.");

  /**
  * Displays dialogue from text based on NPC name.
  */
  void talk(std::istream& input);

  /**
  * Ask for information based on a specific set of questions.
  */
  void ask(std::istream& input);

  /**
  * Kills the NPC, preventing them from using oxygen, and disabling interaction.
  * Does not delete the NPC.
  */
  void stab(std::istream& input);

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

  /**
  * Returns the alive value
  * @return alive bool value of the Alive state.
  */
  bool isAlive();

  /**
  * Sets this NPC's alive value to the given bool.
  * @see TextHelper::cpKillNPC()
  */
  void setAlive(bool newVal);

 private:
  Room* currentRoom;
  bool alive;
};

#endif // NPC_H
