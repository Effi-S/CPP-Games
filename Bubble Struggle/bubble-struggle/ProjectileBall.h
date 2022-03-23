//this is a ball derrived from 
//AbsBall this is the size of 20 radius 
//is shot at the positon given and then when hits an oject 
//splits into 2 balls size 10.
#pragma once
#include "AbsBall.h"


class ProjectileBall:
	public AbsBall
{
public:
	ProjectileBall(sf::Vector2f StartPos , sf::Vector2f TargetPos = sf::Vector2f(0.f,600.f));
	virtual float Gravity() const { return 0; };
	virtual void split();
	void collide(class Wall & wall);
	sf::Vector2f claculateDirection(sf::Vector2f start , sf::Vector2f target);
	~ProjectileBall();
private:
	
	unsigned m_speedOfMovement = 7;// constant speed of movement.
};

