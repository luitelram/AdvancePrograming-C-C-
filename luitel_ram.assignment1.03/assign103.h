#ifndef ASSIGN103_H
# define ASSIGN103_H


#define ROW 105
#define COL 160

typedef struct cell
{
	char c;
	int hardness;
}cell_t;
typedef struct room
{
	int x;
	int y;
	int wide;
	int deep;
}room_t;
typedef struct path
{
  binheap_node_t *hn;
  int xpos;
  int ypos;
} path_t;
typedef struct dungeon
{
	int rm_size;
	room_t *rm;
	cell_t map[ROW][COL];
	int pc_distance[ROW][COL];
	int pc_tunnel[ROW][COL];
	int pc_x;
	int pc_y;
}dungeon_t;

dungeon_t d;


void newmap(dungeon_t *d);
void generate_map(dungeon_t *d);
void draw_map(dungeon_t *d);
room_t createRoom();
void updateRoomOnMap(dungeon_t *d);
void room_connect(dungeon_t *d);
void dijkstra_non_tunnel(dungeon_t *d);
void dijkstra_tunnel(dungeon_t *d);
void drawdist_map(dungeon_t *d);
void drawtunnel_map(dungeon_t *d);
int checkhardness(int);

#endif
