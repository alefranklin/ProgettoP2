#ifndef ITEM_H
#define ITEM_H

#include "entity.h"
#include <iostream>
#include <vector>
#include <string>
#include "character.h"
using namespace std;

class Character;

// struct degli attributi di un oggetto e ridefinizione operator<< e ==
struct Attribute {
  string name;
  string val;
  Attribute(string s, string v): name(s), val(v) {}
  friend ostream& operator<<(ostream& out, const Attribute &a);

  //se dovessero servire
  bool operator==(const Attribute &a) {
    return ( name==a.name && val==a.val);
  }
  bool operator!=(const Attribute &a) {
    return !(*this == a);
  }
};

class Item: public Entity {
private:
  string nome;
protected:
  Item(int i = 0);
public:
  virtual ~Item();
  virtual void use(Character *pg, vector<Character*> *enemies = nullptr);
  virtual void save() = 0;
  //questo metodo viene usato per ritornare tutti gli attributi di un oggetto
  //per poterli stampare nella lista nella gui
  //virtual vector<Attribute<T>> getAttributes() =0;
};


class Potion: public Item {
private:
 int effect;
public:
 Potion(int id, int e);
 virtual ~Potion();
 virtual void use();
 virtual void save();
 /*
 virtual vector<Attribute<T>> getAttributes() {
   vector<Attribute<T>> att;
   att.push_back(Attribute("effect", &effect));
   return att;
 }*/
};


class Weapon: virtual public Item {
private:
  int damage;
public:
  Weapon(int id, int d);
  virtual ~Weapon();
  int getDamage();
  virtual void use();
  virtual void save();
  //virtual vector<Attribute<T>> getAttributes() {}
};


class Magic: virtual public Item {
private:
  int effect;
public:
  Magic(int id, int e);
  virtual ~Magic();
  int getEffect();
  virtual void use();
  virtual void save();
  //virtual vector<Attribute<T>> getAttributes() {}
};

/*class Melee: public Weapon {
public:
  Melee(int id, int d);
  virtual ~Melee();
  virtual void use();
  virtual void save();
  //virtual vector<Attribute<T>> getAttributes() {}

};

class MeleeMagic: public Melee, public Magic {
public:
  MeleeMagic(int id, int d, int e);
  virtual ~MeleeMagic();
  virtual void use();
  virtual void save();
  //virtual vector<Attribute<T>> getAttributes() {}
};*/


class MagicWeapon: public Weapon, public Magic {
public:
  MagicWeapon(int id, int d, int e);
  virtual ~MagicWeapon();
  virtual void use();
  virtual void save();
  //virtual vector<Attribute<T>> getAttributes() {}
};

class Armor: public Item {
private:
 int armatura;
public:
 Armor(int id, int a);
 virtual ~Armor();
 int absorb(int danno);
 virtual void use();
 virtual void save();
 //virtual vector<Attribute<T>> getAttributes() {}
};

#endif
