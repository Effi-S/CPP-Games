#pragma once
#include "Player.h"
class PlayerOne :public Player
{
public:
	
	
	
	virtual void collide(class Moveable & other) override { other.collide(*this); };
	virtual void collide(class Unmoveable & other) override ;
	PlayerOne();
	~PlayerOne();
private:
	
};

