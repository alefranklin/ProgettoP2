#ifndef ENTITY_H
#define ENTITY_H

class Entity {
private:
  int id;
protected:
  Entity(int i = 0);
  virtual ~Entity(); //=default;
public:
  int getId();
  virtual void save() =0;
};

#endif
