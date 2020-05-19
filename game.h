#ifndef GAME_H
#define GAME_H

#include <ostream>
#include "map.h"
#include "character.h"
#include "item.h"
class Game {
public:

private:
  void fight(Character *pg, vector<Character *> enemies);
private:
  Player *PG;
  Map *map;
};
#endif
