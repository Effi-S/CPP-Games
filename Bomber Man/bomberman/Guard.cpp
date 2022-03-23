//*************Guard class*****************
//this is the guard class 
//it is a purely virtual class derived from character. 
//**************************************

//==============includes================
#include "Guard.h"
#include "Robot.h"
#include "Bomb.h"
//========================================

//-----------const section-----------
const unsigned SPAWN_TIME = 2;
//-------------------

//============constructor==================
//window Pos and img grid and gridX are for Character constructor.
Guard::Guard(sf::RenderWindow & window, sf::Vector2f pos, sf::Texture * img ,
	std::vector<Placeable *> &grid , int gridX)
	:Character(window, pos ,img , grid ,gridX )
{
	m_moveTimer.restart();
	m_respawn.restart();
	
}
//=====================================
//========================================
//collision with the robot
void Guard::collide(Robot & other)
{
	if (m_respawn.getElapsedTime().asSeconds() <= SPAWN_TIME)
		return;

	other.collide(*this);
}
//=============================
//makes sure not in the spawn time.
void Guard::move(sf::Event & event)
{
	if (m_respawn.getElapsedTime().asSeconds() <= SPAWN_TIME)
	{
		slideChange(extra_t);

		return;
	}

	move();
}
//============================
//============================
void Guard::collideWith(Bomb & other)
{
	other.collideWith(*this);

	die();
}
//===========================
//==========================
void Guard::revertOrigPos()
{
	m_respawn.restart();
	Placeable::revertOrigPos();
}
//===========================
//=======goes back to original pos and respawns.
void Guard::die()
{
	revertOrigPos();
	
	m_respawn.restart();
}
//======================
Guard::~Guard()
{
}
//=======================