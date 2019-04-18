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


