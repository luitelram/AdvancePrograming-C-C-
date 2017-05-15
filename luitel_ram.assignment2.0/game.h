#ifndef Game_h
#define Game_h
#include<string>
#include<iostream>
#include<vector>
#include"player.h"

using namespace std;

#define DIMS 3

class Game{
  private:
	std::vector< std::vector<char> > board;
	std::vector< std::vector<bool> > marked;
	std::vector<int> position;
	Player* parr[2];
	int turn;
  public:
	Game(Player *p1, Player *p2);
	int chkWinner();
	void drawBoard();
	int getTurn();
 	vector<int> getPos();
	void updateGame();
	void redraw(int r,int c,int color);
};
#endif
