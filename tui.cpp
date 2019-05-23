#include <signal.h>
#include <termios.h>
#include <time.h>
#include <sys/ioctl.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <poll.h>
#include <sys/time.h>
#include "tui.hpp"
#include "Control.hpp"
#include "Game.hpp"

#define MAX_TIMER 100

View * itis_ = nullptr;

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
		printf("\x1b[36m%c\x1b[0m", '#');
}

void tui::DrawCol(unsigned short X)
{
	unsigned short YSize = MinY();
	for(unsigned short i = 0; i < YSize; i++)
	{
		printf("\e[%d;%dH",i,X);
		printf("\x1b[36m%c\x1b[0m", '#');
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
	game -> visitS(std::bind(&tui::SnakePainter, this, _1, _2, _3));
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
	struct timeval t1, t2;
	while(1)
	{
		gettimeofday(&t1, NULL);
		if(poll(&k, 1, OnTime().first))
		{
			char ComeData;
			read(1, &ComeData, 1);
			if(ComeData == 'e')
				break;
			sub -> onkey(ComeData);

			gettimeofday(&t2, NULL);
			ontimer.first -= (t2.tv_sec-t1.tv_sec)*1000+(t2.tv_usec-t1.tv_usec)/1000;
			if(ontimer.first < 0)
				ontimer.first = 0;

		}
		else
		{
			for(auto item: AIds)
				item -> onthink();
			OnTime().second();
			//game -> move();
			Draw();
		}
	}
	Clear();
	std::cout << "Good bye!" << std::endl;
}

View * tui::get()
{
	if(itis_ == nullptr)
		itis_ = new tui;
	return itis_;
}

void tui::gotoxy(int x, int y, char toprt, std::string coller)
{
	printf("\e[%d;%dH",y + 2, x + 2);
	printf("%s%c\x1b[0m",coller.c_str(), toprt);	
}
