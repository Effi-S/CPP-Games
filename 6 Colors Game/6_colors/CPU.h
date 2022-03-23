//this is the CPU class derrived from PLayer 
//it is a player that runs recursively  on the 
//neighbours of the shapeCell's it holds for each turn 
//panting the best choice based on this recursive test
//of how many neighbour's and neighbours of neighbours it finds.
#pragma once
#include "Player.h"
class CPU : public Player
{
public:
	CPU() = default;
	~CPU() = default;
	CPU(ShapeCell * starter) : Player(starter) {}
	void move(sf::Color) override;
	void iWin() const override;
	
};

