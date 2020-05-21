#include "map.h"
#include "randomizer.h"
using namespace std;

int Map::minDim = 500;


Map::Map(int d): pos() {
  //la mappa deve avere una dimensione minima
  dim = (d < minDim) ? minDim : d;

  cout << "dim:" << dim << endl; //debug

  // instanzio i vettori della mappa
  map = vector<vector<Tile>>(dim, vector<Tile>(dim, Tile()));
  
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

vector<vector<Tile>> Map::getMiniMap(int radius) {

  // controllo se ho una grandezza sufficiente a creare una minimappa
  // in caso contrario ritorno tutta la mappa
  
  if (radius*2 > dim) {
    changeRelativePos(pos);
    return map;
  }

  // a questo punto  sono certo che la mappa sia più graande della minimappa
  // quindi posso avere overflow solo su uno dei due lati non su entrambi

  vector<vector<Tile>> miniMap(radius*2, vector<Tile>(radius*2, Tile(false)));

  int overflow_row = 0;
  int overflow_col = 0;


  // calcolo overflow row
  if(pos.row + radius > dim) overflow_row = (pos.row + radius) - dim;
  if(pos.row - radius < 0) overflow_row = pos.row - radius;


  //calcolo overflow col
  if(pos.col + radius > dim) overflow_col = (pos.col + radius) - dim;
  if(pos.col - radius < 0) overflow_col = pos.col - radius;

  for(int row = 0; row < radius*2; row++)
    for(int col = 0; col < radius*2; col++) {
      // clacolo la posizione relativa alla mappa grande
      int map_row = pos.row - radius + row - overflow_row;
      int map_col = pos.col - radius + col - overflow_col;
      miniMap[row][col] = map[ map_row ][ map_col ];

      // trovo la posizione relativa
      if(pos.row == map_row && pos.col == map_col)
        changeRelativePos(Coordinate(row, col));
    }

  return miniMap;
}

void Map::printMap(vector<vector<Tile>> m) const {
  for(int row = 0; row < m.size(); row++){
    for(int col = 0; col < m[row].size(); col++){
      cout << m[row][col].walkable;
    }
    cout << endl;
  }
}

Coordinate Map::RandomPos() const {
  // vettore contenente le /possibili posizioni
  // in cui è possibile spawnare sulla mappa
  vector<Coordinate> possiblePos;

  // trovo tutte le possibili posizioni
  for(int row = 0; row < dim; row++){
    for(int col = 0; col < dim; col++){
      if(map[row][col].walkable == true){
        possiblePos.push_back(Coordinate(row,col));
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
  map[pos.row][pos.col].walkable = true; // debug
  pos = newPos;
  map[pos.row][pos.col].walkable = false; // debug
}

void Map::changeRelativePos(Coordinate newRelativePos) {
  relativePos = newRelativePos;
}
//alessandro merda

void Map::moveUP() {
  Coordinate newPos(pos.row-1, pos.col);
  if(isValid(newPos) && isWalkable(newPos)) changePos(newPos);
}

void Map::moveDOWN() {
  Coordinate newPos(pos.row+1, pos.col);
  if(isValid(newPos) && isWalkable(newPos)) changePos(newPos);
}

void Map::moveLEFT() {
  Coordinate newPos(pos.row, pos.col-1);
  if(isValid(newPos) && isWalkable(newPos)) changePos(newPos);
}

void Map::moveRIGHT() {
  Coordinate newPos(pos.row, pos.col+1);
  if(isValid(newPos) && isWalkable(newPos)) changePos(newPos);
}

// restituisce la tile corrent in modo da poter controllare esternamente cosa contiene
// non è const perche Tile potrebbe essere modificato esternamente e a cascata anche getTileIn() non può essere const
Tile& Map::getCurrentTile() {
  return getTileIn(pos);
}

// richiede una posizione valida
Tile& Map::getTileIn(Coordinate p) {
  return map[p.row][p.col];
}

bool Map::isWalkable(Coordinate p) {
  return getTileIn(p).walkable;
}

bool Map::isValid(Coordinate p) const {
  return (p.row < 0 || p.row >= dim || p.col < 0 || p.col >= dim ) ? false : true;
}