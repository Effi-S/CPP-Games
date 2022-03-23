//*************Guard class*****************
//this is the guard class 
//it is a purely virtual class derived from character. 
//**************************************

//==============includes and consts============
#pragma once
#include "Character.h"
const int MOVES = 4;
//-----------------------------------------

class Guard :
	public Character
{
public:

	Guard(sf::RenderWindow & window, sf::Vector2f pos, sf::Texture * img ,
		std::vector< Placeable *> &grid , int gridX);

	virtual void collideWith(Placeable & other) {};
	virtual void collideWith(class Character & other) {};
	virtual void collideWith(class Robot& other) {};
	virtual void collideWith(class Present& other) {};

	void move(sf::Event &event);
	virtual	void move()=0;
	virtual void collideWith(class Bomb& other) ;
	void revertOrigPos();

	virtual void collide(class Robot &other);
	virtual void collide( Guard &other) {};
	virtual void collide( Character &other) {};
	

	void drawOnGrid() { m_window.draw(m_rect); };

	 void die() ;
	
	~Guard();

private:
	
	
	sf::Clock m_respawn;
};

