#include "Unmoveable.h"
#include"Moveable.h"
#include "WindowCONST.h"
#include"ResourceManager.h"
#include "Board.h"
Unmoveable::Unmoveable(sf::Vector2f pos, sf::Vector2f size, ResourceManager::Texture img)
{
	m_rect.setSize(size);
	m_rect.setPosition(pos);
	m_rect.setTexture(ResourceManager::instance()->getTexture(img));

}

void Unmoveable::draw()
{
	Window::get().draw(m_rect);
}

void Unmoveable::setTextur(sf::Texture * img)
{
	img->setSmooth(false);
	img->setRepeated(false);
	m_rect.setTexture(img);
	
}

void Unmoveable::setTextureRect( sf::Vector2f  pos ,sf::Vector2f  size )
{
		
	sf::IntRect rect( (int)pos.x, (int)pos.y, (int)size.x ,(int)size.y);
	m_rect.setTextureRect(rect);
	m_rect.setOutlineThickness(1.f);
	m_rect.setOutlineColor(sf::Color(170,170,170,255));
	m_rect.setSize(sf::Vector2f(size.x - 2.f, size.y - 2.f));
}

void Unmoveable::fadeUp()
{
	auto x= m_rect.getPosition();

	x.y -= 10;
	if (x.y < Window::WIND_Y-2*m_rect.getSize().y)
		Board::inst().remove(this);
	else
	{
		auto y = m_rect.getFillColor();
		y.a -= 10;
		m_rect.setFillColor(y);
		m_rect.setPosition(x);
	}
	
	
}

