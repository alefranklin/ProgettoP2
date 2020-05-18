#include <vector>
#include "randomizer.cpp"
#include "entity.cpp"
using namespace std;

struct Coordinate {
  int x;
  int y;
  Coordinate(int x=0, int y=0): x(x), y(y) {}
};

struct Tile {
  Entity* e;
  bool walkable;
  Tile(Entity* en = nullptr, bool w = true): e(en), walkable(w){} 
};

class Map {
public:
  Map(int d = minDim) {
    //la mappa deve avere una dimensione minima
    if(dim < d) {
      dim = d;
    }
    cout << "dim:" << dim << endl;

    // instanzio i vettori della mappa
    map = vector<vector<Tile>>(dim, vector<Tile>(dim, Tile()));
    map[1][8] = Tile(nullptr,0);
    // costruisco la mappa
    //  -> creo spazi aperti
    //  -> creo corridoi
    //  -> posiziono oggetti e mob in maniera random

    // aggiorno la posizione iniziale
    changePos(RandomPos());
    

    // aggiorno la visibilità
    updateVisibility();
  }

  // moveUP()
  // moveDOWN()
  void printMap(){
    for(int x = 0; x < dim; x++){
      for(int y = 0; y < dim; y++){
        cout << map[x][y].walkable;
      }
      cout << endl;
    }
  }

//qui giace la funzione pronta

private:
  static int minDim;
  int dim;
  vector<vector<Tile>> map;
  Coordinate pos;

  Coordinate RandomPos() const {
    // vettore contenente le /possibili posizioni
    // in cui è possibile spawnare sulla mappa
    vector<Coordinate> possiblePos;

    // trovo tutte le possibili posizioni
    for(int x = 0; x < dim; x++){
      for(int y = 0; y < dim; y++){
        if(map[x][y].walkable == true){
          possiblePos.push_back(Coordinate(x,y));
          cout << "porocdio" << endl;
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
  void changePos(Coordinate newPos) {
    pos = newPos;
    updateVisibility();
  }

  // aggiorno la visibilità
  /** TODO: il raggio di visione è nel giocatore o nella mappa? **/
  void updateVisibility() {}

  
};

int Map::minDim = 10;
