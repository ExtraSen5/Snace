#include <iostream>
#include "Game.hpp"
#include "tui.hpp"

void Game::visitS(SnakePainter p)
{
	bool first;
	for(const auto &s: snakes)
	{
		first = true;
		for(const auto &c: s -> body)
		{
			if(first)
			{
				p(c, s -> dir);
			}
			else
				p(c, NO);
			first = false;
		}

	}
}

void Game::visitR(RabbitPainter p)
{
	for(const auto &s: rabbits)
		p(s);	
}

void Game::add(Snake * p)
{
	snakes.push_back(p);
}

Snake::Snake()
{
	dir = RIGHT;
	body.push_back(Coord(20,10));
	body.push_back(Coord(19,10));
	body.push_back(Coord(18,10));
	body.push_back(Coord(17,10));
	body.push_back(Coord(16,10));
	body.push_back(Coord(15,10));
	body.push_back(Coord(14,10));
}

void Game::newRab()
{
	auto v = tui::get();
	auto t = *(tui*)v;
	rabbits.push_back(Rabbit(rand()%(t.MinX() - 3) + 2,
				rand()%(t.MinY() - 3) + 2));

}

Game::Game(int RebNum = 0)
{
	for(int i = 0; i < RebNum; i++)
		newRab();
}

void Game::move()
{
	for(const auto s: snakes)
	{
		s -> move();
	}
}

void Snake::move()
{
	auto head = body.front();
	switch(dir)
	{
		case(RIGHT): head.first++; break;
		case(LEFT): head.first--; break;
		case(DOWN): head.second++; break;
		case(UP): head.second--; break;
	}
	body.push_front(head);
	auto v = tui::get();
	auto g = [v,head]()
	{
		for(auto i = v -> game -> rabbits.begin();i != v -> game -> rabbits.end();i++)
			if(*i == head)
				return true;
		return false;

	};
	if(g())
	{
		v -> game -> rabbits.remove(head);
		v -> game -> newRab();
	}
	else
		body.pop_back();
}

void Snake::setdirection(Dir d)
{
	dir = d;
}
