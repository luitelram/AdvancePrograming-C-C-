#ifndef CHARACTER_H
# define CHARACTER_H

#include "binheap.h"
#include "assign104.h"
#include "math.h"

#define SEEN 15
typedef struct dungeon dungeon_t;

typedef struct character{
	char symbol;
	int survive;
	int fromx;
	int fromy;
	int toX;
	int toY;
	int isPC;
	int nextmove;
	int speed;
	int sequence;
	int intell;
	int tele;
	int tunnel;
	int erra;
}character_t;

character_t genMCharacter(int type, dungeon_t *d);
character_t genPCCharacter(dungeon_t *d);
void placeCharacter(character_t *c, dungeon_t *d);
void nextTurn(character_t *c);
void nextPos(character_t *c, dungeon_t *d);
void updatePos(character_t *c);
int checkSeen(int pcX,int pcY, int npcX, int npcY);
#endif
