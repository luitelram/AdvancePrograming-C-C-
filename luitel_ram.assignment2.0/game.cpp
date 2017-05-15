/**
	Spring 2017	
	COMS 327
	Assignmnet 2

*/

#include<string>
#include<iostream>
#include<vector>
#include<ncurses.h>
#include<string.h>
#include<stdlib.h>
#include"game.h"

using namespace std;

Game::Game(Player *p1, Player *p2)
{
  int i,j;
  if(p1->getSymbol() == 'X')
  {
 	parr[0]=p1;
	parr[1]=p2;
  }
  else
  {
  	parr[0]=p2;
  	parr[1]=p1;
  }
  board = std::vector< std::vector<char> >(DIMS, std::vector<char>(DIMS));
  marked=std::vector< std::vector<bool> >(DIMS, std::vector<bool>(DIMS));
  position=std::vector<int>(9);
  for(i = 0;i<DIMS;i++)
  {  
    for(j=0;j<DIMS;j++)
    {
    	board[i][j] = ' ';
        marked[i][j] = false;
       	position[i*DIMS+j] = i*DIMS+j;
    }
  }
 turn = 0;
}
int Game::getTurn(){
  return turn;
}
std::vector< int > Game::getPos(){return position;}
int Game::chkWinner(){
  int i;
//Horizontal
  for(i=0;i<DIMS;i++)
  {
   	if(board[i][0] != ' '&&board[i][0]==board[i][1]&&board[i][0]==board[i][2])
	  return 1;
  }
//Vertical
  for(i=0;i<DIMS;i++)
  {
   	if(board[0][i] != ' '&&board[0][i]==board[1][i]&&board[0][i]==board[2][i])
          return 1;
  }
//Diagonal
  if(board[0][0]!=' '&&board[1][1]==board[2][2]&&board[0][0]==board[2][2])
    return 1;
  if(board[0][2]!=' '&&board[1][1]==board[0][2]&&board[0][2]==board[2][0])
    return 1;
return 0;
}
void Game::drawBoard(){
  initscr();
  raw();
  noecho();
  curs_set(0);
  keypad(stdscr,TRUE);
  start_color();
  init_pair(1,COLOR_RED,COLOR_BLACK);
  init_pair(2,COLOR_BLUE,COLOR_BLACK);
  init_pair(3,COLOR_GREEN,COLOR_BLACK);
  init_pair(4,COLOR_YELLOW,COLOR_BLACK);
  char title[80]="Tic Tac Toe\n";
  strcat(title,"Player(X): ");
  strcat(title,parr[0]->getName());
  strcat(title," VS Player(O): ");
  strcat(title,parr[1]->getName());
  mvprintw(0,0,title);
  mvprintw(6,0,"Q to quit game");
  int i,j;
  for(i=0;i<11;i++)
  {  for(j=0;j<11;j++)
     {	
	if(j==3||j==7)
	  mvaddch(8+j,10+i,'-');
	else if(i==3||i==7)
	 mvaddch(8+j,10+i,'|');
	else	
	  mvaddch(8+j,10+i,' ');  
     }
  }
  attron(COLOR_PAIR(4));
  mvaddch(8,12,'0');
 mvaddch(8,16,'1');
 mvaddch(8,20,'2');
 mvaddch(12,12,'3');
 mvaddch(12,16,'4');
 mvaddch(12,20,'5');
 mvaddch(16,12,'6');
 mvaddch(16,16,'7');
 mvaddch(16,20,'8');
  attroff(COLOR_PAIR(4));	
  updateGame();
  return;
}
void Game::updateGame(){
  char in;
  int pos=-1,r,c;
  char stt[80]="It's ";
  srand(time(NULL));
  
do{
  if(parr[turn%2]->getPlayer()==true){
    strcat(stt,parr[turn%2]->getName());
    strcat(stt,"'s turn. Enter position(1-9): ");
    mvprintw(3,0,stt);
    do{
      in=getch();
      move(4,0);
      clrtoeol();
      if((in<48||in >56)&& in!='q'){
	mvprintw(4,0,"Invalid postion. Select 1-9");
      }	
    }while((in<48||in >56)&& in!='q');
    switch(in)
      {
	case '0':
		pos=0;break;
	case '1':
		pos=1;break;
	case '2':
		pos=2;break;
	case '3':
		pos=3;break;
	case '4':
		pos=4;break;
	case '5':
		pos=5;break;
	case '6':
		pos=6;break;
	case '7':
		pos=7;break;
	case '8':
		pos=8;break;
	case 'q': break;	
      }
     if(in!='q'){
     	if(board[pos/DIMS][pos%DIMS]!=' '){
		mvprintw(4,0,"Postion has been marked. Select another");
	}
	else{
  	 	board[pos/DIMS][pos%DIMS]=parr[turn%2]->getSymbol();
		if(turn%2==0)		
			redraw(pos/DIMS,pos%DIMS,1);
		else
			redraw(pos/DIMS,pos%DIMS,2);
	    	turn++;
        }
     }
  }
  else
  {
	do{
	  r=rand()%3;
 	  c=rand()%3;
	}while(board[r][c]!=' ');
	board[r][c]=parr[turn%2]->getSymbol();
	redraw(r,c,3);
	turn++;
  } 
    move(3,0);
    clrtoeol();
    strcpy(stt,"It's \0");
    
}while(chkWinner()!=1 && in!='q'&&turn!=9);
if(chkWinner()==1){
  char result[80]="";
  turn--;
  strcat(result,parr[turn%2]->getName());
  strcat(result, " win.\nHit q to exit");
  mvprintw(19,0,result);
  do{}while(getch()!='q');
}else
{
 if(turn==9)
 {	mvprintw(19,0,"Draw game.\nHit q to exit");
 	do{}while(getch()!='q');
 }
}
  endwin();
  return;
}
void Game::redraw(int i,int j, int color){
  if(color==1)
   attron(COLOR_PAIR(1));
  else if(color==2)
   attron(COLOR_PAIR(2));
  else
   attron(COLOR_PAIR(3));
	
	if(board[i][j]!=' ')
	{
	  if(i==0)
	  {
		if(j==0)
		  mvaddch(9,11,board[i][j]);
		if(j==1)
		  mvaddch(9,15,board[i][j]);
		if(j==2)
		  mvaddch(9,19,board[i][j]);	
	  }
	  if(i==1)
	  {
		if(j==0)
		  mvaddch(13,11,board[i][j]);
		if(j==1)
		  mvaddch(13,15,board[i][j]);
		if(j==2)
		  mvaddch(13,19,board[i][j]);	
	  }
	  if(i==2)
	  {
		if(j==0)
		  mvaddch(17,11,board[i][j]);
		if(j==1)
		  mvaddch(17,15,board[i][j]);
		if(j==2)
		  mvaddch(17,19,board[i][j]);	
	  }			
	} 

if(color==1)
   attroff(COLOR_PAIR(1));
  else if(color==2)
   attroff(COLOR_PAIR(2));
  else
   attroff(COLOR_PAIR(3));
  return;
}
