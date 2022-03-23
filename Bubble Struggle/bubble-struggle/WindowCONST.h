//constant information of the window 
//as well as a static window for consistancy.
#pragma once
#include <SFML/Graphics.hpp>


 namespace Window
{
	const int WIND_X=1366, WIND_Y = 700;

	sf::RenderWindow& get();
	
	
};
