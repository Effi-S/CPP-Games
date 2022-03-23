#include "Flame.h"
#include "WindowCONST.h"





Flame::Flame(sf::Vector2f pos, sf::Vector2f size)
{
	
	m_fire.setSize(size);
	
	m_fire.setPosition(pos);
	m_fire.setTexture(ResourceManager::instance()->getTexture(ResourceManager::Texture::MovingFire));
	m_array = ResourceManager::instance()->getAnimationArray(4, 4, ResourceManager::Texture::MovingFire);
	m_fire.setTextureRect(m_array.front());

	
	
}

void Flame::draw()
{
	
	if (m_clock.getElapsedTime().asSeconds() > 0.2)
	{
		sf::IntRect x = m_array.front();
		m_array.pop_front();
		m_array.push_back(x);
		m_fire.setTextureRect(x);
		m_clock.restart();
		
		
	}
	
	auto &wind = Window::get();
	
	wind.draw(m_fire);
}

Flame::~Flame()
{
}
