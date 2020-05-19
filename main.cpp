#include <iostream>
#include "item.h"
#include "character.h"
#include "randomizer.h"
#include "map.h"
#include "game.h"
using namespace std;
#include <unistd.h>
#include <ctime>

int main() {

  //parte dediucata a Item
  cout << "TEST DELLE CLASSI ITEM" << endl;

  Character *T = new Player(40, 1000, 200);

  Attribute att1("hello", "20");
  Attribute att2("hello", "21");
  cout << att1 << endl;

  cout << (att1 != att2);
  cout << endl << endl;

  //Item *a = new Item();         // la classe Item non è istanziabile
  Item *b = new Weapon(3, 100);
  Item *c = new Potion(5, 500);
  Item *d = new MagicWeapon(10, 100, 300);
  //Item *e = new MeleeMagic(15, 50, 200);
  Armor *g = new Armor(8, 100);

  cout << endl << endl;

  //a->use();
  b->use(T);
  b->save();
  cout << endl;

  c->use(T);
  c->save();
  cout << endl;

  d->use(T);
  d->save();
  cout << endl;

  //e->use(T);
  //e->save();
  cout << endl;

  cout << "il danno era 300 ma grazie alla tua armatura ricevi " << g->absorb(300) << endl;
  g->save();
  cout << endl;

  Entity *oggettoqualunque;
  oggettoqualunque = c;
  oggettoqualunque->save();
  oggettoqualunque = d;
  oggettoqualunque->save();
  //oggettoqualunque = e;
  //oggettoqualunque->save();
  cout << endl;

  cout << "elimino b" << endl;
  delete b;
  cout << "elimino c" << endl;
  delete c;
  cout << "elimino d" << endl;
  delete d;
  //cout << "elimino e" << endl;
  //delete e;
  cout << "elimino g" << endl;
  delete g;
  cout << "fine" << endl;


  // parte dedicata a character
  cout << endl << endl;
  cout << "TEST DELLE CLASSI CHARACTER" << endl;

  Character *pg = new Player(1,500, 200);
  Character *m = new Mob(2, 300, 100);
  cout << endl;

  pg->info();
  pg->setDamage(100);
  pg->info();
  cout << endl;

  m->info();
  m->setDamage(350);
  m->info();

  // parte dedicata a randomizer
  cout << endl << endl;
  cout << "TEST DELLA CLASSE RANDOMIZER" << endl;

  //cout << Randomizer::

  cout << "seed: " << Randomizer::getSeed() << endl;
  cout << "numero: " << Randomizer::randomNumberBetween(0, 100) << endl;
  Randomizer::setup();
  cout << "seed: " << Randomizer::getSeed() << endl;
  cout << "numero: " << Randomizer::randomNumberBetween(0,100) << endl;

  cout << "seed: " << Randomizer::getSeed() << endl;
  cout << "numero: " << Randomizer::randomNumberBetween(0,100) << endl;


  // parte dedicata a mappa
  cout << endl << endl;
  cout << "TEST DELLE CLASSE MAPPA" << endl;

  Map map = Map();

  //map.printMap();
  cout << endl << endl;

  map.setPos(Coordinate(200, 200));
  cout << "debug" << endl;
  cout << "(" << map.getPos().x << "," << map.getPos().y << ")" << endl;
  map.printMap(map.getSmallMap(5));
  cout << "(" << map.getRelativePos().x << "," << map.getRelativePos().y << ")" << endl;
  //map.printMap();

  return 0;
}
