//*********LevelLoader class *********************
//this is the Level load3er class 
//it is in charge of making the levels as the game is run.
//it holds a vector of strings for each leevel 
//that it reads only once when created.
//each time the level is changed 
//it makes a map based on the vector in that place.
//========include section==============
#pragma once
#include "CONSTS.h"
#include <vector>
#include <string>
//--------------------------------------
class Map;

class LevelLoader
{

public:
	LevelLoader(int curLvl = 0);

	Map &loadNextLvl(sf::RenderWindow &window);

	void restart();

	class Robot *getRobot() const;
	
	sf::Time getCurLvlTime() const ;

	int getCurLvl() const; 

	bool LastLvl() const;
	
	~LevelLoader();

private:

	void PlaceInGrid(sf::RenderWindow &window, std::vector<class Placeable *> &grid, 
		std::vector <class Character *> &characters,
		sf::Vector2f place, char c  );

	void addGuard(sf::RenderWindow &window, std::vector<class Placeable *> &grid,
		std::vector <class Character *> &characters,
		sf::Vector2f place);

	void addRobot(sf::RenderWindow &window, std::vector<class Placeable *> &grid,
		std::vector <class Character *> &characters,
		sf::Vector2f place);

	
	
	int LEVELS;
	
	int m_curLvl;

	class Robot *m_robot;

	std::vector< std::vector< std::string> > m_Levels;

	std::vector <sf::Time > m_lvlTimes;
	
	std::vector <sf::Vector2u > m_lvlSizes;

	std::vector <int> m_bombsLimit;

	sf::Texture  m_images[IMAGES];

	void loadImages();

};

