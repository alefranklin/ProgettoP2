#include "map.h"
#include "randomizer.h"
using namespace std;

int Map::minDim = 500;


Map::Map(int d) {
  //la mappa deve avere una dimensione minima
  if(d < minDim)  dim = minDim;
  else            dim = d;

  cout << "dim:" << dim << endl;

  // instanzio i vettori della mappa
  map = vector<vector<Tile>>(dim, vector<Tile>(dim, Tile()));
  map[1][8] = Tile(false);
  // costruisco la mappa
  //  -> creo spazi aperti
  //  -> creo corridoi
  //  -> posiziono oggetti e mob in maniera random

  // aggiorno la posizione iniziale
  changePos(RandomPos());

}

// moveUP()
// moveDOWN()
// moveLEFT()
// moveRIGHT()

void Map::setPos(Coordinate newPos) {
  changePos(newPos);
}

Coordinate Map::getPos() const {
  return pos;
}

Coordinate Map::getRelativePos() const {
  return relativePos;
}

vector<vector<Tile>> Map::getSmallMap(int radius) {
  vector<vector<Tile>> smallMap(radius*2, vector<Tile>(radius*2, Tile(false)));

  for(int x = 0; x < radius*2; x++)
    for(int y = 0; y < radius*2; y++) {
      int map_x = pos.x-radius+x;
      int map_y = pos.y-radius+y;
      smallMap[x][y] = map[ map_x ][ map_y ];

      // trovo la posizione relativa
      if(pos.x == map_x && pos.y == map_y)
        changeRelativePos(Coordinate(x, y));
    }

  return smallMap;
}

void Map::printMap(vector<vector<Tile>> m) const {
  for(int x = 0; x < m.size(); x++){
    for(int y = 0; y < m[x].size(); y++){
      cout << m[x][y].walkable;
    }
    cout << endl;
  }
}

Coordinate Map::RandomPos() const {
  // vettore contenente le /possibili posizioni
  // in cui è possibile spawnare sulla mappa
  vector<Coordinate> possiblePos;

  // trovo tutte le possibili posizioni
  for(int x = 0; x < dim; x++){
    for(int y = 0; y < dim; y++){
      if(map[x][y].walkable == true){
        possiblePos.push_back(Coordinate(x,y));
      }
    }
  }
  // ne scelgo una a caso
  if(possiblePos.size()) {
     int selected = Randomizer::randomNumberBetween(0, possiblePos.size()-1);
    return possiblePos[selected];
  }
  return Coordinate();   //da fixare
}

// cambio la posizione e aggiorno la visibilità
void Map::changePos(Coordinate newPos) {
  pos = newPos;
}

void Map::changeRelativePos(Coordinate newRelativePos) {
  relativePos = newRelativePos;
}
