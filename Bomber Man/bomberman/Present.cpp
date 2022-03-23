//***************Present class******************
//this is the present class derrived 
//from placeable
//it holds a present type that it gives to the robot when it collides with it.
//**********************************************
#include "Present.h"
//==================

//====constructor==================
//window Pos and img are for Placeable constructor.
//sets the texturRect to random part of the picture
Present::Present(sf::RenderWindow & window, sf::Vector2f pos, sf::Texture * img)
:Placeable(window, pos ,img )
{
	int temp = (rand() % PRESENTS);
	(temp < PRESENTS) ? m_type = (pres_t)temp : m_type = noUp_t; // randomly makes present
	

	m_rect.setTextureRect(sf::IntRect(m_image->getSize().x /PRESENTS *m_type,
		0, m_image->getSize().x /PRESENTS,
		m_image->getSize().y));

}
//-----------------------------
//============robot collision=============
void Present::collideWith(Robot & other)
{
	other.collideWith(*this);

	m_type = noUp_t;
}
//======================================
//==========same as base ====
void Present::drawOnGrid()
{
	if (m_type >= PRESENTS)return;//just incase

		m_window.draw(m_rect);
}
//--------------------------

//returns the present type
pres_t Present::getType() const
{
	return m_type;
}
//--------------------
//----------------------
Present::~Present()
{
}
///---------------------