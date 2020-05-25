#ifndef MAP_H
#define MAP_H

#include <vector>
#include "entity.h"

#include <iostream>

enum Biome {Valley, Desert, Doungeon, Street};

struct Coordinate {
  int row;
  int col;
  Coordinate(int row=0, int col=0): row(row), col(col) {}
  friend std::ostream& operator<<(std::ostream& out, const Coordinate &c);
};

struct Tile {
  Entity* e;
  bool walkable;
  Biome biome;
  Tile(bool w = true, Biome b = Valley, Entity* en = nullptr): walkable(w), biome(b), e(en) {}
};

class Map {
public:
  Map(int d = 0);

  void moveUP();
  void moveDOWN();
  void moveLEFT();
  void moveRIGHT();
  Tile& getCurrentTile();

  void createCircle(Coordinate center, int radius, Biome b); // va messa su private
  void createRectangle(Coordinate center, int width, int height, Biome b); // va messa su private
  void createLine(Coordinate start, Coordinate end, int thickness, Biome b); // va messa su private
  void Generatemap(); // va messa su private

  bool setPos(Coordinate newPos);
  Coordinate getPos() const;
  Coordinate getRelativePos() const;

  std::vector<std::vector<Tile>> getMiniMap(int size);

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
  Tile& getTileIn(Coordinate p);
  bool isWalkable(Coordinate p);
  bool isValid(Coordinate p) const;

};

#endif
