/*
	Iowa State University
	Spring 2017
	ComS 327
	Ram Luitel
*/

#include <stdio.h>
#include <stdint.h> 
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>  
#include <time.h>  
#include <math.h>  
#include <unistd.h>  
#include <string.h> 
#include <endian.h> 

#include"assign102.h"


/* Main function  */
int main(int argc, char *argv[])
{
 
  srand(time(NULL));

  int dungeon_load = 0;
  int dungeon_save = 0;
  int i;

  char l[] = "--load";
  char s[] = "--save";
  char dpath[] = "/.rlg327/dungeon";
  
  char *fpath = getenv("HOME");
  char *fullpath = strcat(fpath, dpath);
  char semantic[12];
  int ver;
  int size;
  int si; 
  uint8_t field[DUNGEON_WIDTH][DUNGEON_HEIGHT];
  struct room toAdd[100];
  
  for(i = 0; i< argc; i++) {
    if(strcmp(argv[i], l) == 0) {
      dungeon_load = 1;
    }
    if(strcmp(argv[i], s) == 0) {
      dungeon_save = 1;
    }
  }

  if(dungeon_load) {
    
    FILE *f;
    f = fopen(fullpath, "r");

    fread(&semantic, 12, 1, f);
    fread(&ver , 4, 1, f);
    fread(&size    , 4, 1, f);
    size = (int) htobe32(size);
    int x,y;
    for (y = 0; y < DUNGEON_HEIGHT; y++ ) {
      for (x = 0; x < DUNGEON_WIDTH; x++ ) {
    	fread(&field[x][y], 1, 1, f);
      }
    }

    si = (size - 16820) / 4;
    uint32_t val;
    for(x = 0; x < si; x++) {
      struct room rom;
      fread(&val, 1, 1, f);
      rom.x = (int) val;
      fread(&val, 1, 1, f);
      rom.w = (int) val;
      fread(&val, 1, 1, f);
      rom.y = (int) val;
      fread(&val, 1, 1, f);
      rom.h = (int) val;
      toAdd[x] = rom;
    }

    dungeon_initial();
    for (y = 0; y < DUNGEON_HEIGHT; y++ ) {
      for (x = 0; x < DUNGEON_WIDTH; x++ ) {
	if(field[x][y] == 0) {
	  area[x][y] = CORRIDOR;
	}
      }
    }

    for(i = 0; i < si; i++) {
      for(x = toAdd[i].x; x < toAdd[i].x + toAdd[i].w; x++) {
	for(y = toAdd[i].y; y < toAdd[i].y + toAdd[i].h; y++) {
	  area[x][y] = ROOM;
	}
      }
    }
    dungeon_display();
    printf("%s\n", semantic);
    printf("%d\n", ver);
    printf("%d\n", size);
    for (x = 0; x < DUNGEON_WIDTH; x++) {
      for(y = 0; y < DUNGEON_HEIGHT; y++) {
	hardness[x][y] = field[x][y];
      }
    }
    fclose(f);
  }
  else {
    dungeon_drwaing();
  }
  if (dungeon_save) {
    int siz;
    if(dungeon_load) {
      siz = size;
    }
    else {
      siz = 16820 + 48;
      si = 12;
    } 
    char se[] = "RLG327-S2017";
    int ve = 0;

    FILE *f;
    f = fopen(fullpath, "w");
    fwrite(&se, 1, 12, f);
    fwrite(&ve, 4, 1, f);
    uint32_t siz2 = be32toh(siz);
    fwrite(&siz2, 4, 1, f);
    uint8_t temp;
    int i,j;
    for(i = 0; i < DUNGEON_HEIGHT; i++) {
      for(j = 0; j < DUNGEON_WIDTH; j++) {
	temp = hardness[j][i];
	fwrite(&temp, 1, 1, f);
      }
    }

    if(dungeon_load) {
      uint8_t x, w, y, h;
      for(i = 0; i < si; i++) {
	x = toAdd[i].x;
	w = toAdd[i].w;
	y = toAdd[i].y;
	h = toAdd[i].h;
	fwrite(&x, 1, 1, f);
	fwrite(&w, 1, 1, f);
	fwrite(&y, 1, 1, f);
	fwrite(&h, 1, 1, f);
      }
    }
    else {
      uint8_t x, w, y, h;
      for(i = 0; i < si; i++) {
	x = (uint8_t) rooms[i].x;
	w = (uint8_t) rooms[i].w + 1;
	y = (uint8_t) rooms[i].y;
	h = (uint8_t) rooms[i].h + 1;
	fwrite(&x, 1, 1, f);
	fwrite(&w, 1, 1, f);
	fwrite(&y, 1, 1, f);
	fwrite(&h, 1, 1, f);
      }
    }
    fclose(f);

  }
  return 0;
}



void dungeon_initial(void)
{
  int x,y;
  for(y = 0; y < DUNGEON_HEIGHT; y++ ) {
    for (x = 0; x < DUNGEON_WIDTH; x++) {
      area[x][y] = WALL;
    }
  }
}

void dungeon_display(void){
  int x,y;
  for (y = 0; y < DUNGEON_HEIGHT; y++ ) {
    for (x = 0; x < DUNGEON_WIDTH; x++ ) {
      printf("%c", area[x][y]);
    }
    printf("\n");
  }
}

int check_tile(int x, int w, int y, int h) {
  int i,j;
  for (i = x; i <= x + w; i++) {
    for (j = y; j <= y + h; j++) {
      if (area[i][j] != WALL) {
	return 1;
      }
    }
  }
  return 0;
}

void add_dungeon_room(void){
  int n = 0;
  while (n < MAX_ROOMS) {
    int x=0, y=0, w=0, h=0;
    struct room addRoom;
    
    while (w < 7) {
      w = rand() % 18;
    }
    while (h < 5) {
      h = rand() % 15;
    }
    
    while (x == 0 || y == 0) {
      x = rand() % (DUNGEON_WIDTH - w -1);
      y = rand() % (DUNGEON_HEIGHT - h -1);
    }
    
    if (check_tile(x - 1, x + w + 1, y - 1, y + h + 1)){
      
    }
    else {
      int i, j;
      for (i = x; i <= w + x; i++) {
	for (j = y; j <= h + y; j++) {
	  area[i][j] = ROOM;
	}
      }
      addRoom.x = x;
      addRoom.y = y;
      addRoom.w = w;
      addRoom.h = h;
      rooms[n] = addRoom;
      n++;
    }
  }
}

void draw_corridor(int x1, int y1, int x2, int y2) {
  while (x1 != x2) {
    if (x1 < x2) {
      if (area[x1][y1] == ROOM) {
	x1++;
      }
      else {
	area[x1][y1] = CORRIDOR;
	x1++;
      }
    }
    if (x2 < x1) {
      if (area[x1][y1] == ROOM) {
	x1--;
      }
      else {
	area[x1][y1] = CORRIDOR;
	x1--;
      }
    }
  }

  while (y1 != y2) {
    if (y1 < y2) {
      if (area[x2][y1] == ROOM) {
	y1++;
      }
      else {
	area[x2][y1] = CORRIDOR;
	y1++;
      }
    }
    if (y2 < y1) {
      if (area[x2][y1] == ROOM) {
	y1--;
      }
      else {
	area[x2][y1] = CORRIDOR;
	y1--;
      }
    }
  }
}

void add_corridor(void) {
  int n = 1;
  int x1, y1, x2, y2;
  while (n < MAX_ROOMS) {
    x1 = rooms[n].x;
    y1 = rooms[n].y;
    x2 = rooms[n - 1].x;
    y2 = rooms[n - 1].y;
    draw_corridor(x1,y1,x2,y2);
    n++;
  }
}

int add_hardness(void)
{
  int x,y;
  for(y = 0; y < DUNGEON_HEIGHT; y++) {
    for(x = 0; x < DUNGEON_WIDTH; x++) {
      if((x == 0) || (x == 159) || (y == 0) || (y == 104)) {
	hardness[x][y] = 255;
      }
      else if(area[x][y] == ' ') {
	int hard = ((rand() % 254) + 1);
	hardness[x][y] = hard;
      }
      else {
	hardness[x][y] = 0;
      }  
    }
  }
  return 0;
}

void dungeon_drwaing()
{
  dungeon_initial();
  add_dungeon_room();
  add_corridor();
  add_hardness();
  dungeon_display();
}


