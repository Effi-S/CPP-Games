#pragma once
//this is an item derrived from AbstracItem 
//gives the player a Simple Arrow.
#include "AbstractItem.h"

class SimpleArrowItem :
	public AbstractItem
{
public:
	SimpleArrowItem(sf::Vector2f pos);
	~SimpleArrowItem();

	virtual void collide(class Player & p) override ;
private:
	static bool m_reg;
};

