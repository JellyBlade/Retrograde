#include "Game.h"
#include "InteractHelper.h"

int main() {
  Game* game = new Game();
  InteractHelper::game = game;
  game->generateMap();
  game->playerTurn();
  delete game;
}
