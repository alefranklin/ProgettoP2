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

bool Game::isItem(const Entity *e) { return (dynamic_cast<const Item*>(e)) ? true : false; }
bool Game::isWeapon(const Entity *e) { return (dynamic_cast<const Weapon*>(e)) ? true : false; }
bool Game::isArmor(const Entity *e) { return (dynamic_cast<const Armor*>(e)) ? true : false; }
bool Game::isPotion(const Entity *e) { return (dynamic_cast<const Potion*>(e)) ? true : false; }
bool Game::isCharacter(const Entity *e) { return (dynamic_cast<const Character*>(e)) ? true : false; }
bool Game::isMob(const Entity *e) { return (dynamic_cast<const Mob*>(e)) ? true : false; }
bool Game::isPlayer(const Entity *e) { return (dynamic_cast<const Player*>(e)) ? true : false; }



void Game::fight(Character *pg, vector<Character *> enemies) {
  cout << "la lotta sta iniziando";
}