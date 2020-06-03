#ifndef ENTITY_H
#define ENTITY_H

class Entity {
protected:
  Entity();
  virtual ~Entity(); //=default;
public:
  virtual void save() =0;
};

#endif
