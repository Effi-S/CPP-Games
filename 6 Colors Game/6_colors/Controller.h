// Controller class.
//this class controls the game play.
//it holds  a sfml renderwindow and event 
//as well as a board and two players 
//it decides when the players turn prints the board 
//checks who wins based on the percentage of the board filled 
//(and prints the percentages onto the screen )
//it holds a toolbar that is incharge of receiveing 
//the users request be it a turn or 
//changing a setting/mode 
//(as well as resizing the boad and multiplayer options)
#pragma once
#include "ToolBar.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Board.h"
#include "Player.h"
#include "Person.h"
#include "CPU.h"

enum GameState {
	SinglePlayer,
	MultiPlayer
};

class Controller
{
public:
	Controller();
	void run();
	~Controller() = default;
private:	
	void makePercent();
	void drawPercent();
	void playTurn();
	void multiTurn();
	
	void restart();
	void resize();
	void changeMode();
	void checkGameWon(Player * player);
	void checkToolBar();
	
	sf::RenderWindow m_window;//the render window
	ToolBar m_toolBar; //the toolbar for getting users choices
	std::unique_ptr<Board>  m_board; //the game board 
		
	sf::Event m_event;
	GameState m_state = SinglePlayer; //the current game mode
	
	
	sf::Font m_font; 
	sf::Text m_p1Text;
	sf::Text m_p2Text;
	
	Player *m_player1 = &m_person1; //these are two pointers 
	Player *m_player2 = &m_computer;//to the players playing currently
	//the options for the two pointers:

	CPU m_computer;//computer
	Person m_person1;//p1
	Person m_person2;//p2

};