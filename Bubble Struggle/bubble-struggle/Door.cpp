#include "Door.h"
#include "DrawableFactory.h"
#include "RegisterFunctionTemplates.h"
#include "Ball.h"
#include "ZeroGravityBall.h"
#include "UpDownBall.h"
#include "HeldBall.h"


bool Door::m_reg2 = DrawableFactory::registerMe("ZeroDoor", &makeDoor<ZeroGravityBall>);
bool Door::m_reg1 = DrawableFactory::registerMe("Door", &makeDoor<Ball>);
bool Door::m_reg3 = DrawableFactory::registerMe("BossDoor", &makeFollowDoor<BossBall>);
bool Door::m_reg4 = DrawableFactory::registerMe("DirectDoor", &makeFollowDoor<DirectHitBall>);

Door::Door(sf::Vector2f positions, sf::Vector2f sizes)
	:Unmoveable(sf::Vector2f(positions.x, Window::WIND_Y*0.8), sf::Vector2f(sizes.x - 1, Window::WIND_Y*0.2), ResourceManager::Texture::wall)
{
	Board::inst().add(std::make_shared< Wall>(sf::Vector2f(positions.x, 1.f), sf::Vector2f(sizes.x, Window::WIND_Y*0.8)));
	
	setTextureRect(sf::Vector2f(positions.x - 1, Window::WIND_Y*0.8), sf::Vector2f(sizes.x + 2, Window::WIND_Y*0.2));
	
	m_checker = std::make_shared<int>();

	m_ballInfo = sf::Vector2f(sizes.y, positions.y);


}

void Door::collide(Moveable & other)
{
	other.collide(*this);
}

void Door::collide(Player & other)
{
	other.collide(*this);
}

void Door::collide(AbsBall & other)
{
	other.collide(*this);
}

void Door::draw()
{
	Unmoveable::draw();


	if (m_ball == nullptr)
	{
		if (m_checker.use_count() == 1)
			fadeUp();
	}
	else if (m_ball.use_count() == 1)
		fadeUp();


}
