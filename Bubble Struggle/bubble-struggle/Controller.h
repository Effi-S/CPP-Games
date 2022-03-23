//This is the Controller class 
//it controlls the gameplay of the game 
//it holds the LevelLoader and decides when to load levels and which.
//it runs the time of the game and finihes or ends the game.
// for this it holds the game toolbar and gets information via it and the board.
#pragma once
#include "LevelLoader.h"
#include "Board.h"
#include "GameToolBar.h"

class Controller
{
public:
	Controller() = default;
	void run();
	void init(bool multiPlayer = false);
	~Controller() = default;
private:
	void doTurn();
	void doTimeUp();
	void resize();
	void outOfTime();
	void display(ResourceManager::Texture img);
	void restartLevel();
	void displayScoreScreen();
	bool handleEvents();
	bool isGameOver(); 
	bool isGameWon();
	bool isLevelWon();

	Board& m_board = Board::inst();//reference to the static board
	LevelLoader m_loader; // the Level Loader for loading the correct board
	GameToolBar m_bar; // the toolbar at the bottom of the screen 
	
	sf::Event m_event; // for the mouse events and screen events
	sf::Clock m_gameTimer; // timing each turn 
	sf::Time m_elapsed;// time since ^^ restarted
	sf::Clock m_waitTimer; // timing a transition pause in the game.
	sf::Clock m_clock; // updating clock
	sf::Time m_time = sf::seconds(0.03f); // the time of the turns 
};

