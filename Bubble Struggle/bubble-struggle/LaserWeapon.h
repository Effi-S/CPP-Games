#pragma once
//this is a laser Weapon for the player
//serrived from Abstract Weapon
#include "AbstractWeapon.h"
#include <SFML/Graphics.hpp>

class LaserWeapon : public AbstractWeapon
{
public:
	LaserWeapon(sf::Vector2f pos);
	~LaserWeapon() = default;
	virtual void update(float delta) override;
	
private:
	 sf::Clock m_scaleClock;// for making the weapon bigger over time
	 sf::Time m_elapsed; // timing the scaling^^
};

