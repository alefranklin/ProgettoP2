#include "character.h"
#include "entity.h"
#include <iostream>
#include <vector>
using namespace std;

  //CLASSE CHARACTER
  Character::Character(int v, int m): vita(v), mana(m), Entity() { cout << "istanzio Character: " << endl; }
  int Character::getVita() { return vita; }
  int Character::getMana() { return mana; }
  void Character::setDamage(int d) { vita = (vita-d >= 0) ? vita-d : 0; isAlive(); }

  //CLASSE PLAYER
  Player::Player(int v, int m): Character(v, m) {}
  void Player::save() { cout << "salvo Player " << endl; }
  void Player::info() { cout << "sono Player " << " con " << getVita() << " di vita e " << getMana() << " di mana" << endl;}
  bool Player::isAlive() { 
    if(getVita()) { cout << "non sono ancora morto bastardo!" << endl; return true;}
    else { cout << "Player " << " è morto" << endl; return false;} 
  }


  //CLASSE MOB
  Mob::Mob(int v, int m): Character(v, m) {}
  void Mob::save() { cout << "salvo Mob " << endl; }
  void Mob::info() { cout << "sono Mob " << " con " << getVita() << " di vita e " << getMana() << " di mana" << endl;}
  bool Mob::isAlive() { 
    if(getVita()) { cout << "non sono ancora morto bastardo!" << endl; return true;}
    else { cout << "Mob " << " è morto" << endl; return false;}
  }