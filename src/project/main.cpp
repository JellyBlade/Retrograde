#include "Game.h"

int main() {
  Game* game = new Game();
  game->generateMap();
  game->playerTurn();
  delete game;
}
