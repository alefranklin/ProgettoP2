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

Sword::Sword(int id, int d, int r) : Weapon(id, d), range(r), Item(id) {}
int Sword::getRange() { return range; }
void Sword::use() { cout << "sto usando SPADA " << endl;}


Bow::Bow(int id, int d, int a) : Weapon(id, d), arrows(a), Item(id) {}
int Bow::getArrow() { return arrows; }
void Bow::use() { cout << "sto usando ARCO " << endl;}



Magic::Magic(int id, int e, int m): Item(id), effect(e), mana(m) {} 
Magic::~Magic() { cout << "elimino Magic:" << getId() << endl; }
int Magic::getEffect() { return effect; }
int Magic::getMana() { return mana; }
//void Magic::use() { cout << "sto usando Magic " << getId() << " subisci " << effect << " danno" << endl; }
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


MagicWeapon::MagicWeapon(int id, int d, int e, int m): Weapon(id, d), Magic(id, e, m), Item(id) {} 
MagicWeapon::~MagicWeapon() { cout << "elimino MagicWeapon:" << getId() << endl; } 
void MagicWeapon::use() { 
  cout << "Arma magica" << endl; 
  if(100 >= Magic::getMana()){ //**** AGGGIORNARE CON manaPG
    //settare nuovo mana disponibile nel personaggio
    Weapon::use();
    cout << " + infliggi " << Weapon::getDamage()*Magic::getEffect() << " danno magico" << endl;
  } 
} 
//void MagicWeapon::useMana() { cout << " Uso " << Magic::getMana() << " mana" << endl; }
void MagicWeapon::save() { cout << "salvo MagicWeapon " << getId() << endl; }
//vector<Attribute<T>> MagicWeapon::getAttributes() {}

Armor::Armor(int id, int a): Item(id), armatura(a) {} 
Armor::~Armor() { cout << "elimino Armor:" << getId() << endl; }
int Armor::absorb(int danno) { return (armatura > danno) ? 0 : danno-armatura; } 
//void Armor::use() { } 
void Armor::save() { cout << "salvo Armor " << getId() << endl; }
//vector<Attribute<T>> Armor::getAttributes() {}


Chest::Chest(int id, int c): Armor(id, c), Item(id) {}
Chest::~Chest() { cout << "Elimino CHEST ARMOR: " << getId() << endl; }
void Chest::save() { cout << "salvo CHEST " << getId() << endl; }

Boots::Boots(int id, int a): Armor(id, a), Item(id) {}
Boots::~Boots() { cout << "Te buto via e scarpe " << getId() << endl; }
void Boots::save() { cout << "salvo BOOTS " << getId() << endl; }