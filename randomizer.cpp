#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include "test_item.cpp"
#include "test_character.cpp"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
using namespace std;

struct ScrapedInfo {
  string name;
  int lvl;
  string file;
  ScrapedInfo(string n, int l, string f): name(n), lvl(l), file(f) {}
};


/**
 * classe statica per ottenere valori oppure oggetti random
 * avendo tutti i metodi statici è possibile utilizzarla senza bisogno di istanziare un oggetto
 */
class Randomizer {
private:
  static unsigned int seed;

  //static vettore da definire constructVectorSword()
  //static vettore da definire constructVectorBow()
  //ecc
public:
  // queste 3 funzioni permettono di avere il controllo sulla generazione dei numeri casuali
  static unsigned int setup() {
    setSeed(time(NULL));
    return getSeed();
  }  //funzione pronta

  static unsigned int getSeed() { return seed; }  //funzione pronta
  static void setSeed(unsigned int s) { seed = s; srand(s); } //funzione pronta


  static int randomNumberBetween(int min = 0, int max = 1) { 
    setup();
    return min+(rand()%(max-min+1));
    } //fatta a cazzo da definire

  static Item* getRandomItem(int livello) {/*chiamare casualmente o randomWeapon o randonArmor o potion o altri item istanziabili*/}

  static Weapon* getRandomWeapon(int livello) {/*chiamare casualmente uno dei metodi sotto*/}
  //static Weapon* getRandomSword(int livello);
  //static Weapon* getRandomBow(int livello);
  //ecc ecc per ogni arma

  static Item* getRandomPotion(int livello);

  //static Armor* getRandomArmor(int livello);

  static Character* getRandomMob(int livello);

  static string getRandomMobName();
  static string getrandomNpcName();
};

unsigned int Randomizer::seed = 1; //valore di default di srand

#endif
