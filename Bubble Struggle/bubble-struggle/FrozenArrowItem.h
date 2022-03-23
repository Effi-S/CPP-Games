//this is an item derived from Abstract Item 
//it gives the player a frozen arrow upgrade.
#pragma once
#include "AbstractItem.h"
class FrozenArrowItem :
	public AbstractItem
{
public:
	FrozenArrowItem(sf::Vector2f pos);
	~FrozenArrowItem();
	virtual void collide(class Player & p) override ;
private:
	static bool m_reg;//registration.

};

