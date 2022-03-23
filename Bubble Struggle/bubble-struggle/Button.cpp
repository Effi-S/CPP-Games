#include "Button.h"
#include "WindowCONST.h"
#include "Sound.h"

Button::Button(sf::Vector2f pos, sf::Texture* t, sf::Vector2f size)
{
	m_rect.setPosition(pos);
	m_rect.setSize(size);
	m_rect.setTexture(t);
	m_color = m_rect.getFillColor();
}

void Button::draw()
{
	if (m_mouseOver)
		m_rect.setFillColor(sf::Color::Red);
	else
		m_rect.setFillColor(m_color);

	Window::get().draw(m_rect);
}

bool Button::isMouseOverButton(sf::Vector2f mousePos)
{
	if (m_rect.getGlobalBounds().contains(mousePos))
	{
		if(!m_mouseOver)
			Sound::instance()->reg(ResourceManager::Sound::Click);
		m_mouseOver = true;
	}
	else
		m_mouseOver = false;
	return m_mouseOver;
}

