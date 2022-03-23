#include "AbstractWeapon.h"
#include "WindowCONST.h"
#include "Unmoveable.h"
#include "Board.h"
#include "AbsBall.h"
#include "Wall.h"
#include "Sound.h"


AbstractWeapon::AbstractWeapon(sf::Vector2f pos, ResourceManager::Texture tex)
	: m_pos(pos)
{	
	m_sprite.setTexture(*ResourceManager::instance()->getTexture(tex));
	m_sprite.setPosition(m_pos);
	
}

void AbstractWeapon::collide(Unmoveable & other)
{
	other.collide(*this);
}

void AbstractWeapon::update(float delta)
{
	auto pos = m_sprite.getPosition();	

	m_sprite.setPosition(pos.x , pos.y -m_speed * m_clock.restart().asSeconds());

	if (pos.y <= 0)Board::inst().remove(this);
	
}

void AbstractWeapon::draw()
{
	Window::get().draw(m_sprite);
}

void AbstractWeapon::collide(Wall & wall)
{
	if (wall.getBounds().top < Window::WIND_Y - 100)
	{
		Sound::instance()->stopArrow();
		Board::inst().remove(this);
	}
} 

void AbstractWeapon::collide(Spikes & spikes)
{
	Board::inst().remove(this);
}

void AbstractWeapon::collide(AbsBall & ball)
{
	ball.collide(*this);
	Board::inst().remove(this);

}

void AbstractWeapon::setScale(const float factor)
{
	if (factor < 4 && 0 < factor)
	{
		m_sprite.setOrigin(factor, factor);
		m_sprite.setScale(factor , factor);
		
			
	}

}
