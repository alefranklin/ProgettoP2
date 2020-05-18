#include <vector>
#include "randomizer.cpp"
using namespace std;

struct Coordinate {
  int x;
  int y;
  Coordinate(int x=0, int y=0): x(x), y(y) {}
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
    map = vector<vector<char>>(dim, vector<char>(dim, '#'));
    visible = vector<vector<bool>>(dim, vector<bool>(dim, false));

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
        cout << map[x][y];
      }
      cout << endl;
    }
  }

  void pushTo(Coordinate cor){
    if(cor.x < dim && cor.y < dim){     //controllo se le coordinate sono entro i limiti
      bool trovato = false;             
      int x = 0, y = 0;                     
      for(auto i = map.begin(); i != map.end() && !trovato; ++i){     //iteratore
        if(y == cor.y){
          for(auto j = i->begin(); j != i->end() && !trovato; ++j){
            if (x == cor.x){
              i->insert(j,'@');
              trovato == true;
            }
            x++;
          }
        }
        y++;
      }
    } else {
      cout << "**push coords out of bounds**" << endl;
    }
  }   //funzione pronta

private:
  static int minDim;
  int dim;
  vector<vector<char>> map;
  vector<vector<bool>> visible;
  Coordinate pos;

  Coordinate RandomPos() const {
    // vettore contenente le /possibili posizioni
    // in cui è possibile spawnare sulla mappa
    vector<Coordinate> possiblePos;

    // trovo tutte le possibili posizioni
    for(int x = 0; x < dim; x++){
      for(int y = 0; y < dim; y++){
        if(map[x][y] == '#'){
          possiblePos.push_back(Coordinate(x,y));
        }
      }
    }
    // ne scelgo una a caso
    int selected = Randomizer::randomNumberBetween(0, possiblePos.size()-1);
    return possiblePos[selected];
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
