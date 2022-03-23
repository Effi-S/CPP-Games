//this is the toolbar class 
//it holds two vectors of sfml rectangle shapes 
//one for the toolbar on the top of the screen 
//the other for the 6 colors the player can choose from in his turn 
//this class can return the users choice for both of these.
#pragma once
#include <SFML/Graphics.hpp>
class ToolBar
{
public:
	ToolBar();
	void draw(sf::RenderWindow &wind);
	sf::Color getTurnChoice(sf::RenderWindow &e ,sf::Event &, sf::Color p1Color, sf::Color p2Color);
	int getOptionChoice(sf::RenderWindow &e, sf::Event &);

	~ToolBar();
private:
	sf::RectangleShape m_colors[6];//the users color options in turn
	sf::RectangleShape m_options[4];//the game options
};

