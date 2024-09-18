#include "Player.h"
#ifdef MAKELINUX
#include <iostream>
#include <cstdlib>
#else
#include "Windows.h"
#endif

Player::Player(ShapeCell * starter)
{
	starter->paintMe(sf::Color::Black);
	
	m_myShapes.push_back(starter);
	
	m_myShapes[0]->switchAdded();
}

//the player adds all its neighbouring cells 
//with the sfml color color. 
void Player::paintAll(sf::Color color)
{
	m_color = color;
	//add neighbours	
	for (auto i = 0; i < m_myShapes.size(); ++i)
		m_myShapes[i]->addNeighbourIfColor(color, m_myShapes);

	//paint own territory
	
	for (auto i : m_myShapes)
		i->paintMe(color);
		
}

//getting the amount of adjacent cells with color.
int Player::getColorCount(sf::Color color)
{
	int count = 0;
	std::vector <ShapeCell *> Queue;
	for(auto x : m_myShapes)
		count += x->numOfNeighboursWithColor(color, Queue);

	for (auto x : Queue)//making all cells added to the qeue revert back to default. 
		x->switchAdded();

	return count;
}

//restarts the player. reverting all its cells and clearing the vector except the 
//starting cell.
void Player::restart()
{	
	for (auto x : m_myShapes)
		x->switchAdded();

	auto x=m_myShapes[0];
	x->paintMe(sf::Color::Black);
	
	m_myShapes.clear();

	m_myShapes.push_back(x);
	m_color = sf::Color::Black;
	
}


