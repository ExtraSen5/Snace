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
	void virtual SnakePainter(Coord a, Dir b)
	{
		gotoxy(a.first, a.second, "o^v<>"[b]);
	}
	void virtual RabbitPainter(Coord a)
	{
		gotoxy(a.first, a.second, '@');
	}
    void setonAI(Robot* R)
    {  
        AId = R;
    }
	void gotoxy(int x, int y, char toprt);
	void Run();
	void ReDraw();
	~tui();
};

#endif
