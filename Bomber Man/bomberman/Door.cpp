
//*******
//this is the Door class derrived from 
//when collides with robot 
//it changes the texture rect 
//to the second half of the image and sends the robot a collision
//otherwise displays only the first half
//**********
//=========include section ==========
#include "Door.h"
#include "Robot.h"
#include <unistd.h>
//======================

//====constructor==================
//window Pos and img are for Placeable constructor.
//sets the texturRect to first half of the picture
Door::Door(sf::RenderWindow &window, sf::Vector2f Pos ,  sf::Texture * img)
	:Placeable(window, Pos , img)
{
	m_rect.setTextureRect(sf::IntRect(0.f, 0.f,
		m_image->getSize().x / 2,
		m_image->getSize().y));

	m_empty = true;
}
//=================================

//===================================
//collision with robot
//sets the texture rect to second half 
//and titnts yellow.
void Door::collideWith(Robot & other)
{
	m_rect.setFillColor(sf::Color::Yellow);

	m_rect.setTextureRect(sf::IntRect(m_image->getSize().x / 2, 0.f,
		m_image->getSize().x / 2,
		m_image->getSize().y));

	m_window.clear();

	m_window.draw(m_rect);

	usleep(500 * 1000);

	other.collideWith(*this);

}
//--------------------------------------------

Door::~Door()
{
}


