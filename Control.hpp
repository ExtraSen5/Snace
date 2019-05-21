#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "Game.hpp"
#include "keypressable.hpp"

class Control
{
public:
	Control(Snake * p);
	Snake * s;
};

class ConMan :public Control, public keypressable
{
public:
	ConMan(Snake * p = nullptr);
	void onkey(int key);
};
	
class Robot:public Control
{
public:
    void onthink();
    Coord distance(Coord rab);
    Robot(Snake*);
};

#endif


