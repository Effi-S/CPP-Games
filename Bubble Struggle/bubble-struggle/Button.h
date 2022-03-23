//this is the Button class
//a simple class for a button that recognizes if the mouse
//is within it's bounds and draw itself differently if so.
#pragma once
#include <SFML/Graphics.hpp>

class Button
{
public:
	Button(sf::Vector2f pos, sf::Texture* t, sf::Vector2f size);
	~Button() = default;
	void draw();

	void setIsOver(bool flag) { m_mouseOver = flag; }
	bool isMouseOverButton(sf::Vector2f mousePos);

private:
	sf::RectangleShape m_rect;
	bool m_mouseOver = false;
	sf::Color m_color;
};

