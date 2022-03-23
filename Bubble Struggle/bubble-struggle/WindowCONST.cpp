#include "WindowCONST.h"


sf::RenderWindow & Window::get()
{
	static sf::RenderWindow wind(sf::VideoMode(WIND_X, WIND_Y), "Bubble Trouble Game"
		);
	return wind;
}

