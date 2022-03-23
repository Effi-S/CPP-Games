#include "Ball.h"
#include "Board.h"
#include "DrawableFactory.h"
#include "RegisterFunctionTemplates.h"


bool Ball::m_reg=DrawableFactory::registerMe("Ball", &addAbsball<Ball>);

Ball::Ball(float radius, sf::Vector2f pos, bool inverse)
	:AbsBall(radius, pos, inverse) 
{
	
}

void Ball::split()
{
	Board & board = Board::inst();
	auto rad = getRad();

	if (rad <= 10.f)
	{
	Board::inst().remove(this);
		return;
	};

	sf::Vector2f pos = getCenter();

	board.add(std::make_shared <Ball>(rad - 5, pos, true));
			
	board.add(std::make_shared <Ball>(rad - 5, pos));

	board.remove(this);
}





Ball::~Ball()
{
}
