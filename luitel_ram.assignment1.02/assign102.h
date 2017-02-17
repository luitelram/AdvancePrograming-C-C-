/*
	Iowa State University
	Spring 2017
	ComS 327
	Ram Luitel
*/
#ifndef ASSIGN102_H
# define ASSIGN102_H


#define DUNGEON_WIDTH 160
#define DUNGEON_HEIGHT 105
#define MAX_ROOMS 12


#define ROOM '.'
#define WALL ' '
#define CORRIDOR '#'

struct room {
  int x;
  int y;
  int w;
  int h;
};

struct room rooms[MAX_ROOMS];

int area[DUNGEON_WIDTH][DUNGEON_HEIGHT];
int hardness[DUNGEON_WIDTH][DUNGEON_HEIGHT];


void dungeon_initial(void);
void dungeon_display(void);
int check_tile(int x, int w, int y, int h);
void add_dungeon_room(void);
void draw_corridor(int x1, int y1, int x2, int y2);
void add_corridor(void);
int add_hardness(void);
void dungeon_drwaing();


#endif



