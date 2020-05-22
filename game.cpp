#include "game.h"

void Game::move(char m) {
  switch (m) {
    case 'w': map.moveUP();     break;
    case 'a': map.moveLEFT();   break;
    case 's': map.moveDOWN();   break;
    case 'd': map.moveRIGHT();  break;
    default:  break;
  }
}

void Game::fight(Character *pg, vector<Character *> enemies) {
  cout << "la lotta sta iniziando";
}

