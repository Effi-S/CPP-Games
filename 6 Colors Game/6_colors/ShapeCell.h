//this is the ShapeCell class 
//the "power-house" of this program 
//it holds a convex shape and weather or not it is added 
//as well it also holds a vector of its neighbours 
//it can add itself to a vector of Shapecells and it can add
//remove or swap a neighbour.
//it can split itself into a triangle if it is a square 
//(chooses to do so or not randomly ).
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>

class ShapeCell
{
public:
	ShapeCell(sf::ConvexShape shape);
	
	void draw(sf::RenderWindow &window) const;

	int numOfNeighboursWithColor(sf::Color color, std::vector<ShapeCell *> &myQueue) const;

	void paintMe(sf::Color color);

	sf::Color getColor();

	void addNeighbourIfColor(sf::Color color ,std::vector<ShapeCell *> &addTo);//for initialization

	void addNeighbour(ShapeCell *toAdd);//for initialization
	
	void placeInBoard(std::vector<ShapeCell *> & board);//for initialization
	void replaceWith(ShapeCell* orig, ShapeCell* toAdd);//for initialization
	
	void switchAdded(); 
	
	
	~ShapeCell();
	
private:
	std::vector<ShapeCell*> m_Neighbours; //vector of neighbouing cells 
	void splitHorizontal(std::vector<ShapeCell *> & board);//for initialization
	void splitVertical(std::vector<ShapeCell *> & board);//for initialization
	
	bool m_added = false;
	sf::ConvexShape m_shape;

	
};

