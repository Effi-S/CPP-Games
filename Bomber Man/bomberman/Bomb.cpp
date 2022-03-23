//**************Bomb class**************
//this is the Bomb class derrived from Placeable 
//it holds a rectangle and a reference to a window 
//so that it can print the rectangle to the screen
//it is dorment until planted then it waits 5 seconds and then explodes 
//itself and the cells it is given when planted
//***************************************
//==========include section==========
#include "Bomb.h"
#include "Character.h"
//===================================

//=========constructor======================
//window img are for Placeable constructor
//the chars is a vector of characters for checking collisions
//the info is for updating the amount of bombs left once 
//planted on the screen.
Bomb::Bomb(sf::RenderWindow &window, sf::Texture * img, std::vector<Character *> &chars ,gameInfo & info)
	:Placeable(window , sf::Vector2f() , img ), m_chars(chars) ,m_gameInfo(info)
{
	m_rect.setTextureRect(sf::IntRect(0.f
		, m_image->getSize().x / 6 * 5,
		m_image->getSize().x / 6 ,
		m_image->getSize().y )
	);
	
	m_countdown.restart();
	
	m_planted = false;

}
//========================================
void Bomb::collideWith(Guard & other)
{
	m_gameInfo.score += m_chars.size();
}

//======================================
//here the Bomb decides what time 
//it will display and wheather it needs to blow.
void Bomb::drawOnGrid()
{	
	if (!m_planted) return;

	if (m_blown)
	{
		m_rect.setTextureRect(sf::IntRect(m_image->getSize().x / 6 *(5)
			, 0.f, m_image->getSize().x / 6, m_image->getSize().y));

		m_window.draw(m_rect);

		for (size_t i = 0; i < m_adjacents.size() ;i++)
		{
			sf::RectangleShape rect (m_rect);
			rect.setPosition(m_adjacents[i]->getPos());

			m_window.draw(rect);
			
		}

		return;
	}	

	m_window.draw(m_rect);
	
	 if ((int)m_countdown.getElapsedTime().asSeconds() == 5)
		MainBlow();			
	

	else if ((int)m_countdown.getElapsedTime().asSeconds() >= 6)
	{
		m_blown = true; 
	}
	 m_rect.setTextureRect(sf::IntRect(m_image->getSize().x / 6 * ((int)m_countdown.getElapsedTime().asSeconds())
		 , 0.f, m_image->getSize().x / 6, m_image->getSize().y));
	
}
//===================================================
//-------------------------------
void Bomb::shade()
{
	m_blown = true;
	
	Placeable::shade();

}
//-------------------------------

//-------------------------------
//returns if planted or not.
bool Bomb::planted() const
{
	return m_planted;
}
//-------------------------
//returns if blown or not.
bool Bomb::blown() const
{
	return m_blown;
}
//-------------------------
//this is the bomb planting 
//function it receives all of the cells the bomb can effect into 
//Adjaceants and its postion  on the window into place
void Bomb::Plant( std::vector<Placeable *> &Adjacents)
{
	if (m_gameInfo.bombs > 0)
		m_gameInfo.bombs--;

	m_adjacents = Adjacents;

	m_rect.setPosition(m_chars[0]->getPos());

	m_countdown.restart();


	m_planted = true;
}
//============================
//blows a particular ccell on the grid 
// presenting a recoil image and checking for collisions.
void Bomb::Blow(sf::Vector2f place)
{
	sf::RectangleShape temp;

	temp.setSize(m_rect.getSize());

	temp.setPosition(place); 

	temp.setTexture(m_rect.getTexture());

	temp.setTextureRect(m_rect.getTextureRect());

	m_image->setRepeated(true);

	m_window.draw(temp);

	for (size_t i = 0; i < m_chars.size(); i++)
	{
		if (temp.getGlobalBounds().intersects(m_chars[i]->getGlobalBoundrie()))
			m_chars[i]->collideWith(*this);
	}


	
}
//==========================

//===========the main bomb blow 
//sends all of the cells it can effect a Blow function.
void Bomb::MainBlow()
{	
	for (size_t i = 0; i < m_adjacents.size(); i++)
		Blow( m_adjacents[i]->getPos());

	Blow(m_rect.getPosition());

	for (int i = 0; i < m_adjacents.size(); i++)
	{
		m_adjacents[i]->collideWith(*this);
	}

	
}
//------------------
//------------------
Bomb::~Bomb()
{
}
//-----------------