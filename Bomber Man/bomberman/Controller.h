//*******************Controller******************
//This is the controller class 
//in charge of controlling the game play.
//it holds a meber of class LevelLoader
//it calls on the it when neccessary to load another level.
//holds a member of UserInterface and map and decides 
//when to call on them.
//as well as when to print them to the screen.
//******************/

//========includes===================
#pragma once
#include "CONSTS.h"
#include "LevelLoader.h"
#include "Robot.h"

#include "UserInterface.h"
#include "Map.h"
//==================================
//------------const --------------


//--------------------------

class Controller
{
public:
	Controller(LevelLoader &lvlLoad);
	void Run();
	
	~Controller();

private:

	void drawInfo();
	void restartClocks();
	void makeInfo();
	void windowClosed();
	void turn(sf::Event &event);
	
	void mouseHandler(sf::Event &event);
	void pauseGame();
	void restartLvl();
	void nextLvl();
	void checkHighscore();
	void lostGame();


	sf::RenderWindow m_window;

	sf::Font m_font;
	
	sf::Clock m_Timer;// general time for the level.
	sf::Clock m_turnTimer; // for how long each turn took.
	sf::Time m_timeLeft;//time left till lost life.

	

	int m_score = 0;
	Map m_map;

	UserInterface m_toolbar;

	LevelLoader m_lvlLoader;
	
	std::vector <sf::Text > m_gameInfoText;

	Robot *m_robot;

	

};

