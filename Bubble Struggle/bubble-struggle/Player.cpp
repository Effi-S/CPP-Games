#include "Player.h"
#include "AbstractWeapon.h"
#include "SimpleArrow.h"
#include "LaserWeapon.h"
#include "WindowCONST.h"
#include "Board.h"
#include "Ball.h"
#include "LaserItem.h"
#include "FrozenArrowItem.h"
#include "SimpleArrowItem.h"
#include "SheildItem.h"
#include "DrawableFactory.h"
#include "RegisterFunctionTemplates.h"
#include "FrozenWeapon.h"
#include "Sheild.h"
#include "Door.h"
#include "GameToolBar.h"

#include "Unmoveable.h"
#include "ResourceManager.h"
#include "SimpleArrow.h"
#include "Wall.h"



Player::Player(sf::Vector2f pos , ResourceManager::Texture img)
{
	m_animationClock.restart();
	
	auto x = ResourceManager::instance()->getTexture(img);
	x->setSmooth(true);	
	m_rect.setTexture(x);
	
	m_rect.setSize(sf::Vector2f(40, 64));
	
	m_rect.setPosition(pos.x , (float)Window::WIND_Y-64);

	sf::IntRect rect(2 * 25, 0, 25, 37);

	m_rect.setTextureRect(rect);

	m_startPos = m_rect.getPosition();

	
}

void Player::shoot()
{
	if (m_weapon.get() == nullptr || m_weapon.use_count() <= 1)
	{
		sf::Vector2f pos(m_rect.getPosition().x + m_rect.getSize().x / 2, m_rect.getPosition().y);

		switch (m_weaponType)
		{
		case Simple:m_weapon = std::make_shared<SimpleArrow>(pos); break;

		case Laser:m_weapon = std::make_shared<LaserWeapon>(pos); break;

		case Frozen: m_weapon = std::make_shared<FrozenWeapon>(pos); break;

		}

		Board::inst().add(m_weapon);
		
	}
	else if (m_weaponType == Frozen)
	{
	Board::inst().remove(m_weapon.get());
	m_weapon = nullptr;
	}

}

void Player::update(float delta)
{	
	

	m_delta = 0.02f;
	switch (m_dir)
	{
	case Direction::Right:
		m_rect.move(m_speed * m_delta, 0);
		break;
	case Direction::Left:
		m_rect.move(-m_speed * m_delta, 0);
		break;
	default: 
		source_x = 2;
	}

	animate();	

	
}

void Player::setMoveDir(sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == m_movingKeys[(size_t)Direction::Idle])
			shoot();
		//--------debug switching arrows---------
		else if (event.key.code == sf::Keyboard::O)
			m_weaponType = (m_weaponType == Simple) ? Laser :
			(m_weaponType == Laser) ? Frozen : Simple;
		//--------debug add sheild------------
		else if (event.key.code == sf::Keyboard::P)
		{
			m_sheild = std::make_shared<Sheild>(*this);
			Board::inst().add(m_sheild);
		}
		//------------------------------------------	
	}

	if (sf::Keyboard::isKeyPressed(m_movingKeys[(size_t)Direction::Right]))
		m_dir = Direction::Right;
	else if (sf::Keyboard::isKeyPressed(m_movingKeys[(size_t)Direction::Left]))
		m_dir = Direction::Left;
	else
		m_dir = Direction::Idle;

}

void Player::draw()
{	
	//draw player
	Window::get().draw(m_rect);

		if (m_myLives->getCount() == 0)
			Board::inst().remove(this);

	
}

void Player::setKeys(std::array<sf::Keyboard::Key, 3> mykeys)
{
	int i = 0;
	for (auto x : mykeys)
	{
		m_movingKeys[i] = x;
			i++;
	}
			
}

void Player::setLivesPos(float x)
{
	m_myLives = std::make_shared<LivesBar>(x);
}

void Player::resetPos()
{
	m_rect.setPosition(m_startPos);
	m_weaponType = WeaponType::Simple;
}

void Player::LoseLife()
{ 
	--*m_myLives;
	
}






void Player::collide(AbsBall & ball)
{
	if (m_sheild.use_count()<=1)
	{
		Board::inst().shadeHere(getPos());
		LoseLife();

	}
	
}

void Player::collide(Wall & wall)
{
	auto pos = m_rect.getPosition();
	auto bounds = wall.getBounds();
	if (bounds.intersects(m_rect.getGlobalBounds()) && bounds.top<pos.y)
	{
		
		if (wall.getBounds().contains(pos))
			m_rect.setPosition(pos.x + m_speed*m_delta, pos.y);
		else
			m_rect.setPosition(pos.x - m_speed*m_delta, pos.y);
		m_delta = 0;
	}

	
		
}


void Player::collide(LaserItem & item)
{
	if (item.getBounds().intersects(m_rect.getGlobalBounds()))
	{
		m_weaponType = Laser;
		item.removeMe();
	}
		
}
void Player::collide(SimpleArrowItem & item)
{
	if (item.getBounds().intersects(m_rect.getGlobalBounds()))
	{
		m_weaponType = Simple ;
		item.removeMe();
	}
}
void Player::collide(FrozenArrowItem & item)
{
	if (item.getBounds().intersects(m_rect.getGlobalBounds()))
	{
		m_weaponType = Frozen;
		item.removeMe();
	}
	
}
void Player::collide(SheildItem & item)
{
	
			m_sheild = std::make_shared<Sheild>(*this);
			Board::inst().add(m_sheild);
		
}
void Player::collide(CashItem & item)
{
	GameToolBar::addScore(100);
};
void Player::collide(TimeItem & item)
{
	m_myLives->setMoreTime();
}
void Player::collide(Door & d)
{
	auto pos = m_rect.getPosition();
	auto bounds = d.getBounds();
	
		if (bounds.contains(pos))
			m_rect.setPosition(pos.x + m_speed * m_delta, pos.y);
		else
			m_rect.setPosition(pos.x - m_speed * m_delta, pos.y);
		m_delta = 0;
	
}
void Player::addLifetoBar(GameToolBar & bar)
{
	bar.addLifeBar(m_myLives);
}
sf::FloatRect Player::getWeaponBounds() const
{
	if (m_weapon.get() == nullptr || m_weapon.use_count() <= 1)
		return sf::FloatRect(-1, -1, 0, 0);

	return m_weapon->getBounds();

}


void Player::animate()
{
	if (m_animationClock.getElapsedTime().asSeconds() < 0.15f)		return;
	
	switch (m_dir)
	{
	case Direction::Right:
		source_x = (source_x == 3) ? 4 : 3;
		break;
	case Direction::Left:
		source_x = (source_x == 0) ? 1 : 0;
		break;
	default: source_x = 2;
	}

	m_rect.setTextureRect(sf::IntRect(source_x * 25, 0, 25, 37));

	m_animationClock.restart();
	
}
