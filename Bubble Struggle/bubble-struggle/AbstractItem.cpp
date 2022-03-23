#include "AbstractItem.h"
#include "ResourceManager.h"
#include "Board.h"
#include "WindowCONST.h"
#include "Player.h"
#include "Unmoveable.h"
#include "Sound.h"

unsigned AbstractItem::m_TotalitemCounter = 0;
AbstractItem::AbstractItem( sf::Vector2f pos ,ResourceManager::Texture img)
{
	sf::Vector2f size(32.f, 42);
	float y_check = Window::WIND_Y-size.y;
	if (pos.y > y_check)pos.y = y_check;

	m_rectangle.setPosition(pos);
	m_rectangle.setSize(size);
	m_rectangle.setTexture(ResourceManager::instance()->getTexture(img));
	m_TotalitemCounter++;
}

void AbstractItem::draw()
{
	Window::get().draw(m_rectangle);
}

void AbstractItem::update(float delta)
{
	auto time = m_groundTime.asSeconds();

	if (time > 3.f && time < 5.f)
	{
		auto tmp = m_rectangle.getFillColor();
		tmp.a -= 10;
		m_rectangle.setFillColor(tmp);
	}		
	else if (m_groundTime.asSeconds() > 5.f)
		Board::inst().remove(this);

	if (m_rectangle.getPosition().y + m_rectangle.getSize().y < Window::WIND_Y)
		m_rectangle.move(0, m_speedLowering);		
	else
		m_groundTime += m_groundTimer.restart();

	m_groundTimer.restart();
	
}

void AbstractItem::removeMe()
{
	Sound::instance()->reg(ResourceManager::Sound::item);
	Board::inst().remove(this);
}
