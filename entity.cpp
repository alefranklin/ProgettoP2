#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
using namespace std;

class Entity {
private:
  int id;
protected:
  Entity(int i = 0): id(i) {}
  virtual ~Entity() { cout << "elimino Entity:" << getId() << endl; } //=default;
public:
  int getId() { return id; }
  virtual void save() =0;
};

#endif
