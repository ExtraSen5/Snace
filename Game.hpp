#ifndef GAME_HPP
#define GAME_HPP

#include <list>
#include <utility>
#include <functional>
#include <vector>
enum Dir
{
	NO,
	UP, 
	DOWN,
	LEFT,
	RIGHT	
};

using Coord = std::pair<int,int>;
using Rabbit = Coord;
using SnakePainter = std::function<void(Coord, Dir)>;
using RabbitPainter = std::function<void(Coord)>;

class Control;
class Snake
{
public:
    bool SnakeDath;
	void move();
    void Spos(Coord);
	void setdirection(Dir d);
	Snake();
	std::list <Coord> body;
	Dir dir;
    Dir last_dir;	
};

class Game
{
    int RabNum; 
public:
	std::list<Snake*> snakes;
	std::list<Rabbit> rabbits;

	void move();
	void add(Snake * p);
	void newRab();
	void visitS(SnakePainter p);
	void visitR(RabbitPainter p);
	Game(int);
};

 #endif
