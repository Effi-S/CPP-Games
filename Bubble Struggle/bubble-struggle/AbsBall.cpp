#include "AbsBall.h"
#include <iostream>
#include <sstream>
#include <string>
#include "WindowCONST.h"
#include "Board.h"
#include "Wall.h"
#include "Ball.h"
#include "DrawableFactory.h"
#include "AbstractItem.h"
#include "Door.h"
#include "Spikes.h"
#include "HeldBall.h"
#include "GameToolBar.h"
#include "Sound.h"
#include "Unmoveable.h"

#include "Door.h"

unsigned AbsBall::m_GlobalAbsBallCounter = 0;
AbsBall::AbsBall(float radius, sf::Vector2f pos, bool inverse)
{
	rangeCheck(radius);
	rangeCheck(pos);

	m_ball = sf::CircleShape(radius - 1);
	m_ball.setOutlineThickness(1);
	m_ball.setOutlineColor(sf::Color::Black);
	m_ball.setFillColor(COLOR[(unsigned)radius / 10 - 1]);
	m_ball.setOrigin(m_ball.getRadius(), m_ball.getRadius());
	m_ball.setPosition(pos);

	m_ball.setTexture(ResourceManager::instance()->getTexture(ResourceManager::Texture::ball));

	if (inverse) {
		m_direction.x *= -1;
		generateItem(pos);
		GameToolBar::addScore((int)radius * 2);
	}
	m_direction.y -= 1.f;

	m_GlobalAbsBallCounter++;

}



void AbsBall::draw( )
{
	Window::get().draw(m_ball);
}

void AbsBall::update(float delta)
{						
		auto pos = m_ball.getPosition();
		
		m_direction.y +=Gravity();
	
		 m_nextPos=sf::Vector2f(pos.x + m_direction.x ,pos.y + m_direction.y);

		 checkInBounds();

		 m_ball.setPosition(m_nextPos);

}

void AbsBall::setColor(sf::Color color)
{
	m_ball.setFillColor(color);
}

sf::Vector2f AbsBall::getCenter() const
{
	return m_ball.getPosition();
}

float AbsBall::getRad() const
{
	return m_ball.getRadius();
}
sf::FloatRect AbsBall::getBounds() const
{
	return m_ball.getGlobalBounds();
}

float AbsBall::Gravity() const
{
	return 0.5f;
}

void AbsBall::collide(Moveable & other)
{
	other.collide(*this);
}

void AbsBall::collide(Unmoveable & other)
{
	other.collide(*this);
}

void AbsBall::collide(Wall & wall)
{
	
	auto rect = wall.getBounds();
	
	if (!m_ball.getGlobalBounds().intersects(rect))return;

	auto pos = getCenter();

	if (m_direction.y >= 0 && pos.y-getRad() <= rect.top)
		hitFloor();
	else if (m_direction.y < 0 && pos.y+getRad() >= rect.top + rect.height)
		hitCeiling();
	else if(m_direction.x>=0 && pos.x<rect.left||
		m_direction.x<0 && pos.x>rect.left+rect.width)
		hitWall();
		
}

void AbsBall::collide(Door & d)
{
	auto bounds = d.getBounds();
	auto pos = getCenter();
	
	if (m_direction.x >= 0 && pos.x < bounds.left ||
		m_direction.x<0 && pos.x>bounds.left + bounds.width)
		hitWall();
}

void AbsBall::collide(Spikes & spike)
{
	if (spike.getBounds().intersects(m_ball.getGlobalBounds()))
	{
		split();
		Sound::instance()->reg(ResourceManager::Sound::Pop);
	}
		
		
	
}

void AbsBall::collide(Player & player)
{
	
	player.collide(*this);
	
}

void AbsBall::collide(AbstractWeapon & w)
{
	if(getRad()<=10.f)
	Sound::instance()->reg(ResourceManager::Sound::smallPop);
	else
	Sound::instance()->reg(ResourceManager::Sound::Pop);
	split();
}

void AbsBall::setTexture(ResourceManager::Texture img)
{
	m_ball.setOutlineThickness(0);
	m_ball.setFillColor(sf::Color::White);
	m_ball.setTexture(ResourceManager::instance()->getTexture(img));
	
	
}

void AbsBall::setAnimation(sf::IntRect rect)
{
	
	m_ball.setTextureRect(rect);
	
}

AbsBall::~AbsBall()
{
	
	GameToolBar::addScore(10);
	m_GlobalAbsBallCounter--;
	
}

void AbsBall::addingItem(std::string str , sf::Vector2f pos)
{
	
	std::stringstream ss;
	std::string temp;
	ss << str << pos.x << " " << pos.y;

	std::getline(ss, temp);  DrawableFactory::createDrawable(temp); 
}

void AbsBall::checkInBounds()
{
	auto rad = m_ball.getRadius();
	//ensure in window bounds
	if (m_nextPos.x - rad < 0) { // left window edge
		hitWall();
	}
	else if (m_nextPos.x + rad >= Window::WIND_X) { // right window edge
		hitWall();
	}
	else if (m_nextPos.y < rad) { // top of window
		hitCeiling();
		m_nextPos.y = rad;

	}
	else if (m_nextPos.y > Window::WIND_Y - rad) { // bottom of window
		hitFloor();

	}
	//----	
}

void AbsBall::rangeCheck(float& radius)
{
	radius = radius - (int)radius % 10;

	if (radius > 80)radius = 80;

	else if(radius < 10)radius = 10;

	m_ball.setRadius(radius);
		
}

void AbsBall::rangeCheck(sf::Vector2f & pos)
{
	float rad = m_ball.getRadius();
	if (pos.x < rad || pos.y < rad)
		pos = sf::Vector2f(rad, rad);
	else if( pos.x> Window::WIND_X-rad || pos.y > Window::WIND_Y-rad)
		pos = sf::Vector2f(float(Window::WIND_X-rad) , float(Window::WIND_Y-rad));
}
	
void AbsBall::hitWall()
{
		m_direction.x *= -1;
			
}

void AbsBall::setDir(sf::Vector2f direction)
{
	m_direction = direction;
}



void AbsBall::hitFloor()
{
	m_direction.y *= -1;
	m_direction.y = -(7 + std::sqrt(2*getRad()));
}

void AbsBall::generateItem(sf::Vector2f pos)
{
	if (AbstractItem::getTotalCount() > 8)return;

	int num = rand() % 15;

	switch (num)
	{
	case(0):addingItem("FrozenArrowItem ",pos); break;
	case(1):addingItem("SimpleArrowItem ", pos); break;
	case(2):addingItem("LaserItem ", pos); break;
	case(3):addingItem("SheildItem ", pos); break;
	case(4):addingItem("OneUpItem ",pos);break;
	case(5):addingItem("TimeItem ", pos); break;
	case(6):addingItem("CashItem ", pos); break;
	}
}

void AbsBall::hitCeiling()
{
	m_direction.y *= -1;
	//new_pos.y = m_ball.getPosition().y+getRad();
}




