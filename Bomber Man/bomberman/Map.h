//*****************************
//this is the map class
//it is incharge of holding all of the characters and Placeables 
//and printing them to the screen.
//****************************************

//============includes==========
#pragma once
#include "CONSTS.h"
//-------------------------------
class Placeable;
#include "LevelLoader.h"

class Map
{
		
public:
	Map( sf::RenderWindow &window, 
		sf::Vector2u gridsize ,
		std::vector <class Placeable *> &grid ,
		std::vector <class Character *> &characters );
	
	void restartLvl();

	void timeRun(sf::Event &event);

	void drawMap();
	
	Map & operator = (Map other);

	~Map();

private:

	void emptyMap();

	void DrawMiniMap() ;

	sf::RectangleShape m_bkground;

	sf::RenderWindow &m_window;
	
	std::vector <Character *> m_characters;

	std::vector <class Placeable *> m_Grid;

	sf::Vector2u m_Gridsize;

	sf::Clock m_lvltime;	
};

