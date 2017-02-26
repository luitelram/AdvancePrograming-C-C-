/*
	Iowa State University
	Spring 2017
	COMS 327
	Assignment1.04
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

#include "binheap.h"
#include "assign104.h"
#include "character.h"


character_t genMCharacter(int type,dungeon_t *d){
	character_t m;
	srand(time(NULL));
	switch(type)
	{
		case 0:
			m.symbol ='0';
			m.survive = 1;
			placeCharacter(&m,d);
			m.toX = m.fromx;
			m.toY = m.fromy;
			m.isPC = 0;
			m.speed = rand()%16+5;
			m.intell = 0;
			m.tele = 0;
			m.tunnel = 0;
			m.erra = 0;
			m.nextmove = 0;
			break;
		case 1:
			m.symbol ='1';
			m.survive = 1;
			placeCharacter(&m,d);
			m.toX = m.fromx;
			m.toY = m.fromy;
			m.isPC = 0;
			m.speed = rand()%16+5;
			m.intell = 0;
			m.tele = 0;
			m.tunnel = 0;
			m.erra = 1;
			m.nextmove = 0;
			break;
		case 2:
			m.symbol ='2';
			m.survive = 1;
			placeCharacter(&m,d);
			m.toX = m.fromx;
			m.toY = m.fromy;
			m.isPC = 0;
			m.speed = rand()%16+5;
			m.intell = 0;
			m.tele = 0;
			m.tunnel = 1;
			m.erra = 0;
			m.nextmove = 0;
			break;
		case 3:
		m.symbol ='3';
			m.survive = 1;
			placeCharacter(&m,d);
			m.toX = m.fromx;
			m.toY = m.fromy;
			m.isPC = 0;
			m.speed = rand()%16+5;
			m.intell = 0;
			m.tele = 0;
			m.tunnel = 1;
			m.erra = 1;
			m.nextmove = 0;
			break;
		case 4:
		m.symbol ='4';
			m.survive = 1;
			placeCharacter(&m,d);
			m.toX = m.fromx;
			m.toY = m.fromy;
			m.isPC = 0;
			m.speed = rand()%16+5;
			m.intell = 0;
			m.tele = 1;
			m.tunnel = 0;
			m.erra = 0;
			m.nextmove = 0;
			break;
		case 5:
		m.symbol ='5';
			m.survive = 1;
			placeCharacter(&m,d);
			m.toX = m.fromx;
			m.toY = m.fromy;
			m.isPC = 0;
			m.speed = rand()%16+5;
			m.intell = 0;
			m.tele = 1;
			m.tunnel = 0;
			m.erra = 1;
			m.nextmove = 0;
			break;
		case 6:
		m.symbol ='6';
			m.survive = 1;
			placeCharacter(&m,d);
			m.toX = m.fromx;
			m.toY = m.fromy;
			m.isPC = 0;
			m.speed = rand()%16+5;
			m.intell = 0;
			m.tele = 1;
			m.tunnel = 1;
			m.erra = 0;
			m.nextmove = 0;
			break;
		case 7:
		m.symbol ='7';
			m.survive = 1;
			placeCharacter(&m,d);
			m.toX = m.fromx;
			m.toY = m.fromy;
			m.isPC = 0;
			m.speed = rand()%16+5;
			m.intell = 0;
			m.tele = 1;
			m.tunnel = 1;
			m.erra = 1;
			m.nextmove = 0;
			break;
		case 8:
		m.symbol ='8';
			m.survive = 1;
			placeCharacter(&m,d);
			m.toX = m.fromx;
			m.toY = m.fromy;
			m.isPC = 0;
			m.speed = rand()%16+5;
			m.intell = 1;
			m.tele = 0;
			m.tunnel = 0;
			m.erra = 0;
			m.nextmove = 0;
			break;
		case 9:
		m.symbol ='9';
			m.survive = 1;
			placeCharacter(&m,d);
			m.toX = m.fromx;
			m.toY = m.fromy;
			m.isPC = 0;
			m.speed = rand()%16+5;
			m.intell = 1;
			m.tele = 0;
			m.tunnel = 0;
			m.erra = 1;
			m.nextmove = 0;
			break;
		case 10:
		m.symbol ='a';
			m.survive = 1;
			placeCharacter(&m,d);
			m.toX = m.fromx;
			m.toY = m.fromy;
			m.isPC = 0;
			m.speed = rand()%16+5;
			m.intell = 1;
			m.tele = 0;
			m.tunnel = 1;
			m.erra = 0;
			m.nextmove = 0;
			break;
		case 11:
		m.symbol ='b';
			m.survive = 1;
			placeCharacter(&m,d);
			m.toX = m.fromx;
			m.toY = m.fromy;
			m.isPC = 0;
			m.speed = rand()%16+5;
			m.intell = 1;
			m.tele = 0;
			m.tunnel = 1;
			m.erra = 1;
			m.nextmove = 0;
			break;
		case 12:
		m.symbol ='c';
			m.survive = 1;
			placeCharacter(&m,d);
			m.toX = m.fromx;
			m.toY = m.fromy;
			m.isPC = 0;
			m.speed = rand()%16+5;
			m.intell = 1;
			m.tele = 1;
			m.tunnel = 0;
			m.erra = 0;
			m.nextmove = 0;
			break;
		case 13:
		m.symbol ='d';
			m.survive = 1;
			placeCharacter(&m,d);
			m.toX = m.fromx;
			m.toY = m.fromy;
			m.isPC = 0;
			m.speed = rand()%16+5;
			m.intell = 1;
			m.tele = 1;
			m.tunnel = 0;
			m.erra = 1;
			m.nextmove = 0;
			break;
		case 14:
		m.symbol ='e';
			m.survive = 1;
			placeCharacter(&m,d);
			m.toX = m.fromx;
			m.toY = m.fromy;
			m.isPC = 0;
			m.speed = rand()%16+5;
			m.intell = 1;
			m.tele = 1;
			m.tunnel = 1;
			m.erra = 0;
			m.nextmove = 0;
			break;
		case 15:
		m.symbol ='f';
			m.survive = 1;
			placeCharacter(&m,d);
			m.toX = m.fromx;
			m.toY = m.fromy;
			m.isPC = 0;
			m.speed = rand()%16+5;
			m.intell = 1;
			m.tele = 1;
			m.tunnel = 1;
			m.erra = 1;
			m.nextmove = 0;
			break;		
	}
	return m;
}
character_t genPCCharacter(dungeon_t *d){
	character_t pc;
	pc.symbol = '@';
	pc.survive = 1;
	placeCharacter(&pc,d);
	pc.toX = pc.fromx;
	pc.toY = pc.fromy;
	pc.isPC = 1;
	pc.speed = 10;
	pc.intell =0;
	pc.tele = 0;
	pc.tunnel=0;
	pc.erra = 0;
	pc.nextmove = 0;
	return pc;
}
void placeCharacter(character_t *c, dungeon_t *d){
	srand(time(NULL));
	int r ;
	do{
		r = rand() % d->rm_size;
		c->fromx = d->rm[r].x + (rand() % d->rm[r].wide);
		c->fromy = d->rm[r].y + (rand() % d->rm[r].deep);
	}while(d->map[c->fromy][c->fromx].ch != '.');
		
}
void nextTurn(character_t *c)
{
  c->nextmove += 100/c->speed;
}
void nextPos(character_t *c, dungeon_t *d){
	if(c->isPC == 1)
	{
		do{
			c->toX = c->fromx + rand()%3-1;
			c->toY = c->fromy + rand()%3-1;	
		}while(d->map[c->toY][c->toX].hardness!=0);
		
	}
	else
	{	
		if(c->intell==0&&c->tunnel==0&&c->tele==0&&c->erra==0)
		{
			do{
					c->toX = c->fromx + rand()%3-1;
					c->toY = c->fromy + rand()%3-1;	
				}while(d->map[c->toY][c->toX].hardness!=0);
		}
		
		if(c->erra==1)
		{
			int chance,count=0;
			chance = rand()%2;
			if(chance==1)
			{
				count++;
				c->intell = 1;
			}
			chance = rand()%2;
			if(chance==1)
			{
				count++;
				c->tele = 1;
			}
			chance = rand()%2;
			if(chance==1)
			{
				count++;
				c->tunnel = 1;
			}
			if(count==0){
				do{
					c->toX = c->fromx + rand()%3-1;
					c->toY = c->fromy + rand()%3-1;	
				}while(d->map[c->toY][c->toX].hardness!=0);
				if(c->tele==0&&c->intell==0&&c->tunnel==0)
					return;
			}
		}
		if(c->tunnel == 1){
			if(c->tele==1&&c->intell==1){
				int cost = d->pc_tunnel[c->fromx][c->fromy];
				if (d->pc_tunnel[c->fromx-1][c->fromy-1]<cost){//checks up
						c->toX=c->fromx-1; 
						c->toY=c->fromy-1; 
						cost=d->pc_tunnel[c->fromx-1][c->fromy-1];
				}
				if (d->pc_tunnel[c->fromx-1][c->fromy]<cost){//checks left
						c->toX=c->fromx-1; 
						c->toY=c->fromy; 
						cost=d->pc_tunnel[c->fromx-1][c->fromy];
				}
				if (d->pc_tunnel[c->fromx-1][c->fromy+1]<cost){//checks right
						c->toX=c->fromx-1; 
						c->toY=c->fromy+1 ;
						cost=d->pc_tunnel[c->fromx-1][c->fromy+1];
				}
				if (d->pc_tunnel[c->fromx][c->fromy-1]<cost){//checks up
						c->toX=c->fromx; 
						c->toY=c->fromy-1; 
						cost=d->pc_tunnel[c->fromx][c->fromy-1];
				}
				if (d->pc_tunnel[c->fromx][c->fromy+1]<cost){//checks left
						c->toX=c->fromx; 
						c->toY=c->fromy+1; 
						cost=d->pc_tunnel[c->fromx][c->fromy+1];
				}
				if (d->pc_tunnel[c->fromx+1][c->fromy-1]<cost){//checks up
						c->toX=c->fromx+1; 
						c->toY=c->fromy-1; 
						cost=d->pc_tunnel[c->fromx+1][c->fromy-1];
				}
				if (d->pc_tunnel[c->fromx+1][c->fromy]<cost){//checks left
						c->toX=c->fromx+1; 
						c->toY=c->fromy; 
						cost=d->pc_tunnel[c->fromx+1][c->fromy];
				}
				if (d->pc_tunnel[c->fromx+1][c->fromy+1]<cost){//checks right
						c->toX=c->fromx+1; 
						c->toY=c->fromy+1 ;
						cost=d->pc_tunnel[c->fromx+1][c->fromy+1];
				}
			}
			else if(c->tele==1&&c->intell==0){
				if(d->crt[0].fromx > c->fromx)
					c->toX = c->fromx + 1;
				else if(d->crt[0].fromx < c->fromx)
					c->toX = c->fromx - 1;
				else
					c->toX = c->fromx;
				if(d->crt[0].fromy > c->fromy)
					c->toY = c->fromy + 1;
				else if(d->crt[0].fromy < c->fromy)
					c->toY = c->fromy - 1;
				else
					c->toY = c->fromy;
			}
		}
		else{
			//not done
		}
		
	}	
}

void updatePos(character_t *c){
	 c->fromx =c->toX;
		 c->fromy=c->toY;
}



