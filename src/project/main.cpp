#include <iostream>
#include <string>

#include "Game.h"
#include "InteractHelper.h"
#include "TextHelper.h"

int main() {
  std::string choice;
  while (1) {
    Game* game = new Game();
    InteractHelper::game = game;
    game->generateMap();
    game->generateNPCs();
    TextHelper::readFile("text/intro.txt");
    game->play();
    TextHelper::rgScriptGlobalFlags.clear();
    delete game;

    std::cout << "Would you like to play again?" << std::endl;
    std::cout << "> ";
    std::getline(std::cin, choice);
    if (TextHelper::tolower(TextHelper::trimAll(choice))[0] != 'y') {
      break;
    }
  }
}
