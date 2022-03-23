//*********************
//this is the placeable pure virtual class
//it holds a posistion in the window 
//and a rectangle that it can print to the screen
//*************************

//----includes-------
#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "CONSTS.h"
//-----------------------

class Placeable
{

public:
	Placeable(sf::RenderWindow &window,
		sf::Vector2f pos = (sf::Vector2f(0, 0)),
		sf::Texture *img = &sf::Texture(),
		sf::RectangleShape rect = sf::RectangleShape()
	);

	void drawOnGrid(sf::View  &minimapView);
	virtual void drawOnGrid() = 0;

	virtual void revertOrigPos();

	virtual void collideWith(class Character & other) = 0;
	virtual void collideWith(class Robot& other) = 0;
	virtual void collideWith(class Bomb& other) = 0;
	virtual void collideWith(class Present& other) = 0;
	
	sf::FloatRect getGlobalBoundrie() const;
	sf::Vector2f getPos() const;

	int getXpos() const;
	int getYpos() const;

	bool isEmpy() const;
	void shade() { m_rect.setFillColor(sf::Color(255, 255, 255, 20)); };
	void unShade() { m_rect.setFillColor(sf::Color::White); };

	void inputPlace(int place); //for Bfs
	int getplace();  //for Bfs

	~Placeable();

protected:
	sf::Texture * m_image;
	
	sf::RectangleShape m_rect;

	sf::RenderWindow &m_window;

	int m_place;//place in bfs list.

	sf::Vector2f m_origPos;
	
	bool m_empty = true;
	
private:

	
	
};

