#pragma once
//this is an item class derrived 
//from abstract Item
//gives the player a Laserweapon.
#include "AbstractItem.h"
class LaserItem :
	public AbstractItem
{
public:
	LaserItem(sf::Vector2f pos);
	~LaserItem();
	virtual void collide(class Player & p) override;
private:
	static bool m_reg;
};

