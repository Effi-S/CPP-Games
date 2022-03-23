//this is the frozen weapon derrived from abstractWeapons
//it is a weapon that stayes put once hitting a wall 
//unless the user creates a new arrow or a ball hits the frozen arrow.
#pragma once
#include "AbstractWeapon.h"
class FrozenWeapon :
	public AbstractWeapon
{
public:
	FrozenWeapon(sf::Vector2f pos);
	~FrozenWeapon();
	virtual void update(float delta) override;
	void collide(class Wall & wall) override;
	void collide(class Spikes & spikes) override;
private:

	sf::Clock m_notMovingTimer;// after a while the frozen arrow is removed.
	bool m_moving = true; // for^^

};

