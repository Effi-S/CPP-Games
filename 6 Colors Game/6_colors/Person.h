//this is the person class derrived from player 
//this is a player that each turn gets a color choice from the user.

#pragma once
#include "Player.h"
class Person :
	public Player
{
public:
	Person() = default;
	~Person() = default;
	Person(ShapeCell * starter) : Player(starter) {}
	void move(sf::Color);
	void iWin()const;
};

