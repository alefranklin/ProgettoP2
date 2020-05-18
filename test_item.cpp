#ifndef ITEM_H
#define ITEM_H

#include "test_entity.cpp"
#include <iostream>
#include <vector>
#include <string>
#include "test_character.cpp"
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
ostream& operator<<(ostream& out, const Attribute &a) {
  out << a.name + ": " + a.val;
  return out;
}


class Item: public Entity {
protected:
  string nome;

  Item(int i = 0): Entity(i) { cout << "istanzio Item: " << getId() << endl; }
public:
  virtual ~Item() { cout << "elimino Item:" << getId() << endl; }
  virtual void use(Character *pg, vector<Character*> *enemies = nullptr) { cout << "sto usando item " << getId() << endl; }
  virtual void save() =0;
  //questo metodo viene usato per ritornare tutti gli attributi di un oggetto
  //per poterli stampare nella lista nella gui
  //virtual vector<Attribute<T>> getAttributes() =0;
};


class Potion: public Item {
private:
 int effect;
public:
 Potion(int id, int e): Item(id), effect(e) {}
 virtual ~Potion() { cout << "elimino Potion: " << getId() << endl; }
 virtual void use() { cout << "sto usando Potion " << getId() << " ripristina " << effect << " salute" << endl; }
 virtual void save() { cout << "salvo Potion " << getId() << endl; }
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
  Weapon(int id, int d): Item(id), damage(d) {}
  virtual ~Weapon() { cout << "elimino Weapon:" << getId() << endl; }
  int getDamage() { return damage; }
  virtual void use() { cout << "sto usando Weapon " << getId() << " infliggi " << damage << " danno" << endl; }
  virtual void save() { cout << "salvo Weapon " << getId() << endl; }
  //virtual vector<Attribute<T>> getAttributes() {}
};


class Magic: virtual public Item {
private:
  int effect;
public:
  Magic(int id, int e): Item(id), effect(e) {}
  virtual ~Magic() { cout << "elimino Magic:" << getId() << endl; }
  int getEffect() { return effect; }
  virtual void use() { cout << "sto usando Magic " << getId() << " subisci " << effect << " danno" << endl; }
  virtual void save() { cout << "salvo Magic " << getId() << endl; }
  //virtual vector<Attribute<T>> getAttributes() {}
};

class Melee: public Weapon {
public:
  Melee(int id, int d): Weapon(id, d) {}
  virtual ~Melee() { cout << "elimino Melee:" << getId() << endl; }
  virtual void use() { cout << "sto usando Weapon Melee " << getId() << " infliggi " << getDamage() << " danno" << endl; }
  virtual void save() { cout << "salvo Weapon Melee" << getId() << endl; }
  //virtual vector<Attribute<T>> getAttributes() {}

};

class MeleeMagic: public Melee, public Magic {
public:
  MeleeMagic(int id, int d, int e): Melee(id, d), Magic(id, e), Item(id) {}
  virtual ~MeleeMagic() { cout << "elimino MeleeMagic:" << getId() << endl; }
  virtual void use() { cout << "grazie alla tua arma melee magica infliggi " << getDamage() << " danno fisico e " << getEffect() << " danno magico" << endl; }
  virtual void save() { cout << "salvo MeleeMagic " << getId() << endl; }
  //virtual vector<Attribute<T>> getAttributes() {}
};


class MagicWeapon: public Weapon, public Magic {
public:
  MagicWeapon(int id, int d, int e): Weapon(id, d), Magic(id, e), Item(id) {}
  virtual ~MagicWeapon() { cout << "elimino MagicWeapon:" << getId() << endl; }
  virtual void use() { cout << "grazie alla tua arma magica infliggi un danno doppio!" << endl; Weapon::use(); Magic::use(); }
  virtual void save() { cout << "salvo MagicWeapon " << getId() << endl; }
  //virtual vector<Attribute<T>> getAttributes() {}
};

class Armor: public Item {
private:
 int armatura;
public:
 Armor(int id, int a): Item(id), armatura(a) {}
 virtual ~Armor() { cout << "elimino Armor:" << getId() << endl; }
 int absorb(int danno) { return (armatura > danno) ? 0 : danno-armatura; }
 virtual void use() { }
 virtual void save() { cout << "salvo Armor " << getId() << endl; }
 //virtual vector<Attribute<T>> getAttributes() {}
};

#endif
