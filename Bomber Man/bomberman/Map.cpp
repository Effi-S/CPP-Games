//*****************************
//this is the map class
//it is incharge of holding all of the characters and Placeables 
//and printing them to the screen.
//****************************************

//============includes==========
#include "Map.h"
#include "Robot.h"
#include "Placeable.h"
#include "Door.h"
//===============================


//=================constructor===============
//rceives a window and gridsize aswell as a vector 
//of placeables
//and vector of characters 
Map::Map(sf::RenderWindow & window, 
	sf::Vector2u gridsize, 
	std::vector< Placeable *> &grid,
	std::vector<class Character *>  &characters)
	:m_window(window),m_Gridsize(gridsize), m_characters(characters) ,m_Grid(grid)
{
	m_bkground.setSize(sf::Vector2f(m_Gridsize.x*CELLSIZE.x, m_Gridsize.y * (CELLSIZE.y+1)));
	m_bkground.setFillColor(MINI_CLEAR); 
	
}
//===================================
//copy operator for swapping the map.
Map & Map::operator=(Map other)
{
	emptyMap();

	m_Gridsize = other.m_Gridsize;

	m_Grid = other.m_Grid;
	m_characters = other.m_characters;

	m_lvltime = other.m_lvltime;

	m_bkground = other.m_bkground;

	return *this;
}
//=================================
//===========the map must run all of its characters 
void Map::timeRun(sf::Event &event)
{
	for (size_t i =1; i < m_characters.size(); i++)
		m_characters[i]->move(event);	

	
}
//============================
//=============restarting the level==============
void Map::restartLvl()
{
	m_window.setView(m_window.getDefaultView());

	for (size_t i = 0; i < (m_Grid.size()); ++i)
		m_Grid[i]->revertOrigPos();

	for (size_t i = 0; i < m_characters.size(); i++)
	{
		m_characters[i]->revertOrigPos();
	}
					
}
//========================================

//=============drawing all characters and placeables.
void Map::drawMap()
{
	//drawing board
	for (size_t i = 0; i < m_Grid.size(); i++)
		m_Grid[i]->drawOnGrid();

	for (size_t i = 0; i < m_characters.size(); i++)
		m_characters[i]->drawOnGrid();


	DrawMiniMap();

}
//-----------------------------
//============================
//emptying the map 
void Map::emptyMap()
{
	for (size_t i = 0; i < m_characters.size(); i++)
		delete m_characters[i];

	for (size_t i = 0; i < m_Grid.size(); i++)
		delete m_Grid[i];

	m_characters.empty();

	m_Grid.empty();
}
//============================

//===============drawing the minimap.===========
void Map::DrawMiniMap()
{
	// drawing minimap 
	sf::View save = m_window.getView();
	
	sf::View  minimapView;

	minimapView.setCenter(save.getCenter());

	minimapView.setViewport(sf::FloatRect(0.75f, -0.3f, 0.25f, 0.75f));
	
	minimapView.zoom(3);

	m_window.setView(minimapView);

	m_window.draw(m_bkground);

	for (size_t i = 0; i < m_Grid.size(); ++i)
		m_Grid[i]->drawOnGrid(minimapView);

	for (size_t i = 0; i < m_characters.size(); i++)
		m_characters[i]->drawOnGrid();
	
	m_window.setView(save);
}
//-----------------------------

//=================
Map::~Map()
{

}
//-----------------
