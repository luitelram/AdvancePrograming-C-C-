#ifndef OBJECT_H
# define OBJECT_H

#include <string>
#include <stdint.h>
#include"heap.h"
#include"dims.h"
#include"character.h"
#include"descriptions.h"
#include"dice.h"


class object {
 public:
  const char* name;
  const char* description;
  char  symbol;
  object_type_t type;
  uint32_t color;
  pair_t position;
  dice damage;
  int32_t weight,speed,attribute,value,hit,dodge,defence;
  bool seen;
};

void gen_objects(dungeon_t *d);
void destroy_objects(dungeon_t *d);


#endif

