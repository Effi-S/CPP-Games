#include "LaserWeapon.h"
#include "Sound.h"
LaserWeapon::LaserWeapon(sf::Vector2f pos)
	:AbstractWeapon(sf::Vector2f(pos.x-22, pos.y), ResourceManager::Texture::LaserArrow)
{
	Sound::instance()->reg(ResourceManager::Sound::Laser);
	m_elapsed= sf::seconds(1.5);
	m_scaleClock.restart();
}

void LaserWeapon::update(float delta)
{
	
	m_elapsed += m_scaleClock.restart();

	setScale( m_elapsed.asSeconds());
	AbstractWeapon::update(delta);
}


