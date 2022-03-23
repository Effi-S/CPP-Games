#include "Menu.h"
#include "WindowCONST.h"
#include <SFML/Graphics.hpp>
#include "Sound.h"

void Menu::run()
{
	show();
	Sound::instance()->play_bg();
	handleEvents();
	Sound::instance()->clear();
}

void Menu::show()
{
	//set backgreound texture
	Window::get().setView(Window::get().getDefaultView());
	m_bgTexture = (m_bgTexture) ? m_bgTexture : m_defaultBgTexture;
	m_bg.setTexture(*m_bgTexture);

	//draw all menu elements
	Window::get().draw(m_bg);
	m_flame1.draw();
	m_flame2.draw();
	for (const auto& option : m_options)
		option.second->draw();
}

void Menu::handleEvents()
{
	sf::Event event;
	if (Window::get().pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			Window::get().close();

		if (event.type == sf::Event::MouseButtonReleased)
		{
			sf::Vector2f mousePos = Window::get().mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
			if (event.mouseButton.button == sf::Mouse::Button::Left)
				for (const auto& option : m_options)
					if (option.second->isMouseOverButton(mousePos))
						option.second->execute();

		}

		if (event.type == sf::Event::MouseMoved)
		{
			sf::Vector2f mousePos = Window::get().mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
			m_bgTexture = m_defaultBgTexture;
			for (const auto& option : m_options)
				if (option.second->isMouseOverButton(mousePos))
					m_bgTexture = option.second->getBgTexture();
		}
	}
}
