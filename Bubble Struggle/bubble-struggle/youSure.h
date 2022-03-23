//this is rectangle for asking if the player is sure 
//he wishes to quit.WindowCONST
#pragma once
#include <SFML/Graphics.hpp>
#include "WindowCONST.h"
class youSure
{
public:
	youSure();
	void draw();
	bool isQuit( class GameToolBar &bar);
	~youSure();
private:
	sf::View m_boardView;
	sf::RectangleShape m_bkg;
	sf::RectangleShape m_yes;
	sf::RectangleShape m_no;
};

