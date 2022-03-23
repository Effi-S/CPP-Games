#pragma once
//this is an item for giving the player 
//more time to complete the level
#include "AbstractItem.h"
class TimeItem :
	public AbstractItem
{
public:
	TimeItem(sf::Vector2f pos);
	virtual void collide(class Player & p) override ;
	~TimeItem();
private:
	static bool m_reg;// registration 
};


