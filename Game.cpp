#include <iostream>
#include <algorithm>
#include "Game.hpp"
#include "tui.hpp"

#define MAX_TIME 100

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
				p(c, s -> dir, s -> coller);
                
			}
			else
				p(c, NO, s -> coller);
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
    coller = "\x1b[0m";
    SnakeDath = false;
	dir = RIGHT;
	body.push_back(Coord(20,20));
}

void Game::newRab()
{
	auto v = tui::get();
	auto t = *(tui*)v;
	rabbits.push_back(Rabbit(rand()%(t.MinX() - 3) + 1,
        rand()%(t.MinY() - 3) + 1));
}

Game::Game(int RabNum = 0)
{
	this -> RabNum = RabNum;
	for(int i = 0; i < RabNum; i++)
		newRab();
	tui::get() -> setOnTimer(MAX_TIME, std::bind(&Game::move, this));
}

void Game::move()
{
	tui::get() -> setOnTimer(MAX_TIME, std::bind(&Game::move, this));
	for(const auto s: snakes)
	{
		if(s -> SnakeDath)
			continue;
		s -> move();
		if(RabNum != rabbits.size())
			newRab();
	}
}

void Snake::move()
{
	Coord head = body.front();
	Coord copy = body.front();
	Coord next_to_head = *(++body.begin());
	switch(dir)
	{
		case(RIGHT): head.first++; break;
		case(LEFT): head.first--; break;
		case(DOWN): head.second++; break;
		case(UP): head.second--; break;
	}
	switch(dir)
	{
		case(RIGHT): copy.first--; break;
		case(LEFT): copy.first++; break;
		case(DOWN): copy.second--; break;
		case(UP): copy.second++; break;
	}
	if(head == next_to_head)
	{
		head = copy;
		dir = last_dir;
	}

	auto v = tui::get();
	std::list<Snake*> sn = tui::get() -> game -> snakes;
	for(auto i : sn)
		if(find(i -> body.begin(), i -> body.end(), head) != i -> body.end() && this -> body.front() != i -> body.front())
		{
			SnakeDath = true;
			coller = "\x1b[0m";
			return;
		}
	if(find(v -> game -> rabbits.begin(), v -> game -> rabbits.end(), head) != v -> game -> rabbits.end())
	{
		v -> game -> rabbits.remove(head);
	}
	else if(find(++body.begin(), body.end(), head) != body.end() || head.first < 0 ||
			head.first > tui::get() -> MinX() - 3 || head.second > tui::get() -> MinY() - 3 || head.second < 0)
	{
		SnakeDath = true;
		coller = "\x1b[0m";
		return;
	}
	else
		body.pop_back();
	body.push_front(head);
}

void Snake::setdirection(Dir d)
{
	last_dir = dir;
	dir = d;
}

void Snake::Spos(Coord c)
{
	body.pop_front();
	body.push_front(c);
}
