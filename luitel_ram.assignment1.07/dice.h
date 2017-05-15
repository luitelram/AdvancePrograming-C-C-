#ifndef DICE_H
# define DICE_H

//#include <iostream>

class dice{
	private: 
          int base, number, sides;
	  
	public:	  
	dice(int base, int number, int sides)
	{
		this->base = base; 
		this->number = number; 
		this->sides = sides; 
	}
	int getBase(){
		return base; 
	}
	int getSides(){
		return sides; 
	}
	int getNumber(){
		return number; 
	}
}; 

#endif
