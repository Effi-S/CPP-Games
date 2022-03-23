#include "UpDownBall.h"
#include "Board.h"
#include "DrawableFactory.h"
#include "RegisterFunctionTemplates.h"
#include "Ball.h"

bool UpDownBall::m_reg = DrawableFactory::registerMe("UpDownBall", &addAbsball<UpDownBall>);
UpDownBall::UpDownBall(float radius,  sf::Vector2f pos, bool inverse )
	:AbsBall(radius,  pos , inverse) 
{
	setDir(sf::Vector2f(0, 4));
	setColor(sf::Color(200, 200, 200, 250));
}

void UpDownBall::split()
{
	auto pos = getCenter();
	Board & board = Board::inst();
	if (getRad() <= 10.f) {
		board.remove(this);
	}
		
	else
	{
		auto rad = getRad();
		board.add(std::make_shared<Ball>(rad, pos));
		board.add(std::make_shared<Ball>(rad, pos, true));
		board.remove(this);
	}
}

float UpDownBall::Gravity() const
{
	return 0.5f;
}


UpDownBall::~UpDownBall()
{
}
