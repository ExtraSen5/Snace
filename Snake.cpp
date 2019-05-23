#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "Game.hpp"
#include "tui.hpp"
#include "Control.hpp"
/*
 *#####################
 *#                   #
 *#     ******>       #
 *#     *             #
 *#  ****             #
 *#            @      #
 *#                   #
 *#                   #
 *#####################
 */
/*
void sigdr (int x)
{
	View * v = tui::get();
	v -> Draw();
}
*/

int main()
{
	auto sigdr = [](int x)
	{
		View * v = tui::get();
		v -> Draw();
	};

	srand(time(NULL));
	struct termios term, copy_term;
	tcgetattr(1, &term);
	copy_term = term;
	cfmakeraw(&term);
	tcsetattr(1,TCSANOW ,&term);
	signal(SIGWINCH, sigdr);

	Game g(20);
	Snake s;
	s.setColler(31);
	ConMan h(&s);

	Snake Rs1;
	Rs1.setColler(32);
	Rs1.Spos(Coord(20, 40));
	Robot r1(&Rs1);

	Snake Rs2;
	Rs2.setColler(33);
	Rs2.Spos(Coord(100,20));
	Robot r2(&Rs2);

	Snake Rs3;
	Rs3.setColler(34);
	Rs3.Spos(Coord(100,40));
	Robot r3(&Rs3);

	g.add(&s);
	g.add(&Rs1);
	g.add(&Rs2);
	g.add(&Rs3);

	View * v = tui::get();
	v -> game = &g;
	
	v -> Draw();
	v -> Run();

	tcsetattr(1,TCSANOW,&copy_term);
	return 0;
}
