/**
	Spring 2017	
	COMS 327
	Assignmnet 2

*/

#include<string>
#include<iostream>
#include "player.h"

using namespace std;

Player::Player(std::string n, char s,bool p)
	{
	  name = n;
	  symbol = s;
	  isPlayer = p;
	}
const char* Player::getName()
	{
	  return name.c_str();
	}
char Player::getSymbol()
	{
	  return symbol;	
	}	
bool Player::getPlayer()
	{
 	  return isPlayer;	
	}
