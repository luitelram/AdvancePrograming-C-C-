#ifndef CHARACTER_H
# define CHARACTER_H

# include <stdint.h>
//#include "dungeon.h"
# include "dims.h"

# ifdef __cplusplus
class character {
 public:
  char symbol;
  pair_t position;
  int32_t speed;
  uint32_t alive;
  uint32_t sequence_number;
};

extern "C" {
# else

typedef void character;

#endif

//#include "dungeon.h"
typedef struct dungeon dungeon_t;

typedef enum kill_type {
  kill_direct,
  kill_avenged,
  num_kill_types
} kill_type_t;


  /* Characters use to have a next_turn for the move queue.  Now that it is *
   * an event queue, there's no need for that here.  Instead it's in the    *
   * event.  Similarly, sequence_number was introduced in order to ensure   *
   * that the queue remains stable.  Also no longer necessary here, but in  *
   * this case, we'll keep it, because it provides a bit of interesting     *
   * metadata: locally, how old is this character; and globally, how many   *
   * characters have been created by the game.                              */

int32_t compare_characters_by_next_turn(const void *character1,
                                        const void *character2);
uint32_t can_see(dungeon_t *d, pair_t voyeur, pair_t exhibitionist,int is_pc);
void character_delete(character *c);
int16_t *character_get_pos(character *c);
int8_t get_y(const character *c);
int8_t set_y(character *c, int8_t y);
int8_t get_x(const character *c);
int8_t set_x(character *c, int8_t x);
uint32_t character_get_next_turn(const character *c);
void chara_die(character *c);
int chara_alive(const character *c);
char character_get_symbol(const character *c);
uint32_t get_speed(const character *c);
void chara_nextTurn(character *c);
void chara_resetTurn(character *c);


# ifdef __cplusplus
}
# endif
#endif
