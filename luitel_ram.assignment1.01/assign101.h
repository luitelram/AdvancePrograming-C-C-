#ifndef ASSIGN101_H
# define ASSIGN101_H


#define ROW 105
#define COLUMN 160


typedef struct
{
	char c;
	int hardness;
}cell;
typedef struct 
{
	int x;
	int y;
	int wide;
	int deep;
}room;

/*------------------Function declaration-------------------*/ 
void generate_map(cell(*p)[ROW][COLUMN]);
void draw_map(cell(*p)[ROW][COLUMN]);
room createRoom();
void updateRoomOnMap(room*,int,cell(*pt)[ROW][COLUMN]);
void room_connect(room*,int,cell(*pt)[ROW][COLUMN]);
/*-----------------------------------------------*/


#endif
