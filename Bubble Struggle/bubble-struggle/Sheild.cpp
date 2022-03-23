#include "Sheild.h"
#include "AbsBall.h"
#include "Board.h"
#include "WindowCONST.h"


Sheild::Sheild(Player &player)
	:m_player(player)
{
	m_circ = sf::CircleShape(m_player.getBounds().height+15);

	m_circ.setOrigin(m_circ.getRadius(), m_circ.getRadius());
	m_circ.setPosition(sf::Vector2f(m_player.getPos().x+ m_player.getBounds().width/2 ,Window::WIND_Y));
	m_circ.setTexture(ResourceManager::instance()->getTexture(ResourceManager::Texture::Sheild));
	
	auto color = sf::Color::Yellow;
	color.a = 10;
	m_circ.setFillColor(color);

}


void Sheild::update(float delta)
{
	m_circ.setPosition(sf::Vector2f(m_player.getPos().x + m_player.getBounds().width / 2, Window::WIND_Y-15));
	
	auto time = m_Countdowntimer.getElapsedTime().asSeconds();

	if ( time< 3)
	{
		auto tmp = m_circ.getFillColor();
		tmp.a += (unsigned)time * 10;
		m_circ.setFillColor(tmp);
	}
	else if (time > 3 && time<5)
	{
		m_circ.setFillColor(sf::Color::Yellow);
	}
	else if (time > 15 && time < 17)
	{
		auto tmp = m_circ.getFillColor();
		tmp.a -= (unsigned)time * 10;
		m_circ.setFillColor(tmp);
	}
	else if (time > 17)
		Board::inst().remove(this);
}

void Sheild::draw()
{
	Window::get().draw(m_circ);
}

void Sheild::collide(AbsBall & ball)
{
	ball.collide(*this);
}

Sheild::~Sheild()
{
}
