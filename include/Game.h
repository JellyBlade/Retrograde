
/**
* @author Tyrell M, Tyler H, Landon C, Truman L
* @date 2021-11
*/

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <iostream>
#include <vector>
#include "Map.h"
#include "PlayerHandler.h"
#include "NPC.h"

class Game {
public:
  /**
  * Constructor for the game.
  */
  Game();

  /**
  * Destructor.
  */
  ~Game();

  //TODO: Maybe this function throws an exception if the vector is size 0.
  /**
  * Returns the npcs in the game.
  * @return vector<NPC> npcs that are in the game
  */
  vector<NPC*> getNPC();

  /**
  * Calls each door to propogateOxygen().
  */
  void oxygenCalc();

  /**
  * Prompt the user for actions they want to perform.
  */
  void playerTurn();

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

private:
  vector<NPC*> npcs;
  Map* map;
  PlayerHandler* player;

};

#endif
