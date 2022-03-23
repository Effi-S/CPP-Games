//*********************
//this is the placeable pure virtual class
//it holds a posistion in the window 
//and a rectangle that it can print to the screen
//*************************

#include "Placeable.h"

//================================
//receives a render window into window 
//for printing itself onto
//receives a vector2f into pos for positioning itself on said window
//it can also receive the rectangle already made.
Placeable::Placeable(sf::RenderWindow &window, sf::Vector2f pos ,
	sf::Texture *img, sf::RectangleShape Rect)
	:m_window(window) , m_rect(Rect), m_origPos(pos) ,m_image(img)
{
	m_empty = true;
		
	sf::RectangleShape rect;

	rect.setSize(CELLSIZE);

	rect.setOutlineColor(sf::Color::Color(216, 216, 255, 216));

	rect.setTexture(img);
	
	rect.setPosition(pos);

	m_rect = rect;

	
}
//==============================

//====drawing the rectangle onto the grid================
void Placeable::drawOnGrid(sf::View & minimapView)
{
	
	if (isEmpy())		
		return;
	
			
	m_window.draw(m_rect);
	
}
//-------------------------------------------

//===returns the bounds of the rectangle.
sf::FloatRect Placeable::getGlobalBoundrie() const
{
		return m_rect.getGlobalBounds();
}
//-------------------------------------
//========================
//returns the postion of the rectangle
sf::Vector2f Placeable::getPos() const
{
	return m_rect.getPosition();
}
//------------------------------
//returns the X postion of the placeable.
int Placeable::getXpos() const
{
	return m_rect.getPosition().x;
}
//----------------

//returns the Y position of the rectangle
int Placeable::getYpos() const
{
	return m_rect.getPosition().y;
}
//-------------------------

//reverts the postion of the rectangle back to its original position
void Placeable::revertOrigPos()
{
		
		m_rect.setPosition(m_origPos);
}
//--------------------------

//returns weather or not the Placeable is 
//empty for the characters to move on them
bool Placeable::isEmpy() const
{
	return m_empty;
}
//----------------------------

//these functions are for the bfs 
//to enter a place in the bfs list
//and returning it
//---
//entering
void Placeable::inputPlace(int place)
{
	m_place = place;
}
//---
//returning said place.
int Placeable::getplace()
{
	return m_place;
}
//================================

//-----------------------------
Placeable::~Placeable()
{
}
//----------------------------

