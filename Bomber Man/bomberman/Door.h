//*******
//this is the Door class derrived from 
//when collides with robot 
//it changes the texture rect 
//to the second half of the image and sends the robot a collision
//otherwise displays only the first half
//**********
//===includes====
#pragma once
#include "Placeable.h"
//===================

class Door :
	public Placeable
{
public:
	Door(sf::RenderWindow &window, sf::Vector2f Pos ,  sf::Texture * img);
	
	virtual void collideWith(class Character & other) { };
	virtual void collideWith(class Robot & other);
	virtual void collideWith(class Bomb& other) { };
	virtual void collideWith(class Present& other) {};
	void drawOnGrid() { m_window.draw(m_rect); };

	~Door();
private:
	
};

