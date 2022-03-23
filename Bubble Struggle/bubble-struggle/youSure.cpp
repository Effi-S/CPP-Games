#include "youSure.h"
#include "ResourceManager.h"
#include "Board.h"
#include "GameToolBar.h"


youSure::youSure()
{
	sf::Vector2u size = Window::get().getSize();
	m_boardView.reset(sf::FloatRect(0.f, 0.f, (float)size.x, (float)size.y));
	m_boardView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 0.80f));

	m_bkg.setPosition(Window::WIND_X*0.3f, Window::WIND_Y*0.7f);
	m_no.setPosition(Window::WIND_X*0.32f, Window::WIND_Y*0.85f);
	m_yes.setPosition(Window::WIND_X*0.38f, Window::WIND_Y*0.85f);

	m_bkg.setSize(sf::Vector2f(200.f, 200.f));
	m_no.setSize(sf::Vector2f(50.f, 50.f));
	m_yes.setSize(sf::Vector2f(50.f, 50.f));

	m_bkg.setTexture(ResourceManager::instance()->getTexture(ResourceManager::Texture::youSure));
	
	m_yes.setFillColor(sf::Color::Yellow);
	m_no.setFillColor(sf::Color::Yellow);
}


void youSure::draw()
{
	
	auto & wind = Window::get();
	wind.setView(m_boardView);	
	
	wind.draw(m_yes);
	wind.draw(m_no);
	wind.draw(m_bkg);

	wind.getDefaultView();
}

bool youSure::isQuit(GameToolBar &bar )
{
	sf::RenderWindow & wind = Window::get();
		sf::Event event;
	while (wind.isOpen())
	{
		wind.clear(sf::Color(95, 95, 95));
		Board::inst().draw();
		bar.draw();
		draw();

		wind.display();
		
		while (wind.pollEvent(event))
		{

			if (event.type ==sf::Event::Closed)
				wind.close();

			else if (event.type == sf::Event::MouseButtonReleased)
			{
				sf::Vector2f mousePos = Window::get().mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
				if (m_yes.getGlobalBounds().contains(mousePos))
					return true;
				else if (m_no.getGlobalBounds().contains(mousePos))
					return false;

			}

			else if (event.type == sf::Event::MouseMoved)
			{
				sf::Vector2f mousePos = Window::get().mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
				
				if (m_yes.getGlobalBounds().contains(mousePos))
					m_yes.setFillColor(sf::Color::Red);
				else
					m_yes.setFillColor(sf::Color::Yellow);

				if (m_no.getGlobalBounds().contains(mousePos))
					m_no.setFillColor(sf::Color::Red);
				else  
					m_no.setFillColor(sf::Color::Yellow);
			}
		}
		
	}

	return false;

}


youSure::~youSure()
{
}
