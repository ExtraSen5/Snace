#ifndef GAME_HPP
#define GAME_HPP

#include <list>
#include <utility>
#include <functional>
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
	void move();
	void setdirection(Dir d);
	Snake();
	std::list <Coord> body;
	Dir dir;	
};

class Game
{
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
