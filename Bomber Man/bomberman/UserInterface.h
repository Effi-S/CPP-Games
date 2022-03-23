/***************UserInterface class**************
//this is the user interface class incharge of interaction
//with the user outside the game
//it has 2 i rectangle arrays:
// 1) the menu for when the game is not beeing played
// 2) the toolbar for when the game is beeing played.

it also prints to the screen on the whole
screen images that explain to the user
what has happend in the game.
******************************************/

//============include section================
#pragma once
#include "CONSTS.h"
const int MENU_ITEMS=4;
const int TOOLBAR_ITEMS=7;
#include <vector>
//------------------------------------------

class UserInterface
{
public:
	UserInterface(sf::RenderWindow &window);
	
	void draw();
	void drawMenu();
	void drawToolbar();


	
	void youLost()  ;
	void youWon()  ;
	void timesUp()  ;
	void newHighscore()  ;
	void runHelp() const ;
	void runHighscore() const ;
	
	action_t RunMenu(const sf::Vector2f &mouseplace, const  sf::Vector2f &mouseClick,  sf::Event & event);
	action_t Run( sf::Event &event);
	action_t RunBar(const sf::Vector2f &mouseplace, const  sf::Vector2f &mouseClick, sf::Event & event);
	
	bool inGame() const;
	 
	


	~UserInterface();
private:
	
	void printToScreen(sf::Texture &) const;

	sf::Event m_event;
	bool m_inGame = false;
	bool m_restart = false;
	
	sf::RenderWindow &m_window;

	sf::RectangleShape m_menu[MENU_ITEMS];
	sf::RectangleShape m_toolbar[TOOLBAR_ITEMS];


	sf::Texture m_toolbarImages[TOOLBAR_ITEMS] ;
	sf::Texture m_menuImages[MENU_ITEMS];

	sf::Texture m_youLost;
	sf::Texture m_youWon;
	sf::Texture m_wallpaper;
	sf::Texture m_timesUp;
	sf::Texture m_newHighscore;
	sf::Texture m_help;
};

