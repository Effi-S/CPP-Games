#include "Board.h"


sf::Color COLORS[6] = {
	sf::Color::Red,
	sf::Color::Blue,
	sf::Color::Green,
	sf::Color::Yellow,
	sf::Color::Magenta,
	sf::Color::Cyan,
};

Board::Board(size_t ROWS, size_t COLS )
{
	makeBoard(ROWS,COLS); // making the vector
	restart(); 
}

//drawing the board to a window given in  window.
void Board::draw(sf::RenderWindow &window) const
{	
	for (auto &i : m_shapes)	
		i->draw(window);
}

//restarting the board to all not taken 
//with new random colors.
void Board::restart()
{
	for (auto &i : m_shapes)
		i->paintMe(COLORS[rand() % 6]);

}

//this function receives a matrix of shapeCells
//that are all diamonds 
//and  sends each cell  to add split into two(only in 
//some cases) and add the Neighbours.

//it seperates into  possibilties:
//1)	row  not the first +even  => top left and right added
//2)	row not first +odd + not end of line => add top right.
//3)	row not first + odd + not first =>add top left.
//4)	row not last  + even =>add bottom  left and right 
//5)	row not last + odd +not first in line => add bottom left
//6)	row not last  + odd + not last in line => add bottom right.
//the impotance of this seperation is because the odd rows are larger 
//than the evens by 2 shapes.
void Board::addNeighbours(std::vector<std::vector<ShapeCell *>> &shapeCells)
{
	//adding neighbours
	for (size_t row = 0; row < shapeCells.size(); row++)
		for (size_t col = 0; col < shapeCells[row].size(); col++)
		{
			if (row != 0)//adding top neighbours
			{
				if (row % 2 == 0)
				{
					shapeCells[row][col]->addNeighbour(shapeCells[row - 1][col]);
					
					shapeCells[row][col]->addNeighbour(shapeCells[row - 1][col+1]);
				}
				else
				{
					if(col!=0)
					shapeCells[row][col]->addNeighbour(shapeCells[row - 1][col-1]);

					if(col!= shapeCells[row].size()-1)
					shapeCells[row][col]->addNeighbour(shapeCells[row - 1][col]);
				}
				
			}

			if (row != shapeCells.size() - 1) //adding bottom neighbours
			{
				if (row % 2 == 0)
				{
					shapeCells[row][col]->addNeighbour(shapeCells[row +1][col]);
					
					shapeCells[row][col]->addNeighbour(shapeCells[row +1][col + 1]);
				}
				else
				{
					if(col!=0)
					shapeCells[row][col]->addNeighbour(shapeCells[row +1][col - 1]);

					if (col != shapeCells[row].size() - 1)
					shapeCells[row][col]->addNeighbour(shapeCells[row +1][col]);
				}
			}
		}
	
	
}

//deleting all CellShapes in the Board.
Board::~Board()
{
	for (auto *x: m_shapes)
		delete x;
			
}

//this is the make board function 
//receives ROWS and COLS and makes 
//a vector of CellShaps pointers (m_shapes).
//the way the vector is made:
//	1) makeing a vector ROWS X COLS size of sfml convex shapes row by row.
//	2) making a vector ROWS X COLS size of ShapeCells from each shape made in 1)
//  4)  splitting and placing the into m_shapes
//	3)adding neighbours
//this is done in one long function in order to avoid copying of the vector many times.
void Board::makeBoard(size_t ROWS, size_t COLS)
{

	if (ROWS % 2 == 0)ROWS++;//for asthetic look

	float cell_len = 12.f ;//the length of a shape 
	int wid = 2;

	if (ROWS < 20) cell_len = 22.f;//for very small board.

	//1) makeing a vector ROWS X COLS size of sfml convex shapes
	
	std::vector<std::vector<sf::ConvexShape>>shapes;


	for (size_t row = 0; row < ROWS; row++)
	{
		std::vector<sf::ConvexShape> line;
		for (size_t i = 0; i < COLS; i++)
		{
			sf::Vector2f p1, p2, p3, p4;
			sf::ConvexShape x(4);

			if (row % 2 == 0)
			{

				p1 = sf::Vector2f((cell_len * 2) + 2 * i*cell_len, (row + 2)*cell_len + cell_len);
				p2 = sf::Vector2f((cell_len * 2) + 2 * i*cell_len - cell_len, (row + 2)*cell_len + cell_len * 2);
				p3 = sf::Vector2f((cell_len * 2) + 2 * i*cell_len, (row + 2)*cell_len + cell_len * 3);
				p4 = sf::Vector2f((cell_len * 2) + 2 * i*cell_len + cell_len, (row + 2)*cell_len + cell_len * 2);

				x.setFillColor(sf::Color::Red);


			}
			else
			{
				p1 = sf::Vector2f((cell_len * 3) + 2 * i*cell_len, (row + 2)*cell_len + cell_len);
				p2 = sf::Vector2f((cell_len * 3) + 2 * i*cell_len - cell_len, (2 + row)*cell_len + cell_len * 2);
				p3 = sf::Vector2f((cell_len * 3) + 2 * i*cell_len, (2 + row)*cell_len + cell_len * 3);
				p4 = sf::Vector2f((cell_len * 3) + 2 * i*cell_len + cell_len, (2 + row)*cell_len + cell_len * 2);

				x.setFillColor(sf::Color::Blue);

			}
			x.setPoint(0, p1);
			x.setPoint(1, p2);
			x.setPoint(2, p3);
			x.setPoint(3, p4);

			if (i == COLS - 1 && row % 2 != 0)
			{
				x.setPointCount(3);
				x.setPoint(0, p1);
				x.setPoint(1, p2);
				x.setPoint(2, p3);
			}
			if (row == 0)
			{
				x.setPointCount(3);
				x.setPoint(0, p2);
				x.setPoint(1, p3);
				x.setPoint(2, p4);
			}
			if (row == ROWS - 1)
			{
				x.setPointCount(3);
				x.setPoint(0, p1);
				x.setPoint(1, p2);
				x.setPoint(2, p4);
			}
			if (i == 0 && row % 2 != 0)
			{
				auto save(x);
				p1.x -= cell_len * 2;
				p3.x -= cell_len * 2;
				p4.x -= cell_len * 2;

				x.setPointCount(3);
				x.setPoint(0, p1);
				x.setPoint(1, p3);
				x.setPoint(2, p4);

				line.push_back(x);
				x = save;
			}

			line.push_back(x);			
		}
		shapes.push_back(line);
	}

	//2) making a vector ROWS X COLS size of ShapeCells from each shape made in 1)
	std::vector<std::vector<ShapeCell *>> shapeCells;

	for (size_t i = 0; i < shapes.size(); i++)
	{
		std::vector<ShapeCell *> line;
		for (size_t j = 0; j < shapes[i].size(); j++)
			line.push_back(new ShapeCell(shapes[i][j]));
		
		shapeCells.push_back(line);
	}


	//	3)adding neighbours
	addNeighbours( shapeCells);
	
	// 4)  splitting and placing the into m_shapes
	for(auto &x :shapeCells)
		for (auto &i : x)
			i->placeInBoard(m_shapes);
			
	m_player1 = shapeCells[shapeCells.size() - 1][0];
	m_player2 = shapeCells[0][shapeCells[0].size()-1];


	
			
}
