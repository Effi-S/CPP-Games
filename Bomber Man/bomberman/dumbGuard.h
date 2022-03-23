//**************DumbGuard class **********
//this is the dumbGuard class derrived from the Guard base class
//the only adjusment is that the move is random.
//**************************************
//------includes----
#pragma once
#include "Guard.h"
//-----------------
class dumbGuard :
	public Guard
{
public:
	dumbGuard(sf::RenderWindow & window, sf::Vector2f pos, sf::Texture * img,
		std::vector< Placeable *> &grid, int gridX);

virtual	void move();

~dumbGuard();

private:


};
	