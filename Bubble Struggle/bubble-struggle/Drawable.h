//this is a abstract drawable base class
//for all objects that can be drawn onto the screen by the board.
#pragma once
#include <SFML/Graphics.hpp>


class Drawable
{
public:
	Drawable() = default;
	
	~Drawable() = default;
	virtual void draw()=0;
	
	virtual void collide(class Moveable & other) = 0;
	virtual void collide(class Unmoveable & other) = 0;
	virtual sf::FloatRect getBounds() const { return sf::FloatRect(); };

	
	
	
};

