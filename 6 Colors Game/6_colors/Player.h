//this is the Player calss 
//holds a vector of pointers 
//to cells that it holds 
//and a color that is the players current move color.
#pragma once
#include"ShapeCell.h"
#include <vector>
#include<SFML/Graphics.hpp>
#include <string>

class Player
{
public:
	Player() = default;
	~Player() = default;
	Player(ShapeCell * root);
	void paintAll(sf::Color color);
	virtual void move(sf::Color) = 0;
	virtual void iWin() const=0;

	int getColorCount(sf::Color color);

	void restart();

	size_t getSize() { return m_myShapes.size(); }

	virtual sf::Color getColor() const { return m_color; }
	virtual double getPercent(double boardSize) const { return ((m_myShapes.size() / boardSize) * 100); }
	
private:
	
	std::vector<ShapeCell *> m_myShapes;
	sf::Color m_color;
	

};

