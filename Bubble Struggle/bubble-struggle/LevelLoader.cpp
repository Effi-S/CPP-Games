#include "LevelLoader.h"
#include <string>
#include <sstream>
#include <iostream>
#include "Board.h"
#include "DrawableFactory.h"


void LevelLoader::LoadNextLevel()
{
	
	(static_cast<std::size_t>(m_currLvlIndex) == m_lvls.size() - 1) ? m_currLvlIndex = 0 : m_currLvlIndex++;
	
	Board::inst().nextLvl();

	LoadCurrent();

	
}

void LevelLoader::ReloadLevel()
{
	Board::inst().restart();
	
	LoadCurrent();
}

LevelLoader::LevelLoader()
{
	
	std::ifstream file("resources/Levels.txt");
	
	if (!file.is_open())std::cout << "cannot open!" << std::endl;

	std::string str;

	
	while (std::getline(file, str))
	{
		if (str.find_first_not_of(' ') != std::string::npos)
			if (str.find("END") != std::string::npos)
				break;
			else if (str.find("LEVEL") != std::string::npos)
				m_lvls.emplace_back(std::vector<std::string>());
			else if(!str.empty())
				m_lvls.back().emplace_back(str);
		
		
	}
	
	
			
}


LevelLoader::~LevelLoader()
{
}

void LevelLoader::LoadCurrent()
{
	//making frame
	DrawableFactory::createDrawable("Wall 1 1 1366 15");
	DrawableFactory::createDrawable("Wall 1 1 50 700");
	DrawableFactory::createDrawable("Wall 1316 1 50 700");
	DrawableFactory::createDrawable("Wall 1 700 1316 30");

	//loading lvl
	for (auto x : m_lvls.at(m_currLvlIndex))
		DrawableFactory::createDrawable(x);
}


