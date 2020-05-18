#ifndef GAME_H
#define GAME_H

#include <ostream>

class Mappa;
class Player;
class Character;

class Game {
public:


private:
  void fight(Character *pg, vector<Character *> enemies) {

    cout << "la lotta sta iniziando";

  }


private:

  Player *PG;
  Mappa *map;



};
#endif
