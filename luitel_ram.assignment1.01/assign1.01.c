/*-----------------Header----------------
	ComS327
	Spring 2017
	Assignment1.01

*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"assign101.h"

/* Main function */
int main(int argc, char *argv[])
{	
	int rm_size;
	room *rm;
	cell map[ROW][COLUMN];
	generate_map(&map);
	srand(time(NULL));
	rm_size=10+rand()%5;	
	rm = (room*)malloc(sizeof(room)*rm_size);
	updateRoomOnMap(rm,rm_size,&map);
	room_connect(rm,rm_size,&map);
	free(rm);
	draw_map(&map);
	return 0;
}
/* Go over the dungeon array to draw the boundary */
void generate_map(cell (*p)[ROW][COLUMN])
{	int i,j;	
	for(i=0;i<ROW;i++)
	{   
		for(j=0;j<COLUMN;j++)
	    {
			if(i==0 || i==ROW-1)
			{	(*p)[i][j].c = '-';
				(*p)[i][j].hardness = 1;
			}
			else
			{ 
				if(j==0 ||j==COLUMN-1)
				{	
					(*p)[i][j].c = '|';	
					(*p)[i][j].hardness = 1;
				}
				else
				{	
					(*p)[i][j].c = ' ';	
					(*p)[i][j].hardness = 1;
				}
			}
		}
	}
}
/* This function display the dungeon */
void draw_map(cell (*p)[ROW][COLUMN])
{     int i,j;	
      for(i=0;i<ROW;i++)
      {   for(j=0;j<COLUMN;j++)
	  {  
		printf("%c",(*p)[i][j].c);
	  }
	  //printf("%d\n",i);
	  printf("\n");
      }
}
/* This function generate the random room of the 160X105 dimension */
room createRoom()
{
	room temp;
	temp.x=rand()%159+1;
	temp.y=rand()%101+1;
	temp.deep=5+rand()%5;
	temp.wide=7+rand()%10;
	return temp;
}
/*Draw room on dungeon of the above size */
void updateRoomOnMap(room *p,int size,cell (*pt)[ROW][COLUMN])
{	int i,k,l,ok;
	room t;
	for(i=0;i<size;i++)
	{
		do{
			t = createRoom();
			ok=1;
			for(k=t.y-1;k<=t.y+t.deep+1;k++)
			{
				for(l=t.x-1;l<=t.x+t.wide+1;l++)
				{
					if((*pt)[k][l].c != ' ')
					{
						ok=0;
						break;
					}
				}
			}
		}while(ok==0);

		for(k=t.y;k<=t.y+t.deep;k++)
		{
			for(l=t.x;l<=t.x+t.wide;l++)
			{
				(*pt)[k][l].c='.';
				(*pt)[k][l].hardness=0;
			}
		}
	
		p[i].x=t.x;
		p[i].y=t.y;
		p[i].wide=t.wide;
		p[i].deep=t.deep;	
	}
}
/*Connect all the rooms that are generated */
void room_connect(room *p,int size,cell (*pt)[ROW][COLUMN])
{
	int midx1,midy1,midx2,midy2,i,j,k,l;
	int prob;
	for(i=0;i<size-1;i++)
	{	
		j=i+1;
		midx1 = (2*p[i].x+p[i].wide)/2;
		midy1 = (2*p[i].y+p[i].deep)/2;
		midx2 = (2*p[j].x+p[j].wide)/2;
		midy2 = (2*p[j].y+p[j].deep)/2;
		if(midx1<midx2)
		{
			for(k=midx1;k<midx2;k++)
			{
				if((*pt)[midy1][k].c == ' ')
				{
					(*pt)[midy1][k].c = '#';
					(*pt)[midy1][k].hardness = 0;	
				}
				
				prob = rand()%20;
				if(prob == 1 && midy1 < ROW && midy1 > 0 && (*pt)[midy1+1][k].c == ' ')
				{
					midy1++;
					k--;
				}
				if(prob == 2 && midy1 < ROW && midy1 > 0 && (*pt)[midy1-1][k].c == ' ')
				{
					midy1--;
					k--;
				}				
			}
			if(midy1<midy2)
			{
				for(l=midy1;l<midy2;l++)
				{
					if((*pt)[l][k].c == ' ')
					{
						(*pt)[l][k].c = '#';	
						(*pt)[l][k].hardness = 0;						
					}
				}
			}
			else
			{
				for(l=midy1;l>midy2;l--)
				{
					if((*pt)[l][k].c == ' ')
					{
						(*pt)[l][k].c = '#';	
						(*pt)[l][k].hardness = 0;
					}
				}
			}
		}
		else 
		{
			for(k=midx2;k<midx1;k++)
			{
				if((*pt)[midy2][k].c == ' ')	
				{
					(*pt)[midy2][k].c = '#';
					(*pt)[midy2][k].hardness = 0;	
				}	
				prob = rand()%200;
				if(prob == 1 && midy2 < ROW && midy2 > 0 && (*pt)[midy2+1][k].c == ' ')
				{
					midy2++;
					k--;
				}
				if(prob == 2 && midy2 < ROW && midy2 > 0 && (*pt)[midy2-1][k].c == ' ')
				{
					midy2--;
					k--;
				}							
			}
			if(midy2<midy1)
				{
				for(l=midy2;l<midy1;l++)
				{
					if((*pt)[l][k].c == ' ')
					{
						(*pt)[l][k].c = '#';	
						(*pt)[l][k].hardness = 0;
					}	
				}
			}
			else
			{
				for(l=midy2;l>midy1;l--)
				{
					if((*pt)[l][k].c == ' ')
					{
						(*pt)[l][k].c = '#';	
						(*pt)[l][k].hardness = 0;
					}		
				}
			}
		}
		
	}
}


