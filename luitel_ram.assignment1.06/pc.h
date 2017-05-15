#ifndef PC_H
# define PC_H

# include <stdint.h>

# include "character.h"
# include "dungeon.h"
# include "dims.h"

# ifdef __cplusplus
class pc : 
public character {
 public:
  terrain_type_t known_terrain[DUNGEON_Y][DUNGEON_X];
  unsigned char visible[DUNGEON_Y][DUNGEON_X];
};

extern "C" {
# else
typedef void pc;

# endif

typedef struct dungeon dungeon_t;

#include "dungeon.h"

 //void pc_delete(pc_t *pc);
uint32_t pc_is_alive(dungeon_t *d);    
void config_pc(dungeon_t *d);
uint32_t pc_next_pos(dungeon_t *d, pair_t dir);
void place_pc(dungeon_t *d);
uint32_t pc_in_room(dungeon_t *d, uint32_t room);
void pc_learn_terrain(pc *p, pair_t pos, terrain_type_t ter);
terrain_type_t pc_learned_terrain(pc *p, int8_t y, int8_t x);

//void pc_learned_terrain(pc *p, int8_t y, int8_t x);
void pc_inititial_terrain(pc *p);
void notice_pc_terrain(pc *p, dungeon_t *d);
int32_t pc_is_illuminated(pc *p, int8_t y, int8_t x);
void reset_pc_visibility(pc *p);

# ifdef __cplusplus
}
# endif
#endif
