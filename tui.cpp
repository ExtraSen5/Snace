#include <termios.h>
#include <sys/ioctl.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <poll.h>
#include <time.h>
#include "tui.hpp"
#include "Control.hpp"
#include "Game.hpp"

#define MAX_TIMER 100

using namespace std::placeholders;

void tui::Clear()
{
	printf("\e[H\e[J");
}

unsigned short tui::MinX()
{
	int fd = 1;
	struct winsize argp;
	ioctl(fd,TIOCGWINSZ,&argp);
	return argp.ws_col;
}

unsigned short tui::MinY()
{
	int fd = 1;
	struct winsize argp;
	ioctl(fd,TIOCGWINSZ,&argp);
	return argp.ws_row;
}

void tui::DrawRow(unsigned short Y)
{
	unsigned short XSize = MinX();
	printf("\e[%d;%dH",Y,0);
	for(unsigned short i = 0; i < XSize; i++)
		printf("#");
}

void tui::DrawCol(unsigned short X)
{
	unsigned short YSize = MinY();
	for(unsigned short i = 0; i < YSize; i++)
	{
		printf("\e[%d;%dH",i,X);
		printf("#");
	}
}

tui::tui()
{}

tui::~tui()
{}

void tui::Draw()
{
	auto Y_MAX = MinY();
	auto X_MAX = MinX();
	Clear();
	DrawCol(0);
	DrawRow(0);
	DrawRow(Y_MAX);
	DrawCol(X_MAX);

	/*
	gotoxy(0,0,'1');
	gotoxy(X_MAX - 3,0,'2');
	gotoxy(X_MAX - 3,Y_MAX - 3,'3');
	gotoxy(0,Y_MAX - 3,'4');
	*/

	game -> visitR(std::bind(&tui::RabbitPainter, this, _1));
	game -> visitS(std::bind(&tui::SnakePainter, this, _1, _2));
	printf("\e[H");
	fflush(stdout);
}
void tui::setonkey(ConMan * data)
{
	sub = data;
}

void tui::Run()
{
	struct pollfd k = {1, POLLIN, 0};
	struct timespec totime;
	while(1)
	{
		clock_gettime(NULL, &totime); 
		int t1 = totime.tv_sec;
		if(poll(&k, 1, ontimer.first))
		{
			char ComeData;
			read(1, &ComeData, 1);
			if(ComeData == 'e')
				break;
			sub -> onkey(ComeData);

			clock_gettime(NULL, &totime); 
			int t2 = totime.tv_sec;
			ontimer.first -= (t2 - t1 > 0)?(t2 - t1):0;

		}
		else
		{
            AId -> onthink();
			ontimer.first = MAX_TIMER;
			//tui::get() -> game -> ontimer.second();
			game -> move();
			Draw();
		}
	}
	Clear();
	std::cout << "Good bye!" << std::endl;
}

View * tui::get()
{
	static tui OneData;
	return &OneData;
}

void tui::gotoxy(int x, int y, char toprt)
{
	printf("\e[%d;%dH",y + 2, x + 2);
	printf("%c", toprt);	
}
void View::getontimer(int time, std::function<void(Game*)> timeout)
{
	ontimer.first = time;
	ontimer.second = timeout;
}
void tui::ReDraw()
{
	
}
