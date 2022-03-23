//***********************************
//this is the stone class
//derrived from the placeable base class
//it can hold a present theat is only reveladed after 
//collision with bomb 
//collision with bomb also turns the stone 
//to an empty cell.
//**********************************
//============================
#include "Stone.h"
#include "EmptyCell.h"
//========================

//====constructor==================
//window Pos and img are for Placeable constructor.
//sets the texturRect to first half of the picture
Stone::Stone(sf::RenderWindow &window , sf::Vector2f Pos , sf::Texture * img , sf::Texture * presImg , bool Pres )
	:Placeable(window ,Pos ,img) ,m_PresImg(presImg) , m_hasPres(Pres)
{
	m_rect.setTextureRect(sf::IntRect(0, 0, 
		m_image->getSize().x / 2,
		m_image->getSize().y) );

	m_empty = false;
}


void Stone::collideWith(Robot & other)
{
	if (m_hasPres && m_empty)
	{
		m_Pres->collideWith(other);
		m_hasPres = false;
	}
}

void Stone::collideWith(Bomb & other)
{
	removeStone();
}

void Stone::revertOrigPos()
{
	m_rect.setTextureRect(sf::IntRect(0, 0,
		m_image->getSize().x / 2,
		m_image->getSize().y));

	m_empty = false;
}

void Stone::drawOnGrid()
{
	 m_window.draw(m_rect); 

	 if (m_hasPres && m_empty)
		 m_Pres->drawOnGrid();
}

void Stone::shade()
{
	if (m_hasPres)
		m_Pres->shade();
	Placeable::shade();
}

void Stone::unShade()
{
	if (m_hasPres)
		m_Pres->unShade();
	Placeable::unShade();
}


void Stone::removeStone()
{
	if(m_hasPres && !m_empty)
	m_Pres = new Present(m_window, m_rect.getPosition(), m_PresImg);

	m_empty = true;

	m_rect.setTextureRect(sf::IntRect(m_image->getSize().x / 2,
		0, m_image->getSize().x / 2,
		m_image->getSize().y));


}


Stone::~Stone()
{

}