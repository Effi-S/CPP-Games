//this is the moveable class 
//a base class for any moving object 
//derrived from Drawable.
#pragma once
#include "Drawable.h"
#include <string>


class Moveable : public Drawable
{
public:
	Moveable() = default;
	~Moveable() = default;

	virtual void update(float delta) = 0;
	virtual void collide(class Moveable & other) =0;
	virtual void collide(class Unmoveable & other) =0;

	virtual void collide(class Wall & other) { };
	virtual void collide(class Spikes & other) { };
	virtual void collide(class Player & other) { };
	virtual void collide(class AbsBall & other) { };
	void collide(class Sheild & other ) { };
	virtual void collide(class AbstractWeapon & other) { };

	

	



	
};


