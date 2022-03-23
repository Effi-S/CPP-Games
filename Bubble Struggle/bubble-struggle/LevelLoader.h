//this is the level loader class
//for loading levels from the 
//file "levels.txt" onto the singleton board.
//it loads said file and stores each 
//level into a vector of strings
//each level must start with "LEVEL"
//and the file is read until "END"

#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include <fstream>
#include <sstream>
#include <memory>
#include "Moveable.h"
#include "Unmoveable.h"
#include <string>
#include "DrawableFactory.h"
class LevelLoader
{
public :
	
	void LoadNextLevel();
	void ReloadLevel();
	void setCurrLvl(int lvl) { m_currLvlIndex = lvl; }
	bool isLastLevel() const { return m_currLvlIndex == m_lvls.size() - 1; }
	LevelLoader();
	~LevelLoader();
private:
	
	void LoadCurrent();
	std::vector<std::vector<std::string>> m_lvls; // vector of the level strings
	int m_currLvlIndex=0; // the current level
	
};

