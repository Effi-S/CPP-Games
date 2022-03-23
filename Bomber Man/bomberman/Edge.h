//***********this is the edge class******************
//this class is derrived from the Placeable base class
//no real functionality apart from blocking any character from entering it.

//**********************************************
//--------includes-------
#pragma once
#include "Placeable.h"
//---------------------

class Edge :
	public Placeable
{
public:
	Edge(sf::RenderWindow &m_window, sf::Vector2f pos , sf::Texture * img);
	virtual void collideWith(class Character & other) {};
	virtual void collideWith(class Robot& other) {};
	virtual void collideWith(class Bomb& other) { };
	virtual void collideWith(class Present& other) {};
	void drawOnGrid() { m_window.draw(m_rect); };

	~Edge();
};

