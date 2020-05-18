#ifndef CHARACTER_H
#define CHARACTER_H

#include "entity.cpp"
#include "test_item.cpp"
#include <iostream>
#include <vector>
using namespace std;

class Weapon;

class Character: public Entity {
private:
  int vita;
  int mana;
  Weapon* arma;
  //Weapon* rmatura;
protected:
  Character(int i, int v, int m): vita(v), mana(m), Entity(i) { cout << "istanzio Character: " << getId() << endl; }
public:
  virtual void save() =0;
  int getVita() { return vita; }
  int getMana() { return mana; }
  void setDamage(int d) { vita = (vita-d >= 0) ? vita-d : 0; isAlive(); }
  virtual bool isAlive() =0;
  virtual void info() =0;

};

class Player: public Character {
public:
  Player(int i, int v, int m): Character(i, v, m) {}
  virtual void save() { cout << "salvo Player " << getId() << endl; }
  void info() { cout << "sono Player " << getId() << " con " << getVita() << " di vita e " << getMana() << " di mana" << endl;}
  bool isAlive() { if(getVita()) { cout << "non sono ancora morto bastardo!" << endl; return true;}
                   else { cout << "Player " << getId() << " è morto" << endl; return false;} }
};

class Mob: public Character {
public:
  Mob(int i, int v, int m): Character(i, v, m) {}
  virtual void save() { cout << "salvo Mob " << getId() << endl; }
  void info() { cout << "sono Mob " << getId() << " con " << getVita() << " di vita e " << getMana() << " di mana" << endl;}
  bool isAlive() { if(getVita()) { cout << "non sono ancora morto bastardo!" << endl; return true;}
                   else { cout << "Mob " << getId() << " è morto" << endl; return false;} }
};

#endif
