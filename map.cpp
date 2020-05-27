#include "map.h"
#include "randomizer.h"
#include <cmath>
#include <set>

#include "colors.h"

using namespace std;

int Map::minDim = 80;

ostream& operator<<(ostream& out, const Coordinate &c) {
  out << "(" << c.row << "," << c.col << ")";
  return out;
}


Map::Map(int d): pos() {
  //la mappa deve avere una dimensione minima
  dim = (d < minDim) ? minDim : d;

  cout << "dim:" << dim << endl; //debug

  // instanzio i vettori della mappa
  map = vector<vector<Tile>>(dim, vector<Tile>(dim, Tile()));

  Generatemap();
  
  // costruisco la mappa
  //  -> creo spazi aperti
  //  -> creo corridoi
  //  -> posiziono oggetti e mob in maniera random

  // aggiorno la posizione iniziale
  changePos(RandomPos());

}

// ritorna true se la posizione è stata settata
// fasle altrimenti 
bool Map::setPos(Coordinate newPos) {
  //if(isWalkable(newPos)) {
    changePos(newPos);
    return true;
  //} else return false;

  // TODO decommentare quando finito il dev // debug
}

Coordinate Map::getPos() const {
  return pos;
}

Coordinate Map::getRelativePos() const {
  return relativePos;
}

vector<vector<Tile>> Map::getMiniMap(int size) {

  // controllo se ho una grandezza sufficiente a creare una minimappa
  // in caso contrario ritorno tutta la mappa
  
  if (size >= dim) {
    changeRelativePos(pos);
    return map;
  }

  // a questo punto  sono certo che la mappa sia più grande della minimappa
  // quindi posso avere overflow solo su uno dei due lati non su entrambi

  vector<vector<Tile>> miniMap(size, vector<Tile>(size, Tile(false)));

  int overflow_row = 0;
  int overflow_col = 0;
  int half_size = size/2; 


  // calcolo overflow row
  if(pos.row + half_size > dim-1) overflow_row = (pos.row + half_size) - (dim-1);
  if(pos.row - half_size < 0) overflow_row = pos.row - half_size;


  //calcolo overflow col
  if(pos.col + half_size > dim-1) overflow_col = (pos.col + half_size) - (dim-1);
  if(pos.col - half_size < 0) overflow_col = pos.col - half_size;

  for(int row = 0; row < size; row++)
    for(int col = 0; col < size; col++) {
      // clacolo la posizione relativa alla mappa grande
      int map_row = pos.row - half_size + row - overflow_row; /*size=11 h_size=5 ov_row=1 ov_col=1 map_row=79 map_col=79*/
      int map_col = pos.col - half_size + col - overflow_col;

      miniMap[row][col] = map[ map_row ][ map_col ];

      // trovo la posizione relativa
      if(pos.row == map_row && pos.col == map_col)
        changeRelativePos(Coordinate(row, col));
    }

  return miniMap;
} // funzione pronta

void Map::printMap(vector<vector<Tile>> m, Coordinate pos) {
  for(int row = 0; row < m.size(); row++){
    for(int col = 0; col < m[row].size(); col++){
      if(row == pos.row && col == pos.col) cout << BLUE << "P" << RESET;
      else if(m[row][col].biome != Null) {
        switch (m[row][col].biome)
        {
        case Valley:    cout << GREEN << "\"" << RESET;     break;
        case Desert:    cout << YELLOW << "~" << RESET;     break;
        case Doungeon:  cout << BOLDBLACK << "x" << RESET;  break;
        case Street:    cout << WHITE << "=" <<  RESET;     break;
        case Water:     cout << CYAN << "~" << RESET;       break;
        default:        cout << "N";                        break;
        }
      } else cout << BLACK << "=" << RESET;
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
  pos = newPos;
}

void Map::changeRelativePos(Coordinate newRelativePos) {
  relativePos = newRelativePos;
}
//alessandro merda

// nelle funzioni move isValid() è ridondante in quanto utilizzata anche in isWalkable(),
// per chiarezza l'abbiamo utilizzata lo stesso nel controllo

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
  return (isValid(p)) ? getTileIn(p).walkable : false;
}

bool Map::isValid(Coordinate p) const {
  return (p.row < 0 || p.row >= dim || p.col < 0 || p.col >= dim ) ? false : true;
}

vector<Coordinate> Map::createCircle(Coordinate center, int radius) {
  /* controllo tutte le posizioni in una regione grande radius^2 x radius^2 con centro in center
     e controllo se fanno parte dell'area utilizzando la formula del cerchio */
  vector<Coordinate> points;
  
  // il raggio deve essere >= 0
  radius = (radius < 0) ? radius*(-1) : radius;

  // itero nell'area da controllare
  for(int i = center.row - radius; i <= center.row + radius; i++) {
    for(int j = center.col - radius; j <= center.col + radius; j++) {
      
      // utilizzo l'equazione del cerchio
      if((i-center.row)*(i-center.row) + (j-center.col)*(j-center.col) <= radius*radius) {
        // se valida aggiungo la posizione alla lista dei punti selezionati
        Coordinate p(i,j);
        if(isValid(p)) points.push_back(p);
      }

    }
  }
  return points;
}

vector<Coordinate> Map::createRectangle(Coordinate center, int width, int height) {
  vector<Coordinate> points;

  // itero nell'area da controllare
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {

      int row = center.row - (height/2) + i;
      int col = center.col - (width/2) + j;
      
      // se valida aggiongo la posizione alla lista di punti selezionati
      Coordinate p(row,col);
      if(isValid(p)) points.push_back(p);
    }
  }
  return points;
}

vector<Coordinate> Map::createLine(Coordinate p1, Coordinate p2, int thickness) {
  vector<Coordinate> line;

  // variabili equazione retta
  int A = p2.col - p1.col; 
  int B = p1.row - p2.row; 
  int C = A*(p1.row) + B*(p1.col);

  cout << "r min: " << min(p1.row, p2.row) << " r max: " << max(p1.row, p2.row) << endl;
  cout << "c min: " << min(p1.col, p2.col) << " c max: " << max(p1.col, p2.col) << endl;

  for(int r = min(p1.row, p2.row); r <= max(p1.row, p2.row); r++) {
    for(int c = min(p1.col, p2.col); c <= max(p1.col, p2.col); c++) {

      if( (A*r) + (B*c) == C ) {
          Coordinate p(r,c);
          if(isValid(p)) line.push_back(p);
      }

      // forse non serve
      /*
      if(B<0) {
        // l'equazione è AxBy=C
        if( (A*r) + (B*c) == C ) {
          Coordinate p(r,c);
          if(isValid(p)) points.push_back(p);
        }
      } else {
        //l'equazione è Ax+By=C
        if( (A*r) * (B*c) == C ) {
          Coordinate p(r,c);
          if(isValid(p)) points.push_back(p);
        }
      } */


    }
  }

  // thickness deve essere >= 1
  if(thickness <= 0) thickness = 1;

  // se la linea è obliqua per potermi muovere devo avere uno spessore almeno di 2
  if ( ((p1.row != p2.row) or (p1.col != p2.col)) && thickness == 1) thickness = 1;

  // se thickness è 1 allora non devo fare altro
  if(thickness == 1) return line; 

  // se tickness è > 1 ingrosso la linea
  vector<Coordinate> points;
  for(auto it = line.begin(); it != line.end(); ++it) {
    // creo un quadrato di dimensione thicknessxthickness intorno ad ogni punto della linea
    vector<Coordinate> v = createRectangle(*it, thickness, thickness);
    points.insert(points.end(), v.begin(), v.end());
  }

  // elimino tutti i punti duplicati
  set<Coordinate> s( points.begin(), points.end() );
  points.assign( s.begin(), s.end() );

  return points;
      
}

void Map::modifyTile(vector<Coordinate> points, bool w, Biome b, bool overwrite) {
  for(auto it = points.begin(); it != points.end(); ++it) {
    if(isValid(*it)) {
      Tile &t = getTileIn(*it);
      // sovrawscrivo sempre se overWrite a true
      // altrimenti solo se il bioma è Null
      if(overwrite || t.biome == Null) {
        t.walkable = w;
        t.biome = b;
      }
    }
  }
}

/* calcolo la percentuale di spawn in base al Bioma */
float Map::calcSpawnRate(const Tile& t) const {
  //se non ci posso andare laprobabilità di spawn è 0
  if(t.walkable == false) return 0.0;

  float rate = 0.1;
  switch (t.biome)
  {
    case Valley:    rate = 0.1;  break;
    case Desert:    rate = 0.2;  break;
    case Doungeon:  rate = 0.4;  break;
    case Street:    rate = 0.05; break;
    default:        rate = 0.1;  break;
  }
  return rate;
}

void Map::generateOasi(Coordinate center, int minDim, int maxDim, bool overwrite) {
  vector<Coordinate> oasi;
  
  // scelgo la forma
  if( Randomizer::randomNumberBetween(0,100) <= 50 ) {

    int radius = Randomizer::randomNumberBetween(minDim/2, maxDim/2);
    oasi = createCircle(center, radius);
  
  } else {
    
    int w = Randomizer::randomNumberBetween(minDim, maxDim);
    int h = Randomizer::randomNumberBetween(minDim, maxDim);
    oasi = createRectangle(center, w, h);
  
  }
  // aggiungo l'oasi 
  modifyTile(oasi, true, Valley, overwrite);

  // aggiungo l'acqua
  modifyTile(vector<Coordinate>(1, center), true, Water, overwrite);
}

void Map::generateDesert(Coordinate center, int minDim, int maxDim, int maxOasis, bool overwrite) {
  vector<Coordinate> desert;
  bool oasis = true;
  // scelgo la forma
  if( Randomizer::randomNumberBetween(0,100) <= 50 ) {

    int radius = Randomizer::randomNumberBetween(minDim, maxDim);
    desert = createCircle(center, radius);
    if(radius <= 10 ) oasis = false;
  
  } else {
    
    int w = Randomizer::randomNumberBetween(minDim, maxDim);
    int h = Randomizer::randomNumberBetween(minDim, maxDim);
    desert = createRectangle(center, w, h);
    if(w*h <= 30) oasis = false;
  
  }
  // aggiungo il deserto  
  modifyTile(desert, true, Desert, overwrite);

  if(oasis) {
    // aggiungo le oasi
    for(int i = 0; i < Randomizer::randomNumberBetween(0, maxOasis); i++) {
      Coordinate oasi = desert[ Randomizer::randomNumberBetween(0, desert.size()-1) ];
      generateOasi(oasi, 4, 12, true);
    }
  }
}

void Map::Generatemap() {

  vector<Coordinate> centers;

  Coordinate center = Coordinate(40, 40); //TODO implementare GetRandomNullPos()
  centers.push_back(center);

  generateDesert(center, 20, 80, 4, true);


  /**
   * chiama combinazioni casuali di forme geometriche intercconnesse da linee
   * che si differenziano per biomi
   * le linee sono le strade
   * 
   * si possono fare vallate
   * 
   * deserti giganti con oasi in mezzo
   * 
   * magari prevedere un modo di generare acqua o lava rendendo decidibile anche il walkable oltre al bioma
   */
}