//this is the Board class 
//is holds a vector of ShapeCells that 
//can be printed to the screen.
#pragma once
#include "ShapeCell.h"
#include <vector>
#include <SFML/Graphics.hpp>
class Board
{
public:
	Board(size_t ROWS= 43, size_t COLS = 28);
	void draw(sf::RenderWindow &window) const;
	void restart();
	ShapeCell *getPlayer1Cell() const  { m_player1->switchAdded(); return m_player1; };
	 ShapeCell *getPlayer2Cell() const { m_player2->switchAdded(); return m_player2; };
	 double getCellsCount() const { return (double)m_shapes.size(); }
	~Board();
private:
	
	void makeBoard(size_t ROWS , size_t COLS );
	void addNeighbours(std::vector<std::vector<ShapeCell *>> & shapeCells);

	std::vector< ShapeCell *> m_shapes;
	
	ShapeCell *m_player1;//pointer to player1 Cell
	ShapeCell *m_player2;// pointer to player2 Cell
};

