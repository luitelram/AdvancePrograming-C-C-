
/**
	Spring 2017	
	COMS 327
	Assignmnet 2

*/

#include<string>
#include<iostream>
#include<ncurses.h>
#include<string.h>
#include<ctype.h>
#include "player.h"
#include "game.h"

using namespace std;

int main(int argc, char* argv[])
{
  if(argc !=2)
  {
  	cout<<"Please enter number of player (1 or 2) in command line"<<endl;
	return 1;
  }
  if(strcmp(argv[1],"1")!=0 && strcmp(argv[1],"2")!=0)
  {
   	cout<<"Invalid number of player ( enter 1 or 2)"<<endl;
	return 1;
  }
  char s;
  std::string n;
  cout<<"Enter first player  name: "<<endl;
  cin>>n;
  cout<<"Enter first player symbol(X goes first or O goes second): "<<endl;
  do{
    	cin>>s;
 	if(toupper(s)!='O' && toupper(s)!='X')
    	{
    		cout<<"Only 'O' or 'X' allow. Enter again:"<<endl;
    	}
  }while(toupper(s)!='O' && toupper(s)!='X');
  Player p1(n,toupper(s),true);
  bool p;
  if(strcmp(argv[1],"2")==0)
  {
	cout<<"Enter second player name: "<<endl;
 	cin>>n;
	p=true;
  }
  else
  {
 	n = "CPU";
	p=false;	
  }
  
  if(p1.getSymbol() == 'X')
	s='O';
  else
	s='X';
  Player p2(n,toupper(s),p);
  Game g(&p1,&p2);
  g.drawBoard();
  endwin();
  return 0;
}
