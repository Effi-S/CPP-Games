#include "Wall.h"
#include "ResourceManager.h"
#include "Ball.h"
#include "Moveable.h"
#include "DrawableFactory.h"
#include "RegisterFunctionTemplates.h"
#include "Moveable.h"
#include "Player.h"
#include "BossBall.h"

bool Wall::m_reg=DrawableFactory::registerMe("Wall", &addStationary<Wall>);

Wall::Wall(sf::Vector2f pos, sf::Vector2f size)
	:Unmoveable(pos,size)
{
	setTextureRect(pos,size);
}

void Wall::collide(Moveable & other)
{
	other.collide(*this);
}

void Wall::collide(Player & other)
{
	other.collide(*this);
}

void Wall::collide(BossBall & b)
{
	b.collide(*this);
}


