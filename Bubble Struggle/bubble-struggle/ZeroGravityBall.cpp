#include "ZeroGravityBall.h"
#include "Board.h"
#include "RegisterFunctionTemplates.h"
#include "DrawableFactory.h"


bool ZeroGravityBall::m_reg= DrawableFactory::registerMe("ZeroGravityBall", &addAbsball<ZeroGravityBall>);
ZeroGravityBall::~ZeroGravityBall()
{
}

ZeroGravityBall::ZeroGravityBall(float radius,  sf::Vector2f pos, bool inverse)
:AbsBall(radius, pos, inverse)
{
	setColor(sf::Color(170,17,100 , 170 ));

	
	
}


void ZeroGravityBall::split()
{
	auto rad = getRad();
	Board & board = Board::inst();
	if (rad <= 10.f)
	{
		board.remove(this);
		return;
	};

	sf::Vector2f pos = getCenter();

	board.add(std::make_shared<ZeroGravityBall>(rad - 5,  pos, true));

	board.add(std::make_shared<ZeroGravityBall>(rad - 5,  pos));

	board.remove(this);

}


