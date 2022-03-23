
//*******************Controller******************
//This is the controller class 
//in charge of controlling the game play.
//it holds a meber of class LevelLoader
//it calls on the it when neccessary to load another level.
//holds a member of UserInterface and map and decides 
//when to call on them.
//as well as when to print them to the screen.
//******************/
//=============include section==========
#include "Controller.h"
#include <fstream>
#include<cstring>
#include <Windows.h>

//===================================================
//constructor receuves the levelLoader of the game.
//and makes map and UserInterface
//aswell as lvl info for printing the info to the screen.
Controller::Controller(LevelLoader &lvlLoad)
	:m_window(sf::VideoMode(1024, 512), "BomberMan",  sf::Style::Default) ,m_toolbar(m_window)
	,m_lvlLoader(lvlLoad ),
	m_robot(m_lvlLoader.getRobot()),
	m_map(lvlLoad.loadNextLvl(m_window) )
{
	m_score = 0;

	makeInfo();	
	m_window.setFramerateLimit(120);

}
//=================================================
//runs game 
//this function runs throughout the game and only finishes when window is 
//closed or when the user presses exit in the menu.
void Controller::Run()
{

	restartClocks();

	m_timeLeft = m_lvlLoader.getCurLvlTime();


	while (m_window.isOpen())
	{
		sf::Event event;
		
		while (m_window.pollEvent(event))
		{
			

			switch (event.type)
			{
			case(sf::Event::Closed):						windowClosed();break;
			case(sf::Event::MouseButtonReleased):			
			case(sf::Event::MouseMoved):			 mouseHandler(event); break;
			}
					
		}
		
		if (m_turnTimer.getElapsedTime() > TURN_UNIT)
			turn(event);

		m_window.clear(CLEAR1);

		if (m_toolbar.inGame())
			m_map.drawMap();		
		else
			m_Timer.restart();
					
		m_toolbar.draw();

		drawInfo();

		m_window.display();		

	}
}
//==================================================

//====================
//restarting the turn timer and then 
//updating time left.
void Controller::restartClocks()
{
	m_turnTimer.restart();
	m_Timer.restart();
	m_timeLeft = m_lvlLoader.getCurLvlTime();
}

void Controller::makeInfo()
{
	m_font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
	
	m_window.setView(m_window.getDefaultView());

	sf::Text text("00", m_font, 14);

	text.setFillColor(sf::Color::Red);

	text.setOutlineThickness(3.f);

	text.setOutlineColor(sf::Color::Yellow);

	for (int i = 0; i <= bar_lvl_t -2 ; i++)
	{
		text.setPosition(TOOLBAR_BUTTONSIZE.x*(i + (float)2.5), TOOLBAR_BUTTONSIZE.y /(float)2.5);
	
		m_gameInfoText.push_back(text);
	}
}

void Controller::windowClosed()
{
	m_window.close();
}
//---------------------------------------

//======================================
//this is the turn 
//receives the event for the robot 
//to know which key has been pressed.
void Controller::turn(sf::Event &event)
{
	if (m_robot->getInfo().lives <= 0)
		lostGame();

	m_turnTimer.restart();

	if (m_toolbar.inGame())
	{		
			m_robot->move(event);
			
			m_map.timeRun(event);

			m_timeLeft -= m_Timer.restart();
	
	
		if (m_robot->getInfo().nextlvl)
		nextLvl();

		if ((int)m_timeLeft.asSeconds() == 0)
		 {
		m_toolbar.timesUp();

		restartLvl();
		 }
	}
}
//================================================

//==================================================
//sends the event received into event to the toolbar
//when the event is a mouse event.
void Controller::mouseHandler(sf::Event &event)
{
	switch (m_toolbar.Run(event))
	{
	case(NO_ACTION):   											 break;
	case(PAUSE):							pauseGame();		 break;//pause
	case(RESTART):							restartLvl();		 break; //restart		
	case(NEXT_LVL):							nextLvl();			 break; // next lvl
	case(CLOSE):							windowClosed();		 break;
	
	}
	 
}
//-----------------------------------------

//==================================
//drawing the game info 
//time left
//bombs, score ,lvl , 
void Controller::drawInfo()
{
	if (!m_toolbar.inGame())return;
	
//creating local info strings:
	char livesStr[10], timeStr[10] = { ' ' },//(only this one needed initialization for some reason)
		scoreStr[10], bombStr[10] = { ' ' }, lvlStr[10];

	
	//time
	int temp = (int)m_timeLeft.asSeconds() + m_robot->getInfo().time;

	sprintf_s(timeStr, "%d", temp);

	m_gameInfoText[bar_time_t-2].setString(timeStr);
	//lives:
	sprintf_s(livesStr, "%d", m_robot->getInfo().lives);

	m_gameInfoText[bar_lives_t-2].setString(livesStr);

	

	//bombs:
	sprintf_s(bombStr, "%d", m_robot->getInfo().bombs);

	
	if (m_robot->getInfo().bombs < 0)
		m_gameInfoText[bar_bombs_t-2].setString("infinite");
	else if (m_robot->getInfo().bombs == 0)
		m_gameInfoText[bar_bombs_t - 2].setString("none");
	else
		m_gameInfoText[bar_bombs_t - 2].setString(bombStr);

	//score:
	int score = m_robot->getInfo().score + m_score;

	sprintf_s(scoreStr, "%d", score);

	m_gameInfoText[bar_score_t - 2].setString(scoreStr);

	//Level:	
	sprintf_s(lvlStr, "%d", m_lvlLoader.getCurLvl());

	m_gameInfoText[bar_lvl_t -2].setString(lvlStr);

	
//displaying:
	sf::View  gameView = m_window.getView();

	m_window.setView(m_window.getDefaultView());

	for (size_t i = 0; i < m_gameInfoText.size(); i++)
		m_window.draw(m_gameInfoText[i]);

	m_window.setView(gameView);				
}
//===================================


//==================pauseing the game=============
//used both when game paused and when unpaused.
void Controller::pauseGame()
{
	if (!m_toolbar.inGame())		
	{
		m_turnTimer.restart();
		m_Timer.restart();
				
	}
	else
		m_Timer.restart();
	
}
//=============restarting the level===========
void Controller::restartLvl()
{	
	if (m_lvlLoader.LastLvl())
		m_toolbar.youWon();

	m_map.restartLvl();

	

	restartClocks();
}
//================loading next level from the levelLoader==========
void Controller::nextLvl()
{
	if (m_lvlLoader.LastLvl())
	{
		m_toolbar.youWon();
		checkHighscore();

	}
		
	m_window.clear(CLEAR1);

	m_map.drawMap();

	m_window.display();

	m_score += m_robot->getInfo().score;

	m_map = m_lvlLoader.loadNextLvl(m_window);

	m_robot = m_lvlLoader.getRobot();
	
	
	restartClocks();
}
//========checks wheather or not the highscore has been reached a n updates it==========
void Controller::checkHighscore()
{
	
	std::fstream INPUT("Highscore.txt");
	int highscore=0;
	INPUT >> highscore;

	INPUT.close();

	std::ofstream FILE("Highscore.txt");

	int curScore = m_robot->getInfo().score + m_score;

	int i = 0;

	if (curScore > highscore)
	{
		FILE.clear();

		FILE << curScore;


		m_toolbar.newHighscore();
	} 


}
//---------------------------

//============the user lost the game completly=========
void Controller::lostGame()
{
	m_toolbar.youLost();

	m_robot->lostGame();

	pauseGame();
	
	checkHighscore();

	m_lvlLoader.restart();

	nextLvl();

}
//--------------------------------------

//==================================================
Controller::~Controller()
{
}
//==================================================