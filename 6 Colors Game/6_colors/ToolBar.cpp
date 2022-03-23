#include "ToolBar.h"
#include "ImageLoader.h"

sf::Color COLOR[6] = {
	sf::Color::Red,
	sf::Color::Blue,
	sf::Color::Green,
	sf::Color::Yellow,
	sf::Color::Magenta,
	sf::Color::Cyan,
};


ToolBar::ToolBar()
{
	int i = 0;
	for (auto &x : m_colors)
	{
		x.setFillColor(COLOR[i]);
		x.setPosition(175.f +i*64.f , 565.f);
		x.setSize(sf::Vector2f(32.f, 32.f));
		x.setOutlineThickness(2);
		x.setOutlineColor(sf::Color::Black);

		x.setTexture(ImageLoader::instance().getSquare());
		i++;
	}

	 i = 0;
	for (auto &x : m_options)
	{
		x.setFillColor(sf::Color(85	,107, 47));
		x.setPosition(170.f + i * 100.f, 10.f);
		x.setSize(sf::Vector2f(64.f, 32.f));
		x.setOutlineThickness(2);
		x.setOutlineColor(sf::Color::Black);
		x.setTexture(ImageLoader::instance().getTool(i));
		i++;
	}

}

//drawing both rectangle vectors onto wind( a render window given)
void ToolBar::draw(sf::RenderWindow &wind)
{
	
	for (auto &x : m_colors)		
		wind.draw(x);		
	

	for (auto & x : m_options)
		wind.draw(x);
}

//returns the users choice from option toolbar.
//the mouse place is found from event.
//mouseplace is a mouse hovering position
//mouseClick is a mouse click position
int ToolBar::getOptionChoice(sf::RenderWindow &window, sf::Event &event)
{
	sf::Vector2f mouseplace(window.mapPixelToCoords({ event.mouseMove.x ,event.mouseMove.y }));

	sf::Vector2f mouseClick(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }));

	int i = 0;
	for (auto & x : m_options)
		if (x.getGlobalBounds().contains(mouseplace))
			x.setFillColor(sf::Color::Yellow);
		else if (x.getGlobalBounds().contains(mouseClick))
		{
			x.setFillColor(sf::Color::Yellow);
			if (i == 2)x.setTexture(ImageLoader::instance().getTool(i));
			return i+1;
		}

		else
		{
			x.setFillColor(sf::Color(85, 107, 47));
			i++;
		}
			

	return 0;
}

//returns the users color chosen from the six possible colors for a turn
//the mouse place is found from event.
//mouseplace is a mouse hovvering position
//mouseClick is a mouse click position
//the user cannot choose p1Color or p2Color that are given
sf::Color ToolBar::getTurnChoice(sf::RenderWindow &window ,sf::Event &event, sf::Color p1Color, sf::Color p2Color)
{
	
	sf::Vector2f mouseplace(window.mapPixelToCoords({ event.mouseMove.x ,event.mouseMove.y }));

	sf::Vector2f mouseClick(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }));
	
	
	int i = 0;
	for (auto &x : m_colors)
	{
		if (COLOR[i] == p1Color || COLOR[i] == p2Color)
			x.setTexture(ImageLoader::instance().getXSquare());
		else
		{
			x.setFillColor(COLOR[i]);
			x.setTexture(ImageLoader::instance().getSquare());
		}

		if(x.getTexture() != ImageLoader::instance().getXSquare())
			if (x.getGlobalBounds().contains(mouseplace) )
			{
				auto color = COLOR[i];
				color.a -= 120;
				x.setFillColor(color);
			}		
			else if (x.getGlobalBounds().contains(mouseClick) )
			{
				auto color = COLOR[i];
				x.setFillColor(color);
				x.setTexture(ImageLoader::instance().getXSquare());
				return COLOR[i];

			}			
			else
				x.setFillColor(COLOR[i]);
				
				i++;
	}
	
				
	return sf::Color::White;
}
	



ToolBar::~ToolBar()
{
}

		
	

	
		

		
