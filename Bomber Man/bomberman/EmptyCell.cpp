//*********************EmptyCell************
//this is the emptyCell class
//it randomly generates a background from the img it receives 
//and can hold a present 
//has no other functionality other than allowing character movement into 
//its space.
//******************************************

//------includes---------
#include "EmptyCell.h"
//--------------------

//============constructor==================
//window Pos and img are for Placeable constructor.
//sets the texturRect to random part of the picture.
EmptyCell::EmptyCell(sf::RenderWindow & window, sf::Vector2f Pos, sf::Texture * img , sf::Texture * presImg, bool Pres)
	:Placeable(window,Pos,img) ,m_hasPres(Pres)
{
	m_empty = true;
	if (m_hasPres)
		addPres(presImg);

	setBkg();
}
//---------------------

//===========================
void EmptyCell::collideWith(Robot & other)
{
	if(m_hasPres)m_present->collideWith(other);
}
//=============================
void EmptyCell::drawOnGrid()
{
	m_window.draw(m_rect);

	if (m_hasPres)
		m_present->drawOnGrid();
}
//==============================
//add present function 
//this function adds a present to the emptyCell
void EmptyCell::addPres(sf::Texture * img)
{
	m_present = new Present(m_window, m_rect.getPosition(), img);

	m_hasPres = true;

}
//=========================
//no different from Placeable shade apart from shading the present ifr it has one.
void EmptyCell::shade()
{
	if (m_hasPres)
		m_present->shade();
	Placeable::shade();
}
//==========
//no different from Placeable unshade apart from unshading the present ifr it has one.
void EmptyCell::unShade()
{
	if (m_hasPres)
		m_present->unShade();
	Placeable::unShade();
}
//=================
//==================
//randomly selects a 4X4 part of the 
//bakground image to be its m_image.
void EmptyCell::setBkg()
{
	int cell = rand() % 4;

	m_rect.setTextureRect(sf::IntRect(m_image->getSize().x / 5 *cell
		, m_image->getSize().y / 4 *cell,
		m_image->getSize().x / 5,
		m_image->getSize().y / 4)
	);
}
//----------------------

//========================
//deletes present aswell
EmptyCell::~EmptyCell()
{

	delete m_present;
}
//=======================