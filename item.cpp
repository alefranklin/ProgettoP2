#include "item.h"
#include <iostream>
#include <vector>
#include <string>
#include "character.h"
using namespace std;

ostream& operator<<(ostream& out, const Attribute &a) {
  out << a.name + ": " + a.val;
  return out;
}

Item::Item(int i): Entity(i) { cout << "istanzio Item: " << getId() << endl; }
Item::~Item() { cout << "elimino Item:" << getId() << endl; }
void Item::use(Character *pg, vector<Character*> *enemies) { cout << "sto usando item " << getId() << endl; }
//questo metodo viene usato per ritornare tutti gli attributi di un oggetto
//per poterli stampare nella lista nella gui
 //vector<Attribute<T>> getAttributes() =0;

Potion::Potion(int id, int e): Item(id), effect(e) {} 
Potion::~Potion() { cout << "elimino Potion: " << getId() << endl; }
void Potion::use() { cout << "sto usando Potion " << getId() << " ripristina " << effect << " salute" << endl; } 
void Potion::save() { cout << "salvo Potion " << getId() << endl; }
/* vector<Attribute<T>> getAttributes() {
   vector<Attribute<T>> att;
   att.push_back(Attribute("effect", &effect));
   return att;
 }*/


Weapon::Weapon(int id, int d): Item(id), damage(d) {} 
Weapon::~Weapon() { cout << "elimino Weapon:" << getId() << endl; }
int Weapon::getDamage() { return damage; } 
void Weapon::use() { cout << "sto usando Weapon " << getId() << " infliggi " << damage << " danno" << endl; }
void Weapon::save() { cout << "salvo Weapon " << getId() << endl; }
//vector<Attribute<T>> Weapon::getAttributes() {}

Magic::Magic(int id, int e): Item(id), effect(e) {} 
Magic::~Magic() { cout << "elimino Magic:" << getId() << endl; }
int Magic::getEffect() { return effect; } 
void Magic::use() { cout << "sto usando Magic " << getId() << " subisci " << effect << " danno" << endl; }
void Magic::save() { cout << "salvo Magic " << getId() << endl; }
//vector<Attribute<T>> Magic::getAttributes() {}


/*Melee::Melee(int id, int d): Weapon(id, d) {} 
Melee::~Melee() { cout << "elimino Melee:" << getId() << endl; } 
void Melee::use() { cout << "sto usando Weapon Melee " << getId() << " infliggi " << getDamage() << " danno" << endl; }
void Melee::save() { cout << "salvo Weapon Melee" << getId() << endl; }
//vector<Attribute<T>> Melee::getAttributes() {}

MeleeMagic::MeleeMagic(int id, int d, int e): Melee(id, d), Magic(id, e), Item(id) {} 
MeleeMagic::~MeleeMagic() { cout << "elimino MeleeMagic:" << getId() << endl; } 
void MeleeMagic::use() { cout << "grazie alla tua arma melee magica infliggi " << getDamage() << " danno fisico e " << getEffect() << " danno magico" << endl; } 
void MeleeMagic::save() { cout << "salvo MeleeMagic " << getId() << endl; }
//vector<Attribute<T>> MeleeMagic::getAttributes() {}
*/


MagicWeapon::MagicWeapon(int id, int d, int e): Weapon(id, d), Magic(id, e), Item(id) {} 
MagicWeapon::~MagicWeapon() { cout << "elimino MagicWeapon:" << getId() << endl; } 
void MagicWeapon::use() { cout << "grazie alla tua arma magica infliggi un danno doppio!" << endl; Weapon::use(); Magic::use(); } 
void MagicWeapon::save() { cout << "salvo MagicWeapon " << getId() << endl; }
//vector<Attribute<T>> MagicWeapon::getAttributes() {}

Armor::Armor(int id, int a): Item(id), armatura(a) {} 
Armor::~Armor() { cout << "elimino Armor:" << getId() << endl; }
int Armor::absorb(int danno) { return (armatura > danno) ? 0 : danno-armatura; } 
void Armor::use() { } 
void Armor::save() { cout << "salvo Armor " << getId() << endl; }
//vector<Attribute<T>> Armor::getAttributes() {}
