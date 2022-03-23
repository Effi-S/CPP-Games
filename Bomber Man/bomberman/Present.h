//***************Present class******************
//this is the present class derrived 
//from placeable
//it holds a present type that it gives to the robot when it collides with it.
//**********************************************
//-------includes--------
#pragma once
#include "CONSTS.h"
#include "Placeable.h"
#include "Robot.h"
//--------------------

class Present :
	public Placeable
{
public:
	Present(sf::RenderWindow &window, sf::Vector2f pos , sf::Texture * img);
	virtual void collideWith(class Character & other) {};
	virtual void collideWith(class Robot & other);
	virtual void collideWith(class Bomb & other) { };
	virtual void collideWith(class Present& other) { };
	void drawOnGrid();


	pres_t getType() const; 

	~Present();

private:
	pres_t m_type;
};

