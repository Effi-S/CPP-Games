//this a useful list of registration functions for the drawable factory
//one does not have to use these but the come in handy.

#pragma once
#include "DrawableFactory.h"
#include "Board.h"
#include "Door.h"

namespace{

template<class T>
void addAbsball(ObjInfo info, Board & board)
{
	if (info._x2 > 0 && info._x3 > 0)
		board.add(std::make_shared<T>(info._x1, sf::Vector2f(info._x2, info._x3)));
	else
		board.add(std::make_shared<T>(info._x1));

	
}

template<class T>
void addWeapon(ObjInfo info, Board & board)
{
	board.add(std::shared_ptr< T >());
}

template<class T>
void addFollowingBall(ObjInfo info, Board & board)
{
	
	if (info._x1 > 0 && info._x2 > 0)
		board.add(std::make_shared<T>( sf::Vector2f(info._x1, info._x2)));
	else
		board.add(std::make_shared<T>());

}

template <class T>
void makeDoor(ObjInfo info, Board & board)
{	
	auto door=std::make_shared<Door>(sf::Vector2f(info._x1, info._x2), sf::Vector2f(info._x3, info._x4));
	door->makeBall<T>();
	board.add(door);
}

template <class T>
void makeFollowDoor(ObjInfo info, Board & board)
{
	auto door = std::make_shared<Door>(sf::Vector2f(info._x1, info._x2), sf::Vector2f(info._x3, info._x4));
	door->makeFollowBall<T>();
	board.add(door);
}


template<class T>
void addStationary(ObjInfo info, Board & board)
{
	board.add(std::make_shared<T>(sf::Vector2f(info._x1, info._x2), sf::Vector2f(info._x3, info._x4)));

}

void addSpikes(ObjInfo info, Board & board)
{
	if (info._x1 > 0)
		board.add(std::make_shared<Spikes>(info._x1));
	else
		board.add(std::make_shared<Spikes>());
}

template<class T>
void addItem(ObjInfo info, Board & board)
{
	board.add(std::make_shared<T>(sf::Vector2f(info._x1, info._x2)));
}

}

