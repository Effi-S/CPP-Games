//this is the spikes clas 
//derrived from Unmoveable this class 
//is a vertical unmoveable rectangle shape that 
//when colliding with almost all balls 
//should lead to their removall.

#pragma once
#include "Unmoveable.h"



class Spikes : public Unmoveable
{
public:
	Spikes(float y=15.f);
	~Spikes() = default;

	virtual void collide(class Moveable & other);
	virtual void collide(class Player & other) ;
private:
	static bool m_reg;//registration 
	
};

