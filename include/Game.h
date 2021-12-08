/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Map.h"
#include "PlayerHandler.h"
#include "NPC.h"

/**
* Represents the state of the game. Will generate NPCs and Map. Will determine
* win/lose conditions of the game
*/
class Game {
 public:
  /**
  * Default constructor for the game.
  */
  Game();

  /**
  * Destructor.
  */
  ~Game();

  /**
  * Returns the npcs in the game.
  * @return vector<NPC> npcs that are in the game
  */
  std::vector<NPC*> getNPCs();

  /**
  * The core gameplay loop. Checks for win/lose conditions, prompts player
  * to perform actions, and calls for oxygen calculation when needed.
  */
  void play();

  /**
  * Displays several endings based on the actions performed, puzzles solved,
  * and overall ship oxygen by the end.
  */
  void playerWin();

  /**
  * Displays several lose endings based on how the player met their demise.
  */
  void playerLose();

  /**
  * Generates the map and rooms, and distrubtes objects as needed.
  */
  void generateMap();

  /**
  * Create the NPCs and sets their positions to specific rooms.
  */
  void generateNPCs();

  /**
  * Adds the given NPC to the game's list of NPCs.
  */
  void addNPC(NPC* npc);

  /**
  * Returns a pointer to the game environment.
  * @return the Map for the game, containing all rooms and doors.
  */
  Map* getMap();

  /**
  * Returns a pointer to the PlayerHandler class.
  * @return the PlayerHandler for the game, which handles the Player class.
  */
  PlayerHandler* getPlayerHandler();

 private:
  std::vector<NPC*> npcs;
  Map* map;
  PlayerHandler* player;
};

#endif
