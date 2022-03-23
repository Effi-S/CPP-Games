/***************UserInterface class**************
this is the user interface class incharge of interaction 
with the user outside the game 
it has 2 i rectangle arrays: 
 1) the menu for when the game is not beeing played 
 2) the toolbar for when the game is beeing played.

it also prints to the screen on the whole 
screen images that explain to the user 
what has happend in the game.
******************************************/

//============include section================
#include "UserInterface.h"
#include <SFML/System.hpp>
#include <fstream>
#include <Windows.h>
//=============================================

//========constructor===============
UserInterface::UserInterface(sf::RenderWindow &window)
	:m_window(window)
{
	//loading  menu images
	m_menuImages[0].loadFromFile("menu_buttons/play.png");
	m_menuImages[1].loadFromFile("menu_buttons/help.png");
	m_menuImages[2].loadFromFile("menu_buttons/highscore.png");
	m_menuImages[3].loadFromFile("menu_buttons/exit.png");

	//loading toolbar images
	m_toolbarImages[0].loadFromFile("toolbar_buttons/pause.png");
	m_toolbarImages[1].loadFromFile("toolbar_buttons/replay.png");
	m_toolbarImages[2].loadFromFile("toolbar_buttons/time.png");
	m_toolbarImages[3].loadFromFile("toolbar_buttons/lives.png");
	m_toolbarImages[4].loadFromFile("toolbar_buttons/bombs.png");
	m_toolbarImages[5].loadFromFile("toolbar_buttons/score.png");
	m_toolbarImages[6].loadFromFile("toolbar_buttons/level.png");
	

	//loading menu
	for (int i = 0; i < MENU_ITEMS; i++)
	{
		m_menu[i].setSize(MENU_BUTTONSIZE);
		m_menu[i].setPosition(sf::Vector2f(2*MENU_BUTTONSIZE.x , 2*MENU_BUTTONSIZE.y +i*MENU_BUTTONSIZE.y));
		m_menu[i].setOutlineThickness(2.f);
		m_menu[i].setOutlineColor(sf::Color::Magenta);
		
		m_menu[i].setTexture(&m_menuImages[i]);

	}

	//loading toolbar
	for (int i = 0; i < TOOLBAR_ITEMS; i++)
	{	
		m_toolbar[i].setSize(TOOLBAR_BUTTONSIZE);
		m_toolbar[i].setPosition(sf::Vector2f(i*TOOLBAR_BUTTONSIZE.x  ,0.f ));
		m_toolbar[i].setTexture(&m_toolbarImages[i]);
		m_toolbar[i].setFillColor(TOOL_CLEAR);
	}

	m_toolbar[0].setOrigin(-0.01f, -0.01f); //dont know why, but VERY important.

	//loading extra images
	m_wallpaper.loadFromFile("images/wallpaper.png");
	m_youLost.loadFromFile("images/youlost.png");
	m_youWon.loadFromFile("images/youwon.png");
	m_timesUp.loadFromFile("images/timesUp.png");
	m_help.loadFromFile("images/help.png");
	m_newHighscore.loadFromFile("images/highScore.png");

	m_inGame = false;

}
//=============================

//drawing the menu or the bar
//depending on if in the game or not.
void UserInterface::draw()
{
	sf::View  gameView;

	gameView = m_window.getView();

	m_window.setView(m_window.getDefaultView());
	
	(m_inGame) ?drawToolbar() : drawMenu();

	m_window.setView(gameView);
}
//---------------------------

//==========draw the menu============
void UserInterface::drawMenu()
{

	m_window.clear(MENU_CLEAR);


	for (int i = 0; i < MENU_ITEMS; ++i)
	{
		m_menu[i].setPosition(sf::Vector2f(2 * MENU_BUTTONSIZE.x,
			2 * MENU_BUTTONSIZE.y + i * MENU_BUTTONSIZE.y));

		m_window.draw(m_menu[i]);
	}
		
}
//-------------------------------

//======draw the toolbar==============
void UserInterface::drawToolbar()
{
	for (int i = 0; i < TOOLBAR_ITEMS; ++i)
	{
		m_toolbar[i].setPosition(sf::Vector2f(i*TOOLBAR_BUTTONSIZE.x, 2.f));
		m_window.draw(m_toolbar[i]);
	}
		
}
//-------------------------------
//============
//printing on the whole screen an image 
// for 3 seconds.

void UserInterface::printToScreen(sf::Texture &img) const
{
	m_window.setView(m_window.getDefaultView());

	sf::Vector2f viewSize(m_window.getView().getSize());

	sf::FloatRect currentViewRect();

	sf::RectangleShape rect;

	rect.setPosition(0.f, 0.f);

	rect.setTexture(&img);

	rect.setSize(viewSize);

	m_window.clear();

	m_window.draw(rect);

	m_window.display();

	Sleep(3000);
}
//=============================

//===========================
void UserInterface::youLost() 
{	
	m_inGame = false;
	printToScreen(m_youLost);
}
//----------------------------
//===========================
void UserInterface::youWon() 
{
	m_inGame = false;
	printToScreen(m_youWon);

}
//--------------------------

//--------------------------
void UserInterface::timesUp() 
{
	printToScreen(m_timesUp);
}
//-----------------------------

void UserInterface::newHighscore() 
{
	printToScreen(m_newHighscore);
}
//--------------------------------

//==================================
//running the menu or the bar 
//based on if in the game or not 
//receives an event into event and retreives 
//from the event the mouse position 

action_t UserInterface::RunMenu(const sf::Vector2f &mouseplace ,const  sf::Vector2f &mouseClick, sf::Event & event)
{	
		
		 for (int i = 0; i < MENU_ITEMS; i++)
			{
				if (m_menu[i].getGlobalBounds().contains(mouseplace))
				{
					m_menu[i].setFillColor(sf::Color::Yellow);

				}
				else if (m_menu[i].getGlobalBounds().contains(mouseClick))
				{
					m_menu[i].setFillColor(sf::Color::Cyan);

					switch (i)
					{
					case(play_t):   m_inGame = true;
								    return PAUSE;break;		
					case(helpMe_t):runHelp(); break;
					case(highScore_t): runHighscore(); break;
					case(exitGame_t): return CLOSE; break;

					}
					
				}
				else
					m_menu[i].setFillColor(sf::Color::White);
			}	

		 return NO_ACTION;
}
//---------------------------------------------

action_t UserInterface::Run( sf::Event & event)
{
	//retreiving mouse pos 
	sf::View gameView = m_window.getView();

	m_window.setView(m_window.getDefaultView());

	sf::Vector2f mouseplace(m_window.mapPixelToCoords({ event.mouseMove.x ,event.mouseMove.y }));

	sf::Vector2f mouseClick(m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }));
		
	m_window.setView(gameView);

	//calling  toolbar or menu.

	if (!m_inGame)
		return RunMenu(mouseplace, mouseClick, event);
	
	return	RunBar(mouseplace, mouseClick, event);
	
}

action_t UserInterface::RunBar(const sf::Vector2f & mouseplace, const sf::Vector2f & mouseClick, sf::Event & event)
{
	for (int i = 0; i < (int)bar_time_t; ++i)
	{
		if (m_toolbar[i].getGlobalBounds().contains(mouseplace))
			m_toolbar[i].setFillColor(sf::Color::Yellow);
		
		else if (m_toolbar[i].getGlobalBounds().contains(mouseClick))
		{
			m_toolbar[i].setFillColor(sf::Color::Cyan);	
			switch (i)
			{
			case(bar_pause_t):
								m_inGame = false;
								return PAUSE; break;
			case(bar_restart_t):return RESTART; break;
			}
		
		}
		else
			m_toolbar[i].setFillColor(sf::Color::Color(216, 216, 255, 216));

	}
	return NO_ACTION;
}
//==============================

//returns if game in session or not
bool UserInterface::inGame() const
{
	return m_inGame;
}
//===============================


//================================
//runs the help menu.
void UserInterface::runHelp() const 
{
	sf::RenderWindow window(sf::VideoMode(defwindow_y * 2, defwindow_x), "RULES:", sf::Style::Default);

	window.setView(window.getDefaultView());

	sf::Vector2f viewSize(window.getView().getSize());

	sf::FloatRect currentViewRect();

	sf::RectangleShape rect;

	rect.setPosition(0.f, 0.f);
	rect.setSize(viewSize);

	rect.setTexture(&m_help);

	m_window.setActive(false);

	window.setActive(true);

	while (window.isOpen())
	{		
		

		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.setActive(false);

				window.close();

				break;
			}

			
		}
		
		window.clear(sf::Color(215, 255, 245, 255));

		window.draw(rect);

		window.display();
	}

	m_window.setActive(true);
}
//======================

//prints the highscore to the screen.
void UserInterface::runHighscore() const 
{
	std::string str;

	std::fstream FILE("Highscore.txt");

	if (!FILE.is_open())
		return;

	getline(FILE, str);

	sf::Font font;

	font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

	sf::Text text(str, font, 24);

	text.setFillColor(sf::Color::Blue);

	//-----opening window

	sf::RenderWindow window(sf::VideoMode(defwindow_x/2 , defwindow_x/4), "Highscore:", sf::Style::Default);

	m_window.setActive(false);

	window.setActive(true);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.setActive(false);

				window.close();

				break;
			}


		}
		window.clear(sf::Color(215, 255, 245, 255));

		text.setString(str);

		window.draw(text);

		window.display();
	}

	m_window.setActive(true);
}
//=============================


//=============================
UserInterface::~UserInterface()
{
}
//---------------------------------