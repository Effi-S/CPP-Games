//this is a simple arrow 
//derrived from Abstract Weapon 
#pragma once
#include "AbstractWeapon.h"


class SimpleArrow : public AbstractWeapon
{
public:	
	SimpleArrow(sf::Vector2f pos);
	~SimpleArrow() = default;

private:
	
};
