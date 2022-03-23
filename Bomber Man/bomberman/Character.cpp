
//**************Character class**************
//this is the character class  a purely virtual
//class derrived from the Placeable base class.
//a object of this class can move on the 
//grid of the game.
//for that the grid is referenced member of the object
//***************************************

//-----------includes
#include "Character.h"

//===========constructor==========
//window pos and img are for Placeable constructor
//the grid is a vector of placeables that are in play in the 
//game.
Character::Character(sf::RenderWindow &window, sf::Vector2f pos, sf::Texture * img,
	std::vector<Placeable *> & grid , int gridX , int slides , int slideRows)
	: Placeable(window, pos, img ) , m_grid(grid) ,m_gridX(gridX) , SLIDEROWS(slideRows) , SLIDES(slides)
{
	slideChange(up_t);
	m_slideTimer.restart();	

	m_image->setRepeated(true);
}
//----------------------------------
//===================================
//addd a cell in the position gridpos in the m_grid 
//to the vector adjacents.
void Character::addCell(int gridpos, std::vector<Placeable *> &adjacents)
{
	if (gridpos < m_gridX *m_grid.size() / m_gridX && gridpos >= 0)
		adjacents.push_back(m_grid[gridpos]);

}
//----------------------------------
//sends to the move function 
//base on the variable received into move.
void Character::moveMe(move_t move)
{
	switch (move)
	{
	case(up_t):moveUp(); break;
	case(down_t):moveDown(); break;
	case(left_t):moveLeft(); break;
	case(right_t):moveRight();break;

	}
}
//-----------------------------
//==============================
//returns a vector of adjacent cells to the cell place
//in m_grid.
std::vector<Placeable*> Character::Adjacents(int place) 
{
	std::vector <Placeable*> addjacents;

	addCell(place-m_gridX, addjacents);
	addCell(place + m_gridX, addjacents);

	if(place % m_gridX !=m_gridX-1 )
	addCell(place+1, addjacents);

	if(place%m_gridX !=0)
	addCell(place-1, addjacents);

	return addjacents;

}
//-----------------------------
//===========================
//returns only the empty adjaceant cells
std::vector<Placeable*> Character::getEmptyAdjacents() 
{
	 std::vector<Placeable*> adjace=Adjacents();

	 for (size_t i = 0; i < adjace.size(); i++)
		 if (!adjace[i]->isEmpy())
			 adjace.erase(adjace.cbegin() + i);
		 
	 return adjace;
}
//---------------------------
//returns the adjaceant cells 
//relevent for bfs 
//that are in view and empty.
std::vector<Placeable*> Character::getBFSAdjacents(int place, sf::FloatRect windowView) 
{

	std::vector<Placeable*> adjace = Adjacents(place);

	for (size_t i = 0; i < adjace.size(); i++)
		if (!adjace[i]->isEmpy() || !windowView.contains(adjace[i]->getPos()))
			 adjace.erase(adjace.cbegin() + i);
	return adjace;

}
//------------------------
//=============================
//returns the place of this on m_grid.
int Character::getGridPlace() const 
{
	sf::Vector2f gridpos = getGridPos();

	return gridpos.x + gridpos.y*m_gridX;

}
//------------------------------
//==============================
//returns this's adjaceant cells in m_grid.
std::vector<Placeable*> Character::Adjacents()  
{
	std::vector <Placeable*> addjacents;

	sf::Vector2f gridpos = getGridPos();

	addCell( m_gridX * (gridpos.y + 1) + gridpos.x,  addjacents);
	addCell( m_gridX *(gridpos.y - 1) + gridpos.x,  addjacents);
	addCell( m_gridX *gridpos.y + gridpos.x + 1,  addjacents);
	addCell( m_gridX *gridpos.y + gridpos.x - 1, addjacents);

	return addjacents;
}
//-------------------------------------

//returns the cells from the object till the end of the grid
//in all directions.
std::vector<Placeable*> Character::AdjacentsLong()
{
	std::vector<Placeable*> adjace;

	sf::Vector2f pos = m_rect.getPosition();
	int gridPlace = getGridPlace();

	
	for (size_t i = gridPlace+1; i % m_gridX !=0 ; i++)
	{
		adjace.push_back(m_grid[i]);

		if (!m_grid[i]->isEmpy())
			break;
	}

	for (size_t i = gridPlace-1; i>=0 && i % m_gridX != 0; i--)
	{
		adjace.push_back(m_grid[i]);

		if (!m_grid[i]->isEmpy())
			break;
	}

	for (size_t i = gridPlace + m_gridX; i +m_gridX <= m_grid.size() ; i+=m_gridX)
	{
		adjace.push_back(m_grid[i]);

		if (!m_grid[i]->isEmpy())
			break;
	}
	for (size_t i = gridPlace - m_gridX; i - m_gridX >=0; i-=m_gridX)
	{
		adjace.push_back(m_grid[i]);

		if (!m_grid[i]->isEmpy())
			break;
	}
	
	return adjace;
}
//--------------------------------------

//--------------------------------
void Character::revertOrigPos()
{
	Placeable::revertOrigPos();
}
//===================================

//===========movements=============
void Character::moveUp()
{
	sf::Vector2f savePos = m_rect.getPosition();

	sf::Vector2f temp = m_rect.getPosition();

	temp.y -= latMove;

	m_rect.setPosition(temp);
	
	if (decidePos(savePos))
	{
		slideChange(up_t);
		m_move = up_t;
	}
	
}
//---------------------------------
void Character::moveDown()
{

	sf::Vector2f savePos = m_rect.getPosition();

	sf::Vector2f temp = m_rect.getPosition();

		temp.y += latMove;

	m_rect.setPosition(temp);

	if (decidePos(savePos))
	{
		slideChange(down_t);
		m_move = down_t;
	}
	
}
//----------------------------
void Character::moveLeft()
{

	sf::Vector2f savePos = m_rect.getPosition();

	sf::Vector2f temp = m_rect.getPosition();

	temp.x -= horMove;
	m_rect.setPosition(temp);

	

	if (decidePos(savePos))
	{
		slideChange(left_t);
		m_move = left_t;
	}

	
}
//-----------------------------------
void Character::moveRight()
{

	sf::Vector2f savePos = m_rect.getPosition();

	sf::Vector2f temp = m_rect.getPosition();

	temp.x+= horMove; 

	m_rect.setPosition(temp);

	if (decidePos(savePos))
	{
		slideChange(right_t);
		m_move = right_t;
	}
}
//----------------------------------
//returns if the cell received in cell 
//is not empty.
bool Character::CellBlocked( unsigned cell) const
{
	if(cell >= m_grid.size())
	return false;

	if (!m_grid[cell]->getGlobalBoundrie().intersects(m_rect.getGlobalBounds()))
		return false;

	if(!m_grid[cell]->isEmpy())		
	 return true;

	return false;
}
//---------------------
//======================
//returns this's position  in m_grid 
//as a vector2f thats x is the column and y the row.
sf::Vector2f Character::getGridPos() const
{
	sf::Vector2f auxPos(m_rect.getPosition());

	auxPos.y += CELLSIZE.y / 2;
	auxPos.x += CELLSIZE.x* 3 / 4;
	
	//findig  y position
	float y=0, x =0;
		
	for (y = 0; y <m_grid.size()/m_gridX; y++)
		if (m_grid[m_gridX*y]->getYpos() > auxPos.y) break;

	y--;

	//finding x position
	if( y >= 0 )
	for (x = 0; x < m_gridX; x++)
	{
		if (m_grid[m_gridX * y + x]->getGlobalBoundrie().contains(auxPos))
			break;
	}

	auxPos.y -= CELLSIZE.y / 2;
	auxPos.x -= CELLSIZE.x *4/ 3;


	return sf::Vector2f(x,y);
}
//------------------------------
//=============change animation slide===============
void Character::slideChange(move_t move)
{
	
		(m_slide == (SLIDES-1)) ? m_slide = 0 : m_slide++;
	
		
	m_rect.setTextureRect(sf::IntRect(m_image->getSize().x / SLIDES * m_slide
		, m_image->getSize().y / SLIDEROWS * move,
				m_image->getSize().x / SLIDES,
		m_image->getSize().y / SLIDEROWS)
	);
}
//---------------------------------------
//===================================================
//returns a floatRect that contains the view of m_window. 
sf::FloatRect Character::getCurrentViewRect() const
{
	sf::Vector2f viewCenter(m_window.getView().getCenter());

	sf::Vector2f viewSize(m_window.getView().getSize());

	sf::FloatRect currentViewRect(viewCenter - viewSize / 2.f, viewSize);

	return currentViewRect;
}
//-----------------------------------------
//=============decides the position of the move.
//valid returns true 
//otherwise change m_rect's position to the savPos given and returns false.
bool Character::decidePos( sf::Vector2f & savePos)
{	
	if (m_rect.getPosition().x > m_grid[m_grid.size() - 1]->getXpos() || m_rect.getPosition().y > m_grid[m_grid.size() - 1]->getYpos()
		|| m_rect.getPosition().y < m_grid[0]->getYpos() || m_rect.getPosition().x < m_grid[0]->getXpos())
	{
		m_rect.setPosition( savePos) ;

		return false; 
	}
		
	sf::Vector2f gridPos = getGridPos();

	if (   CellBlocked(m_gridX*gridPos.y + gridPos.x) //me
		|| CellBlocked( m_gridX * (gridPos.y+1) + gridPos.x )//down 
		|| CellBlocked( m_gridX* (gridPos.y ) + gridPos.x-1)//left
		//|| CellBlocked(m_gridX* (gridPos.y-1) + gridPos.x)//up
		//|| CellBlocked( m_gridX * gridPos.y + (gridPos.x+1) )//right//
		 )
	{
		m_rect.setPosition(savePos);

		return false;
	}

	collideWith(*m_grid[gridPos.y *  m_gridX + gridPos.x]);

	return true;
	
}
//-----------------------------
//----------------------------
Character::~Character()
{

}
//---------------------------