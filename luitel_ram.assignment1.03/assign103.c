/*
	Iowa State University
	Spring 2017
	COMS 327
	Assignment1.03
*/
#include <stdio.h>
#include <stdint.h> 
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>    
#include <unistd.h>  
#include <string.h> 
#include <endian.h> 
#include <time.h>  
#include <math.h>
#include "binheap.h"
#include"assign103.h"

/* Main function */
int main(int argc, char *argv[])
{	
	newmap(&d);
	dijkstra_non_tunnel(&d);
	printf("\t\t\t\t\t\t\t\tDistance map\n");
	drawdist_map(&d);
	printf("\t\t\t\t\t\t\t\tTunnel map\n");
	dijkstra_tunnel(&d);
	drawtunnel_map(&d);
	return 0;
}
/* generate new map */
void newmap(dungeon_t *d)
{
	generate_map(d);
	srand(time(NULL));
	d->rm_size= 10+rand()%3;	
	d->rm = (room_t*)malloc(sizeof(room_t)*d->rm_size);
	updateRoomOnMap(d);
	room_connect(d);
	d->pc_y = (2*d->rm[0].x+d->rm[0].wide)/2;
	d->pc_x = (2*d->rm[0].y+d->rm[0].deep)/2;
	d->map[d->pc_x][d->pc_y].c = '@';
	draw_map(d);
}
/* Draw a distace map   */
void drawdist_map(dungeon_t *d)
{
	int i,j;	
   for(i=0;i<ROW;i++)
	{
		for(j=0;j<COL;j++)
		{
			if(d->pc_distance[i][j]!=255)
				printf("%d",d->pc_distance[i][j]%10);
			else 
				printf("%c",d->map[i][j].c);
		}
		printf("\n");
	}
}
/*Generate tunnel map */
void drawtunnel_map(dungeon_t *d)
{
	int i,j;	
   for(i=0;i<ROW;i++)
	{
		for(j=0;j<COL;j++)
		{
		    if(d->pc_tunnel[i][j]!=255)
			printf("%d",d->pc_tunnel[i][j]%10);
		   else 
			printf("%c",d->map[i][j].c);
		}
		printf("\n");
	}
}

int32_t dist_cmp(const void *key, const void *with) {
  return ((int32_t) d.pc_distance[((path_t *) key)->xpos]
                                        [((path_t *) key)->ypos] -
          (int32_t) d.pc_distance[((path_t *) with)->xpos]
                                        [((path_t *) with)->ypos]);
}
int32_t tunnel_cmp(const void *key, const void *with) {
  return ((int32_t) d.pc_tunnel[((path_t *) key)->xpos]
                                        [((path_t *) key)->ypos] -
          (int32_t) d.pc_tunnel[((path_t *) with)->xpos]
                                        [((path_t *) with)->ypos]);
}

/* This is dijkstra non tunnel distance calculation */
void dijkstra_non_tunnel(dungeon_t *d)
{	
	binheap_t hp;
	path_t p[ROW][COL], *temp;
	int i,j;
	
	
		for(i=0;i<ROW;i++)
		{
			for(j=0;j<COL;j++)
			{
				p[i][j].xpos=i;
				p[i][j].ypos=j;
			}
		}
	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COL;j++)
		{
			d->pc_distance[i][j]=255;
		}
	}
	
	d->pc_distance[d->pc_x][d->pc_y] = 0;
	binheap_init(&hp,dist_cmp,NULL);
	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COL;j++)
		{
			if(d->map[i][j].c == '.' || d->map[i][j].c == '#' || d->map[i][j].c == '@')
			{
				p[i][j].hn = binheap_insert(&hp,&p[i][j]);
				
			}
			else
			{
				p[i][j].hn = NULL;
			}
		}
	}
	
	while((temp = (path_t*)binheap_remove_min(&hp)))
	{	
		temp->hn=NULL;
	
		if((p[temp->xpos-1][temp->ypos-1].hn)&& (d->pc_distance[temp->xpos-1][temp->ypos-1]>d->pc_distance[temp->xpos][temp->ypos]+1))
		{	d->pc_distance[temp->xpos-1][temp->ypos-1] = d->pc_distance[temp->xpos][temp->ypos]+1;
			binheap_decrease_key(&hp, p[temp->xpos-1][temp->ypos-1].hn);	
		}
		if((p[temp->xpos-1][temp->ypos].hn)&& (d->pc_distance[temp->xpos-1][temp->ypos]>d->pc_distance[temp->xpos][temp->ypos]+1))
		{	d->pc_distance[temp->xpos-1][temp->ypos] = d->pc_distance[temp->xpos][temp->ypos]+1;
			binheap_decrease_key(&hp, p[temp->xpos-1][temp->ypos].hn);
		}
		if((p[temp->xpos-1][temp->ypos+1].hn)&&(d->pc_distance[temp->xpos-1][temp->ypos+1]>d->pc_distance[temp->xpos][temp->ypos]+1))
		{	d->pc_distance[temp->xpos-1][temp->ypos+1] = d->pc_distance[temp->xpos][temp->ypos]+1;
			binheap_decrease_key(&hp, p[temp->xpos-1][temp->ypos+1].hn);
		}
		if((p[temp->xpos][temp->ypos-1].hn)&& (d->pc_distance[temp->xpos][temp->ypos-1]>d->pc_distance[temp->xpos][temp->ypos]+1))
		{	d->pc_distance[temp->xpos][temp->ypos-1] = d->pc_distance[temp->xpos][temp->ypos]+1;
			binheap_decrease_key(&hp, p[temp->xpos][temp->ypos-1].hn);
		}
		if((p[temp->xpos][temp->ypos+1].hn)&& (d->pc_distance[temp->xpos][temp->ypos+1]>d->pc_distance[temp->xpos][temp->ypos]+1))
		{	d->pc_distance[temp->xpos][temp->ypos+1] = d->pc_distance[temp->xpos][temp->ypos]+1;
			binheap_decrease_key(&hp, p[temp->xpos][temp->ypos+1].hn);
		}
		if((p[temp->xpos+1][temp->ypos-1].hn )&& (d->pc_distance[temp->xpos+1][temp->ypos-1]>d->pc_distance[temp->xpos][temp->ypos]+1))
		{	d->pc_distance[temp->xpos+1][temp->ypos-1] = d->pc_distance[temp->xpos][temp->ypos]+1;
			binheap_decrease_key(&hp, p[temp->xpos+1][temp->ypos-1].hn);
		}
		if((p[temp->xpos+1][temp->ypos].hn)&& (d->pc_distance[temp->xpos+1][temp->ypos]>d->pc_distance[temp->xpos][temp->ypos]+1))
		{	d->pc_distance[temp->xpos+1][temp->ypos] = d->pc_distance[temp->xpos][temp->ypos]+1;
			binheap_decrease_key(&hp, p[temp->xpos+1][temp->ypos].hn);
		}
		if((p[temp->xpos+1][temp->ypos+1].hn)&& (d->pc_distance[temp->xpos+1][temp->ypos+1]>d->pc_distance[temp->xpos][temp->ypos]+1))
		{	d->pc_distance[temp->xpos+1][temp->ypos+1] = d->pc_distance[temp->xpos][temp->ypos]+1;
			binheap_decrease_key(&hp, p[temp->xpos+1][temp->ypos+1].hn);
		}
	}
	binheap_delete(&hp);
}
/* This function check the hardness  */
int checkhardness(int h)
{
	if(h>=0 && h<=84)
	{	return 1;}
	if(h>=85&&h<=170)
	{	return 2;}
	if(h>=171&&h<=254)
	{	return 3;}
	return 0;
}

/* This function used dijkstra algorithum to calculate tunnal map distance */
void dijkstra_tunnel(dungeon_t *d)
{	
	binheap_t hp;
	path_t p[ROW][COL], *temp;
	int i,j;

		for(i=0;i<ROW;i++)
		{
			for(j=0;j<COL;j++)
			{
				p[i][j].xpos=i;
				p[i][j].ypos=j;
			}
		}
	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COL;j++)
		{
			d->pc_tunnel[i][j]=255;
		}
	}
	d->pc_tunnel[d->pc_x][d->pc_y] = 0;
	d->pc_tunnel[d->pc_x][d->pc_y] = 0;
	binheap_init(&hp,tunnel_cmp,NULL);
	
	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COL;j++)
		{
			if(d->map[i][j].hardness!=255)
			{	p[i][j].hn = binheap_insert(&hp,&p[i][j]);
	
			}
			else
			{
				p[i][j].hn = NULL;
			}
		}
	}
	
	while((temp = (path_t*)binheap_remove_min(&hp)))
	{	
		temp->hn=NULL;
		if((p[temp->xpos-1][temp->ypos-1].hn)&& 	
			(d->pc_tunnel[temp->xpos-1][temp->ypos-1]>d->pc_tunnel[temp->xpos][temp->ypos]+checkhardness(d->map[temp->xpos-1][temp->ypos-1].hardness)))
		{	d->pc_tunnel[temp->xpos-1][temp->ypos-1] = d->pc_tunnel[temp->xpos][temp->ypos]+checkhardness(d->map[temp->xpos-1][temp->ypos-1].hardness);
			binheap_decrease_key(&hp, p[temp->xpos-1][temp->ypos-1].hn);		
		}
		if((p[temp->xpos-1][temp->ypos].hn)&& 
			(d->pc_tunnel[temp->xpos-1][temp->ypos]>d->pc_tunnel[temp->xpos][temp->ypos]+checkhardness(d->map[temp->xpos-1][temp->ypos].hardness)))
		{	d->pc_tunnel[temp->xpos-1][temp->ypos] = d->pc_tunnel[temp->xpos][temp->ypos]+checkhardness(d->map[temp->xpos-1][temp->ypos].hardness);
			binheap_decrease_key(&hp, p[temp->xpos-1][temp->ypos].hn);
		}
		if((p[temp->xpos-1][temp->ypos+1].hn)&&
			(d->pc_tunnel[temp->xpos-1][temp->ypos+1]>d->pc_tunnel[temp->xpos][temp->ypos]+checkhardness(d->map[temp->xpos-1][temp->ypos+1].hardness)))
		{	d->pc_tunnel[temp->xpos-1][temp->ypos+1] = d->pc_tunnel[temp->xpos][temp->ypos]+checkhardness(d->map[temp->xpos-1][temp->ypos+1].hardness);
			binheap_decrease_key(&hp, p[temp->xpos-1][temp->ypos+1].hn);	
		}
		if((p[temp->xpos][temp->ypos-1].hn)&& 
			(d->pc_tunnel[temp->xpos][temp->ypos-1]>d->pc_tunnel[temp->xpos][temp->ypos]+checkhardness(d->map[temp->xpos][temp->ypos-1].hardness)))
		{	d->pc_tunnel[temp->xpos][temp->ypos-1] = d->pc_tunnel[temp->xpos][temp->ypos]+checkhardness(d->map[temp->xpos][temp->ypos-1].hardness);
			binheap_decrease_key(&hp, p[temp->xpos][temp->ypos-1].hn);
		}
		if((p[temp->xpos][temp->ypos+1].hn)&& 
			(d->pc_tunnel[temp->xpos][temp->ypos+1]>d->pc_tunnel[temp->xpos][temp->ypos]+checkhardness(d->map[temp->xpos][temp->ypos+1].hardness)))
		{	d->pc_tunnel[temp->xpos][temp->ypos+1] = d->pc_tunnel[temp->xpos][temp->ypos]+checkhardness(d->map[temp->xpos][temp->ypos+1].hardness);
			binheap_decrease_key(&hp, p[temp->xpos][temp->ypos+1].hn);	
		}
		if((p[temp->xpos+1][temp->ypos-1].hn )&& 
		(d->pc_tunnel[temp->xpos+1][temp->ypos-1]>d->pc_tunnel[temp->xpos][temp->ypos]+checkhardness(d->map[temp->xpos+1][temp->ypos-1].hardness)))
		{	d->pc_tunnel[temp->xpos+1][temp->ypos-1] = d->pc_tunnel[temp->xpos][temp->ypos]+checkhardness(d->map[temp->xpos+1][temp->ypos-1].hardness);
			binheap_decrease_key(&hp, p[temp->xpos+1][temp->ypos-1].hn);
		}
		if((p[temp->xpos+1][temp->ypos].hn)&& 
			(d->pc_tunnel[temp->xpos+1][temp->ypos]>d->pc_tunnel[temp->xpos][temp->ypos]+checkhardness(d->map[temp->xpos+1][temp->ypos].hardness)))
		{	d->pc_tunnel[temp->xpos+1][temp->ypos] = d->pc_tunnel[temp->xpos][temp->ypos]+checkhardness(d->map[temp->xpos+1][temp->ypos].hardness);
			binheap_decrease_key(&hp, p[temp->xpos+1][temp->ypos].hn);
		}
		if((p[temp->xpos+1][temp->ypos+1].hn)&& 
			(d->pc_tunnel[temp->xpos+1][temp->ypos+1]>d->pc_tunnel[temp->xpos][temp->ypos]+checkhardness(d->map[temp->xpos+1][temp->ypos+1].hardness)))
		{	d->pc_tunnel[temp->xpos+1][temp->ypos+1] = d->pc_tunnel[temp->xpos][temp->ypos]+checkhardness(d->map[temp->xpos+1][temp->ypos+1].hardness);
			binheap_decrease_key(&hp, p[temp->xpos+1][temp->ypos+1].hn);
		}
	}
	binheap_delete(&hp);
}
/*  Generate map */
void generate_map(dungeon_t *d)
{	int i,j,hness;	
	for(i=0;i<ROW;i++)
	{   
		for(j=0;j<COL;j++)
	    {
			if(i==0 || i==ROW-1)
			{	d->map[i][j].c = '-';
				d->map[i][j].hardness = 255;
			}
			else
			{ 
				if(j==0 ||j==COL-1)
				{	
					d->map[i][j].c = '|';	
					d->map[i][j].hardness = 255;
				}
				else
				{	
					d->map[i][j].c = ' ';	
					hness = rand()%255; 
					d->map[i][j].hardness = hness+1;
				}
			}
		}
	}
}
/* This function display the dungeon */
void draw_map(dungeon_t *d)
{     int i,j;	
      for(i=0;i<ROW;i++)
      {   for(j=0;j<COL;j++)
	  {  
		printf("%c",d->map[i][j].c);
	  }
	  printf("\n");
      }
}
/* This function generate the random room of the 160X105 dimension */
room_t createRoom()
{
	room_t temp;
	temp.x=rand()%159+1;
	temp.y=rand()%101+1;
	temp.deep=5+rand()%5;
	temp.wide=7+rand()%10;
	return temp;
}
//Draw room on dungeon
void updateRoomOnMap(dungeon_t *d)
{	int i,k,l,ok;
	room_t t;
	for(i=0;i<d->rm_size;i++)
	{	
		do{
			t = createRoom();
			ok=1;
			for(k=t.y-1;k<t.y+t.deep+1;k++)
			{
				for(l=t.x-1;l<t.x+t.wide+1;l++)
				{
					if(d->map[k][l].c != ' ')
					{
						ok=0;
						break;
					}
				}
			}
		}while(ok==0);
		
		for(k=t.y;k<t.y+t.deep;k++)
		{
			for(l=t.x;l<t.x+t.wide;l++)
			{
				d->map[k][l].c='.';
				d->map[k][l].hardness=0;
			}
		}
		//Save room in array
		d->rm[i].x=t.x;
		d->rm[i].y=t.y;
		d->rm[i].wide=t.wide;
		d->rm[i].deep=t.deep;	
	}
}
/*Connect all the rooms that are generated */
void room_connect(dungeon_t *d)
{
	int midx1,midy1,midx2,midy2,i,j,k,l;
	int prob;
	for(i=0;i<d->rm_size-1;i++)
	{	
		j=i+1;
		
		midx1 = (2*d->rm[i].x+d->rm[i].wide)/2;
		midy1 = (2*d->rm[i].y+d->rm[i].deep)/2;
		midx2 = (2*d->rm[j].x+d->rm[j].wide)/2;
		midy2 = (2*d->rm[j].y+d->rm[j].deep)/2;
		if(midx1<midx2)
		{
			for(k=midx1;k<midx2;k++)
			{
				if(d->map[midy1][k].c == ' ')
				{
					d->map[midy1][k].c = '#';
					d->map[midy1][k].hardness = 0;	
				}
				//Change direction on corridor (rate 5%)
				prob = rand()%20;
				if(prob == 1 && midy1 < ROW && midy1 > 0 && d->map[midy1+1][k].c == ' ')
				{
					midy1++;
					k--;
				}
				if(prob == 2 && midy1 < ROW && midy1 > 0 && d->map[midy1-1][k].c == ' ')
				{
					midy1--;
					k--;
				}				
			}
			if(midy1<midy2)
			{
				for(l=midy1;l<midy2;l++)
				{
					if(d->map[l][k].c == ' ')
					{
						d->map[l][k].c = '#';	
						d->map[l][k].hardness = 0;						
					}
				}
			}
			else
			{
				for(l=midy1;l>midy2;l--)
				{
					if(d->map[l][k].c == ' ')
					{
						d->map[l][k].c = '#';	
						d->map[l][k].hardness = 0;
					}
				}
			}
		}
		else 
		{
			for(k=midx2;k<midx1;k++)
			{
				if(d->map[midy2][k].c == ' ')	
				{
					d->map[midy2][k].c = '#';
					d->map[midy2][k].hardness = 0;	
				}	
				prob = rand()%200;
				if(prob == 1 && midy2 < ROW && midy2 > 0 && d->map[midy2+1][k].c == ' ')
				{
					midy2++;
					k--;
				}
				if(prob == 2 && midy2 < ROW && midy2 > 0 && d->map[midy2-1][k].c == ' ')
				{
					midy2--;
					k--;
				}							
			}
			if(midy2<midy1)
				{
				for(l=midy2;l<midy1;l++)
				{
					if(d->map[l][k].c == ' ')
					{
						d->map[l][k].c = '#';	
						d->map[l][k].hardness = 0;
					}	
				}
			}
			else
			{
				for(l=midy2;l>midy1;l--)
				{
					if(d->map[l][k].c == ' ')
					{
						d->map[l][k].c = '#';	
						d->map[l][k].hardness = 0;
					}		
				}
			}
		}
		
	}
}

