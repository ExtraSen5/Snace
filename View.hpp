#ifndef VIEW_HPP
#define VIEW_HPP

#include "Game.hpp"
#include "Control.hpp"
#include "keypressable.hpp"

class View
{
protected:
	// use std::list;
	std::pair<int, std::function<void(Game *)> > ontimer;
public:	
	keypressable * sub;
    Robot * AId;
	Game * game;
	void getontimer(int time, std::function<void(Game *)> timeout);
	void virtual setonkey(ConMan * p) = 0;
    void virtual setonAI(Robot* R) = 0;
	void virtual Draw() = 0;
	void virtual Run() = 0;
	void virtual Clear() = 0;
	void virtual gotoxy(int x, int y, char toprt) = 0;
	void virtual SnakePainter(Coord a, Dir b) = 0;
	void virtual RabbitPainter(Coord a) = 0;
	void virtual ReDraw() = 0;
    short unsigned virtual MinX() = 0;
    short unsigned virtual MinY() = 0;
	virtual ~View() {}
};

#endif
