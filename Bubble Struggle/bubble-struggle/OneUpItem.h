#pragma once
//this is a one up item derrived from 
//Abstract item 
//for adding a life to the player
#include "AbstractItem.h"

class OneUpItem :
	public AbstractItem
{
public:
	OneUpItem(sf::Vector2f pos);
	virtual void collide(class Player & p) override ;
	~OneUpItem();
private:
	static bool m_reg;// registration 
};

