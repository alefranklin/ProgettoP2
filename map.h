#ifndef MAP_H
#define MAP_H

#include <vector>
#include "entity.h"

struct Coordinate {
  int row;
  int col;
  Coordinate(int row=0, int col=0): row(row), col(col) {}
};

struct Tile {
  Entity* e;
  bool walkable;
  Tile(bool w = false, Entity* en = nullptr): walkable(w), e(en) {}
};

class Map {
public://
  Map(int d = 0);

  //test push con aton

  // moveUP()
  // moveDOWN()
  // moveLEFT()
  // moveRIGHT()

  void setPos(Coordinate newPos);
  Coordinate getPos() const;
  Coordinate getRelativePos() const;

  std::vector<std::vector<Tile>> getMiniMap(int radius);

  void printMap(std::vector<std::vector<Tile>> m) const;
//qui giace la funzione pronta

private:
  static int minDim;
  int dim;
  std::vector<std::vector<Tile>> map;
  Coordinate pos;
  Coordinate relativePos;

  Coordinate RandomPos() const;
  // cambio la posizione e aggiorno la visibilità
  void changePos(Coordinate newPos);
  void changeRelativePos(Coordinate newRelativePos);

};

#endif
