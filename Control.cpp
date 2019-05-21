#include <iostream>
#include <algorithm>
#include "Game.hpp"
#include "Control.hpp"
#include "keypressable.hpp"
#include "tui.hpp"
#include "View.hpp"
Control::Control(Snake * p)
{
	s = p;	
}

ConMan::ConMan(Snake * p) : Control(p)
{
	View * v = tui::get();
	v -> setonkey(this);
}

void ConMan::onkey(int key)
{
    switch(key){
        case('w'): this->s->setdirection(UP); break;
        case('s'): this->s->setdirection(DOWN); break;
        case('a'): this->s->setdirection(LEFT); break;
	    case('d'): this->s->setdirection(RIGHT); break;
	}
}

Coord Robot::distance(Coord rab)
{
   return Coord(rab.first - s -> body.front().first, rab.second - s -> body.front().second);
}

void Robot::onthink()
{
    auto rab = tui::get() -> game -> rabbits;
    Coord low = rab.front();
    for(auto i:rab)
    {
        if((distance(low).first*distance(low).first + distance(low).second*distance(low).second) 
            > (distance(i).first*distance(i).first + distance(i).second * distance(i).second))
        {
            low = i;
        }
    }
    if(distance(low).first*distance(low).first > distance(low).second*distance(low).second)
    {
        if(distance(low).first > 0)
            s -> setdirection(RIGHT);
        else
            s -> setdirection(LEFT);
    }
    else
    {
        if(distance(low).second > 0)
            s -> setdirection(DOWN);
        else
            s -> setdirection(UP);
    }
    
	Coord head = s -> body.front();
    Coord next_to_head = *(++(s -> body.begin()));
	switch(s -> dir)
	{
		case(RIGHT): head.first++; break;
		case(LEFT): head.first--; break;
		case(DOWN): head.second++; break;
		case(UP): head.second--; break;
	} 
	auto v = tui::get();
    std::list<Snake*> sn = tui::get() -> game -> snakes;
    //for(auto i : sn)
    //    if(find(i -> body.begin(), i -> body.end(), head) != body.end() && this -> body.front() != i -> body.front())
    //    {
    //            SnakeDath = true;
    //            return;
    //    }
    if(find(++(s -> body.begin()), s -> body.end(), head) != s -> body.end() || head.first == 0 ||
             head.first == tui::get() -> MinX() || head.second == tui::get() -> MinY() || head.second == 0)
    {
        if(s -> dir == LEFT || s -> dir == RIGHT)
            s -> setdirection((rand() % 2 == 0)?UP:DOWN);
        else
            s -> setdirection((rand() % 2 == 0)?LEFT:RIGHT); 
    }
}

Robot::Robot(Snake* s) : Control(s)
{
    tui::get() -> setonAI(this);
}
