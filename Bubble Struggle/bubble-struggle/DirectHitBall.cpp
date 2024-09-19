#include "DirectHitBall.h"
#include <memory>
#include <cmath>
#include "Board.h"
#include "DrawableFactory.h"
#include "RegisterFunctionTemplates.h"

bool DirectHitBall::m_reg= DrawableFactory::registerMe("DirectHitBall", &addFollowingBall<DirectHitBall>);

DirectHitBall::DirectHitBall( sf::Vector2f pos)
	:AbsBall(10.f, pos) , m_players(Board::inst().getPlayers())
{
	setColor(sf::Color(125, 125, 0, 255));
}

void DirectHitBall::update(float delta)
{
AbsBall::update(delta);

	for (const auto &player : m_players)
	{
		auto wrect = player->getWeaponBounds();
			
		if (wrect.intersects(getBounds())) {
			if (std::fabs(wrect.top - getCenter().y) > 5)
			{
				hitWall();
				AbsBall::update(delta);
				return;
			}
			
		}
	}
	
						
}

void DirectHitBall::split()
{
	Board::inst().remove(this);
}

DirectHitBall::~DirectHitBall()
{
}
