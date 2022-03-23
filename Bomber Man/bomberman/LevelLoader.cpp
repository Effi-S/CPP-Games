
//*********LevelLoader class *********************
//this is the Level load3er class 
//it is in charge of making the levels as the game is run.
//it holds a vector of strings for each leevel 
//that it reads only once when created.
//each time the level is changed 
//it makes a map based on the vector in that place.
//========include section==============
#include "LevelLoader.h"
#include "Map.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "EmptyCell.h"

#include "Robot.h"
#include "Placeable.h"
#include "Character.h"
#include "Guard.h"
#include "smartGuard.h"
#include "dumbGuard.h"

#include "Edge.h"
#include "Door.h"
#include "Stone.h"
//==============================

//========constructor============
//reads from "board.txt" and makes  its 
//members based on the information in the file
//before each level there must be the rows columns 
//time and bombs.
LevelLoader::LevelLoader(int curLvl)
	:m_curLvl(curLvl)
{	
	//opening file
	std::ifstream lvlfile("board.txt");

	if (!lvlfile.is_open())
	{
		std::cerr << "cannot open file \n";
		exit(EXIT_FAILURE);
	}

	//allocating members
	lvlfile >> LEVELS;

	m_lvlSizes.resize(LEVELS);

	m_lvlTimes.resize(LEVELS);

	m_bombsLimit.resize(LEVELS);

	for (int lvl = 0; lvl < LEVELS; lvl++)		
	{		
		std::vector<std::string>	level;

		int							lvlsize_y,lvlsize_x ,bombs;

		float						time;

		lvlfile >> lvlsize_y >> lvlsize_x >> time >>bombs;

		m_lvlSizes[lvl].y = lvlsize_y ; 	
		m_lvlSizes[lvl].x = lvlsize_x;
		m_lvlTimes[lvl] = sf::seconds(time);
		m_bombsLimit[lvl]=bombs;
		
		size_t max_size = 0;
		
		for (int i = 0; i < lvlsize_y; i++)
		{
			std::string line;
			 
			getline(lvlfile, line);

			if (line.empty())continue;

			if (line.size()-1 > max_size)
				max_size = line.size();

			level.push_back(line);
		}

		m_lvlSizes[lvl].x = max_size;
		
		m_Levels.push_back(level);

		m_lvlSizes[lvl].y = level.size();
	}

	m_Levels.shrink_to_fit();

	loadImages();
}
//------------------------------

//=============================
//receives a render window into window 
//and makes a map based on the current lvl in play.
Map  &LevelLoader::loadNextLvl(sf::RenderWindow &window )
{
	if (m_curLvl == LEVELS-1 )
		m_curLvl = 0;

//making grid------

	 std::vector <Placeable *> *grid = new std::vector <Placeable *>;
	
	 std::vector <Character *> *characters = new std::vector <Character *>;

	 m_robot = new Robot(window , &m_images[robot_t], &m_images[bomb_t], *grid, *characters , m_lvlSizes[m_curLvl].x , m_bombsLimit[m_curLvl]  );

	for (size_t i = 0; i < m_lvlSizes[m_curLvl].y; i++)
	{
			for(size_t j =0 ; j< m_lvlSizes[m_curLvl].x ; j++)
			{	

			char c; 
			(j <= m_Levels[m_curLvl][i].size()) ? c = m_Levels[m_curLvl][i][j] : c = ' ';

			PlaceInGrid(window, *grid , *characters, sf::Vector2f(j * CELLSIZE.x, i * CELLSIZE.y),
				c );	

			}
	}
//------------making map----
	
	m_curLvl++;
	return (* new Map(window, m_lvlSizes[m_curLvl-1],  *grid , *characters ));

}
//=======================================================



//======================================================
//returns the time for the current lvl
sf::Time LevelLoader::getCurLvlTime() const
{
	return m_lvlTimes[m_curLvl-1];
}
//============================

//================returns the current lvl
int LevelLoader::getCurLvl() const
{
	return m_curLvl;
}

//-------------------------

//=================================
//receives a position and a char
//into pos and c
//as well a charactors vector and a grid
//into characters and grid.
//based on the char adds to the grid if placeable
//or to the characters vector if a character
//it also receives a reference to the window to be transferred
// for '/' adds a robot
// for '! ' adds a guard
//for '&' or  '@' adds a stone 
//for '#' adds a wall
//for '+' adds a empty cell with a present.

void LevelLoader::PlaceInGrid(sf::RenderWindow &window ,std::vector< Placeable *> & grid,
	std::vector <Character *> & characters ,
	sf::Vector2f place, char c)
{		
		switch(c)
	   {
		case(' '): grid.push_back(new EmptyCell(window, place, &m_images[empty_t]));break ;

		case('+'):grid.push_back(new EmptyCell(window, place, &m_images[empty_t], &m_images[present_t], true)  ); break;

		case ('/'):
			addRobot(window, grid, characters, place);break;
			
			 
		case ('!'): addGuard(window, grid, characters, place);	break; 


		case('&'):grid.push_back(new Stone(window, place, &m_images[stone_t], &m_images[present_t], true) ); break;

		 case ('#'):grid.push_back(new Edge(window, place , &m_images[edge_t]) ); break;

		 case ('@'):grid.push_back(new Stone(window, place , &m_images[stone_t] )); break;

		 case ('D'):grid.push_back(new Door(window, place, &m_images[door_t])); break;

		 default:grid.push_back(new EmptyCell(window, place, &m_images[empty_t])); break; 
			 
	}

		
}
//==================================

//======================================
void LevelLoader::addGuard(sf::RenderWindow & window, std::vector<class Placeable*>& grid, std::vector<class Character*>& characters, sf::Vector2f place)
{

	switch (rand() % 2)
	{
	case(0):characters.push_back(new dumbGuard(window, place, &m_images[guard_t], grid, m_lvlSizes[m_curLvl].x)); break;
	case(1):  characters.push_back(new smartGuard(window, place, &m_images[smartGuard_t], grid, m_robot, m_lvlSizes[m_curLvl].x)); //break;
	}
	
	
	grid.push_back(new EmptyCell( window, place, &m_images[empty_t] ) );
}
//----------------------------------------

//========================================
void LevelLoader::addRobot(sf::RenderWindow & window, std::vector<class Placeable*>& grid, std::vector<class Character*>& characters, sf::Vector2f place)
{
	m_robot->setPos(place);

	characters.push_back(m_robot);

	std::rotate(characters.rbegin(), characters.rbegin() + 1, characters.rend());

	grid.push_back(new EmptyCell(window, place, &m_images[empty_t]));

}
//=======================================

//==========loads all the images for the game.
void LevelLoader::loadImages()
{
	m_images[empty_t].loadFromFile("images/empty.png");
	m_images[edge_t].loadFromFile("images/edge.png");
	m_images[stone_t].loadFromFile("images/stone.png");
	m_images[door_t].loadFromFile("images/door.png");
	m_images[guard_t].loadFromFile("images/guard.png");
	m_images[smartGuard_t].loadFromFile("images/smartGuard.png");
	m_images[robot_t].loadFromFile("images/robot.png");
	m_images[bomb_t].loadFromFile("images/bomb.png");
	m_images[present_t].loadFromFile("images/present.png");
	

}
//======================================	
//returns weather or not the current level is the last level
bool LevelLoader::LastLvl() const 
{
	if (m_curLvl == LEVELS-1 )
		return true;

	return false;
}
//===========================

//===========================
void LevelLoader::restart()
{
	m_curLvl = 0;

}

//================================
Robot * LevelLoader::getRobot() const 
{
	return m_robot;
}
//========================	
//==============================
LevelLoader::~LevelLoader()
{
}
//===========================
