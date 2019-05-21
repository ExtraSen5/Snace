#ifndef TIO_HPP
#define TIO_HPP

#include "View.hpp"
#include "Control.hpp"
#include "Game.hpp"

class tui: public View
{
	void DrawRow(unsigned short Y);
	void DrawCol(unsigned short X);
	static View * OneData;
	tui();
public:
	//void getontimer(int time, std::function<void(Game*)>) = 0;
	unsigned short MinX();
	unsigned short MinY();
	static View * get();
	void setonkey(ConMan * data); 
	void Clear();
	void Draw();
	void virtual SnakePainter(Coord a, Dir b, std::string coller = "\x1b[0m")
	{
		gotoxy(a.first, a.second, "o^v<>"[b], coller);
	}
	void virtual RabbitPainter(Coord a)
	{
		gotoxy(a.first, a.second, '@', "\x1b[1m");
	}
    void setonAI(Robot* R)
    {  
        AIds.push_back(R);
    }
	void gotoxy(int x, int y, char toprt, std::string color = "\x1b[0m");
	void Run();
	~tui();
};

#endif
