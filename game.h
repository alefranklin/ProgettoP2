#ifndef GAME_H
#define GAME_H

#include <ostream>
#include "map.h"
#include "character.h"
#include "item.h"
class Game {
public:
  void move(char m);

  static bool isItem(const Entity *e);
  static bool isWeapon(const Entity *e);
  static bool isArmor(const Entity *e);
  static bool isPotion(const Entity *e);
  static bool isCharacter(const Entity *e);
  static bool isMob(const Entity *e);
  static bool isPlayer(const Entity *e);

private:
  void fight(Character *pg, vector<Character *> enemies);
private:
  Player *PG;
  Map map;
};

#endif
