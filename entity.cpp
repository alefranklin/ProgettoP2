#include <iostream>
#include "entity.h"
using namespace std;


Entity::Entity(int i): id(i) {}
Entity::~Entity() { cout << "elimino Entity:" << getId() << endl; } //=default;
int Entity::getId() { return id; }

