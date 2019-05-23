#ifndef VIEW_HPP
#define VIEW_HPP

#include <termios.h>
#include "Game.hpp"
#include "Control.hpp"
#include "keypressable.hpp"

using TimeOutCost = std::function<void()>;

class View
{
	protected:
		std::pair<int, TimeOutCost> ontimer;
	public:	
		void setOnTimer(int time, TimeOutCost act)
		{
			ontimer.first = time;
			ontimer.second = act;
		}
		std::pair<int, TimeOutCost> OnTime() { return ontimer; }
		keypressable * sub;
		std::list<Robot *> AIds;
		Game * game;
		void getontimer(int time, std::function<void(Game *)> timeout);
		void virtual setonkey(ConMan * p) = 0;
		void virtual setonAI(Robot* R) = 0;
		void virtual Draw() = 0;
		void virtual Run() = 0;
		void virtual Clear() = 0;
		void virtual gotoxy(int x, int y, char toprt, std::string coller) = 0;
		void virtual SnakePainter(Coord a, Dir b, std::string coller) = 0;
		void virtual RabbitPainter(Coord a) = 0;
		short unsigned virtual MinX() = 0;
		short unsigned virtual MinY() = 0;
		virtual ~View() {}
};

#endif
