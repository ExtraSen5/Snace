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
	
	struct termios term;
	tcgetattr(1, &term);
	cfmakeraw(&term);
	tcsetattr(1,TCSANOW ,&term);

	signal(SIGWINCH, sigdr);
	Game g(7);
    Snake s;
    ConMan h(&s);

    Snake Rs;
    Rs.Spos(Coord(20, 23));
    Robot r(&Rs);
    g.add(&s);
    g.add(&Rs);
    View * v = tui::get();
    v -> game = &g;
    //v -> setontimer(500, std::bind(Game::move(), this);
    v -> Draw();
    v -> Run();
    
    pid_t f = fork(); 
    if(f == 0)
    {
        execlp("stty", "stty", "sane", NULL);
        perror(strerror(errno));
        return 0;
    }
    waitpid(f, NULL, 0);
    return 0;

}
