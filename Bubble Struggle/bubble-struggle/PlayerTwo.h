#pragma once
#include "Player.h"
class PlayerTwo :public Player
{
public:
	
	
	
	PlayerTwo();	
	virtual void collide(class Moveable & other) override ;
	virtual void collide(class Unmoveable & other) override;
	~PlayerTwo();
private:
	
};

