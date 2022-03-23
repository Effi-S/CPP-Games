#pragma once
//this is a flaming effect.
//given a position and size
//it draws a falme in the position 
//the size given.
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
class Flame
{
public:
	Flame(sf::Vector2f pos , sf::Vector2f size);
	void draw();

	~Flame();
private:
	std::deque<sf::IntRect> m_animationRects;
	
	sf::RectangleShape m_fire;
	std::deque<sf::IntRect> m_array;
	sf::Clock m_clock;
	bool m_first = true;

};

