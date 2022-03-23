#include "Controller.h"
#include <sstream>

const int window_x = 700, window_y = 700;

Controller::Controller()
:	m_window(sf::VideoMode(window_x, window_y),
		"6 colors", sf::Style::Titlebar | sf::Style::Close)	
{
	m_board = std::make_unique<Board>(43, 28);
	makePercent();
	m_person1 = Person(m_board->getPlayer1Cell()) ;
	m_person2 = Person(m_board->getPlayer2Cell());
	m_computer = CPU(m_board->getPlayer2Cell());

	restart();
}


//run function:
//this function runs the game.
//it opens a window and prints the board to the screen untill the 
//window is close.
void Controller::run()
{	
	while (m_window.isOpen())
	{
		m_window.clear(sf::Color(202, 225, 255, 255));

		m_board->draw(m_window);
		m_toolBar.draw(m_window);
		drawPercent();
		m_window.display();

		checkGameWon(m_player1);
		checkGameWon(m_player2);

					
		if (m_window.waitEvent(m_event))
		{
			if (m_event.type == sf::Event::Closed) m_window.close();

			if (m_event.type == sf::Event::MouseButtonPressed ||
				m_event.type == sf::Event::MouseMoved)
			{
				checkToolBar();		
			}
	
			switch (m_state) {//playing the players turns based on state: multiplayer/singleplayer
			case SinglePlayer:	playTurn(); break;
			case MultiPlayer: multiTurn(); break;

			}
		}
			

	}
}

//creating fonts and texts to print to the screen.
void Controller::makePercent() 
{
	m_font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

	 m_p1Text=sf::Text("00", m_font, 14);
	 m_p2Text=sf::Text("00", m_font, 14);

	m_p1Text.setFillColor(sf::Color::Black);
	m_p2Text.setFillColor(sf::Color::Black);

	m_p1Text.setOutlineThickness(3.f);
	m_p2Text.setOutlineThickness(3.f);

	m_p2Text.setOutlineColor(sf::Color::Yellow);
	m_p1Text.setOutlineColor(sf::Color::Yellow);
	
	
	m_p1Text.setPosition(30, 570);
	m_p2Text.setPosition(600, 570);
	
}

//this function prints each players percent of the boaard 
//occupide using a stringstream  to get input into const strings
//that are printed as sfml texts.
void Controller::drawPercent()
{
	if (!m_player1 || !m_player2)return;
	//creating local info strings :
	char percent1Str[30] = { ' ' }, percent2Str[30] = { ' ' };
	std::stringstream ss;

	ss << m_player1->getPercent(m_board->getCellsCount());
	ss >> percent1Str;

	m_p1Text.setString(percent1Str);
	
	ss.clear();

	ss << m_player2->getPercent(m_board->getCellsCount());

	ss >> percent2Str;

	m_p2Text.setString(percent2Str);


		m_window.draw(m_p1Text);
		m_window.draw(m_p2Text);

}

//a multiplayer turn 
void Controller::multiTurn()
{
	sf::Color color = m_toolBar.getTurnChoice(m_window, m_event, m_player1->getColor(), m_player2->getColor());
	
	if (color != sf::Color::White)
	{
		static bool flag = true;
		if (flag)
			m_player1->move(color);
		else
			m_player2->move(color);

		flag = !flag;
	}
}
	
//a single player turn.
void Controller::playTurn()
{
	sf::Color color = m_toolBar.getTurnChoice(m_window, m_event, m_player1->getColor(), m_player2->getColor());
	
	if (color != sf::Color::White)
	{
		m_player1->move(color);		
		m_player2->move(color);
		
	}
	
}

//restarting the board and the players.
void Controller::restart()
{

	m_board->restart();
	m_player1->restart();
	m_player2->restart();
	
}

//changes the size of the board 
//to one of three options:
//1)43 X 28 (default)
//2)15X15 
//3)25X25
void Controller::resize()
{	
	static int i = 0;

	switch (i) {
	case (0):
		m_board = std::make_unique<Board>(15, 15); break;
	case (1):
		m_board = std::make_unique<Board>(25, 25); break;
	case (2):
		m_board = std::make_unique<Board>(43, 28); break;
	}
	(i == 2) ? i = 0 : i++;

	m_person1 = Person(m_board->getPlayer1Cell());
	m_person2 = Person(m_board->getPlayer2Cell());
	m_computer = CPU(m_board->getPlayer2Cell());

	restart();
}

//switches the current turn type 
//multiplayer or single player
//(opposite of current mode)
void Controller::changeMode()
{	
	restart();

	static bool flag = true;
	if (flag)
	{
		m_player2 = &m_person2;
		m_state = MultiPlayer;
		flag = false;
	}
	else
	{
		m_player2 = &m_computer;
		m_state = SinglePlayer;
		flag = true;
	}
}

//checks if player's percent of board filled 
//is greater or equal to 50 percent and restarts the game if so.
void Controller::checkGameWon(Player * player)
{

	if (player->getPercent(m_board->getCellsCount()) >= 50)
	{
		player->iWin();
		restart();		
	}

}

//checks is the user chose an option from the toolbar 
//(not a turn ) and implements his choice.
void Controller::checkToolBar()
{
	int choice = m_toolBar.getOptionChoice(m_window, m_event);


	switch (choice) {
	case(1):restart();break;
	case(2):resize();break;
	case(3):changeMode();break;
	case(4):m_window.close(); break;
	}
	
		
}

