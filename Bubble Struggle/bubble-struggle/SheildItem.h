//this is the sheild item derrived from AbstractItem 
//this item gives the player a sheild.
#pragma once
#include "AbstractItem.h"
class SheildItem :
	public AbstractItem
{
public:
	SheildItem(sf::Vector2f pos);
	~SheildItem();
	virtual void collide(class Player & p) override ;
private:
	static bool m_reg;// registration
};

