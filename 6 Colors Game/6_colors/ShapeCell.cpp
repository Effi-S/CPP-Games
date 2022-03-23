#include "ShapeCell.h"
#include "ImageLoader.h"
#include <algorithm>
#include<iostream>



ShapeCell::ShapeCell(sf::ConvexShape shape)
	:m_shape(shape)
{	
	 
	m_shape.setTexture(ImageLoader::instance().getSquare());

}


//receives a sfml render window and prints its convex shape onto it
void ShapeCell::draw(sf::RenderWindow & window) const
{	
	window.draw(m_shape);
}

//adds the number of neighbouring cells with  color 
//to myQueue 
int ShapeCell::numOfNeighboursWithColor(sf::Color color, std::vector<ShapeCell *> &myQueue) const
{
	
	int num = 0;
	for (auto x : m_Neighbours)
		if (!x->m_added && x->getColor() == color)
		{
			myQueue.push_back(x);
			x->switchAdded();
			num++;
			num += numOfNeighboursWithColor(color , myQueue);
		}
			return num;
}


//adds the ShapeCell toAdd to the neghbours of this shapeCell
void ShapeCell::addNeighbour(ShapeCell *toAdd)
{
	m_Neighbours.push_back(toAdd);
}

//places this shapeCell into board given. 
void ShapeCell::placeInBoard(std::vector<ShapeCell *> & board)
{	
	if ( m_Neighbours.size()==4)
	{	
		switch (rand() % 3)
		{
		case(0):splitHorizontal(board); break;
		case(1):splitVertical(board); break;
		case(2):board.push_back(this); break;
		}
	}
	else
	board.push_back(this);

}

//replaces orig if found in the neighbours with toAdd
void ShapeCell::replaceWith(ShapeCell *orig, ShapeCell *toAdd)
{
	for (auto &i: m_Neighbours )
		if (i==orig)
		{
			i = toAdd;
			break;
		}			
}

//switchs m_added to its opposite
//and the its texture accordingly.
void ShapeCell::switchAdded()
{
	m_added = !m_added;

	if(m_added)
	m_shape.setTexture(ImageLoader::instance().getFilledSquare());
	else
	m_shape.setTexture(ImageLoader::instance().getSquare());
};

//paints the shape mamber the color given 
void ShapeCell::paintMe(sf::Color color)
{
	m_shape.setFillColor(color);

}

//returns the sfml color of the sfml convex shape
sf::Color ShapeCell::getColor()
{
	return m_shape.getFillColor();
}

//adds all neighbours with color to addTo
void ShapeCell::addNeighbourIfColor(sf::Color color, std::vector<ShapeCell*> &addTo)
{	
		for (auto &i : m_Neighbours)			
			if (!i->m_added && i->getColor() == color)
			{
				addTo.push_back(i);
				i->switchAdded();
				
			}		
}


ShapeCell::~ShapeCell()
{
}

//splits a diamond horizontaly 
//to 2 triangles adds to board and then calls 
//the destructor because it is no longer in use.
void ShapeCell::splitHorizontal(std::vector<ShapeCell *>& board)
{
	sf::Vector2f p1(m_shape.getPoint(0)), p2(m_shape.getPoint(1)),
		p3(m_shape.getPoint(2)), p4(m_shape.getPoint(3));

	sf::ConvexShape l(3), r(3);
	l.setPoint(0, p1);
	l.setPoint(1, p2);
	l.setPoint(2, p3);

	r.setPoint(0, p1);
	r.setPoint(1, p3);
	r.setPoint(2, p4);
	l.setFillColor(sf::Color::Magenta);
	r.setFillColor(sf::Color::Cyan);

	ShapeCell *left(new ShapeCell(l)), *right(new ShapeCell(r));

	left->addNeighbour(m_Neighbours[0]);
	m_Neighbours[0]->replaceWith(this, left);

	left->addNeighbour(m_Neighbours[2]);
	m_Neighbours[2]->replaceWith(this, left);
	
	right->addNeighbour(m_Neighbours[1]);
	m_Neighbours[1]->replaceWith(this, right);
	
	right->addNeighbour(m_Neighbours[3]);
	m_Neighbours[3]->replaceWith(this, right);

	right->addNeighbour(left);
	left->addNeighbour(right);

	board.push_back(left);
	board.push_back(right);
	this->~ShapeCell();
}

//splits a diamond vertically 
//to 2 triangles adds to board and then calls 
//the destructor because it is no longer in use.
void ShapeCell::splitVertical(std::vector<ShapeCell *>& board)
{
	sf::Vector2f p1(m_shape.getPoint(0)), p2(m_shape.getPoint(1)),
		p3(m_shape.getPoint(2)), p4(m_shape.getPoint(3));

	sf::ConvexShape u(3), d(3);
	u.setPoint(0, p1);
	u.setPoint(1, p2);
	u.setPoint(2, p4);

	d.setPoint(0, p2);
	d.setPoint(1, p4);
	d.setPoint(2, p3);

	u.setFillColor(sf::Color::Yellow);
	d.setFillColor(sf::Color::Green);

	ShapeCell *up(new ShapeCell(u)), *down(new ShapeCell(d));

	up->addNeighbour(m_Neighbours[0]);
	m_Neighbours[0]->replaceWith(this, up);
	up->addNeighbour(m_Neighbours[1]);
	m_Neighbours[1]->replaceWith(this, up);

	down->addNeighbour(m_Neighbours[2]);
	m_Neighbours[2]->replaceWith(this, down);

	down->addNeighbour(m_Neighbours[3]);
	m_Neighbours[3]->replaceWith(this, down);

	down->addNeighbour(up);
	up->addNeighbour(down);

	board.push_back(up);
	board.push_back(down);
	this->~ShapeCell();
}
