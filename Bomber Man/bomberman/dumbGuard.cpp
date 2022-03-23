
//**************DumbGuard class **********
//this is the dumbGuard class derrived from the Guard base class
//the only adjusment is that the move is random.
//**************************************

//===============include section===========
#include "dumbGuard.h"
#include "Guard.h"
#include "Robot.h"
#include "Bomb.h"
//================================

//---consts section
const unsigned SMOOTHER = 20; //smoothing guard move
//-----------------------

//===========constructor=================
//window Pos and img are for Placeable constructor.
//sets the movetimer to start for better presision.

dumbGuard::dumbGuard(sf::RenderWindow & window, sf::Vector2f pos, sf::Texture * img,
	std::vector<Placeable *> &grid, int gridX)
	:Guard(window, pos, img, grid, gridX)
{
	m_moveTimer.restart();

}
//------------------------------------

//===================================
//the guards move 
//moves every turn 
//changes moves every SMOOTHER turns.
void dumbGuard::move()
{
	if (m_moveTimer.getElapsedTime().asSeconds() > TURN_UNIT.asSeconds() * SMOOTHER)
	{
		switch (rand() % MOVES)
		{
		case(0):m_move = up_t; break;
		case(1):m_move = down_t; break;
		case(2):m_move = left_t; break;
		case(3):m_move = right_t; break;
		}
		m_moveTimer.restart();
	}
	switch (m_move)
	{
	case(up_t):moveUp(); break;
	case(down_t):moveDown(); break;
	case(left_t):moveLeft(); break;
	case(right_t):moveRight(); break;
	}
}
//------------------------
//=================================
dumbGuard::~dumbGuard()
{

}
//----------------------------------





