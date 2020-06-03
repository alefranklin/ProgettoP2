#ifndef CHARACTER_H
#define CHARACTER_H

#include "entity.h"
#include "item.h"
#include <vector>
using namespace std;

class Weapon;
class Armor;

class Character: public Entity {
private:
  int vita;
  int mana;
  Weapon* arma;
  Armor* armatura;
protected:
  Character(int v, int m);
public:
  virtual void save() =0;
  int getVita();
  int getMana();
  void setDamage(int d);
  virtual bool isAlive() =0;
  virtual void info() =0;

};

class Player: public Character {
public:
  Player(int v, int m);
  virtual void save();
  void info();
  bool isAlive();
};

class Mob: public Character {
public:
  Mob(int v, int m);
  virtual void save();
  void info();
  bool isAlive();
};

#endif
