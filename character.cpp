#include "character.h"
#include "entity.h"
#include <iostream>
#include <vector>
using namespace std;

  //CLASSE CHARACTER
  Character::Character(int i, int v, int m): vita(v), mana(m), Entity(i) { cout << "istanzio Character: " << getId() << endl; }
  int Character::getVita() { return vita; }
  int Character::getMana() { return mana; }
  void Character::setDamage(int d) { vita = (vita-d >= 0) ? vita-d : 0; isAlive(); }

  //CLASSE PLAYER
  Player::Player(int i, int v, int m): Character(i, v, m) {}
  void Player::save() { cout << "salvo Player " << getId() << endl; }
  void Player::info() { cout << "sono Player " << getId() << " con " << getVita() << " di vita e " << getMana() << " di mana" << endl;}
  bool Player::isAlive() { 
    if(getVita()) { cout << "non sono ancora morto bastardo!" << endl; return true;}
    else { cout << "Player " << getId() << " è morto" << endl; return false;} 
  }


  //CLASSE MOB
  Mob::Mob(int i, int v, int m): Character(i, v, m) {}
  void Mob::save() { cout << "salvo Mob " << getId() << endl; }
  void Mob::info() { cout << "sono Mob " << getId() << " con " << getVita() << " di vita e " << getMana() << " di mana" << endl;}
  bool Mob::isAlive() { 
    if(getVita()) { cout << "non sono ancora morto bastardo!" << endl; return true;}
    else { cout << "Mob " << getId() << " è morto" << endl; return false;}
  }