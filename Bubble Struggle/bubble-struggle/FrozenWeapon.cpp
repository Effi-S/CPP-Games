#include "FrozenWeapon.h"
#include "Board.h"
#include "Wall.h"
#include "Sound.h"

FrozenWeapon::FrozenWeapon(sf::Vector2f pos)
	:AbstractWeapon(sf::Vector2f(pos.x - 0.5f, pos.y), ResourceManager::Texture::FrozenArrow)
{
	Sound::instance()->reg(ResourceManager::Sound::Arrow);
}


FrozenWeapon::~FrozenWeapon()
{
}

void FrozenWeapon::update(float delta)
{
	auto top = getBounds().top;
	if (top <= 0)
	{
		if(m_moving)Sound::instance()->reg(ResourceManager::Sound::frozenArrow);
		m_moving = false;
		
	}
		
	else if(m_moving)
		AbstractWeapon::update(delta);
	else if(!m_moving && m_notMovingTimer.getElapsedTime().asSeconds()>6)
		Board::inst().remove(this);
}

void FrozenWeapon::collide(Wall & wall)
{
	if (wall.getBounds().top < Window::WIND_Y - 100)
	{
		if (m_moving)m_notMovingTimer.restart();

		if (m_moving)
		{
			Sound::instance()->stopArrow();
			Sound::instance()->reg(ResourceManager::Sound::frozenArrow);
		}


		m_moving = false;
	}
	
	
}

void FrozenWeapon::collide(Spikes & spikes)
{
	if (m_moving)m_notMovingTimer.restart();

	if (m_moving)
	{
		Sound::instance()->stopArrow();
		Sound::instance()->reg(ResourceManager::Sound::frozenArrow);
	}

	m_moving = false;
	
}
