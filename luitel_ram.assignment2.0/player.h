#ifndef Player_h
#define Player_h
#include<string>

using namespace std;

class Player {
  private:
	std::string name;
	char symbol;
	bool isPlayer;
  public:
	Player(std::string name, char symbol,bool play);
	const char* getName();
	char getSymbol();
	bool getPlayer();	
};
#endif
