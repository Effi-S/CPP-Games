#include "PlayerOne.h"
#include "DrawableFactory.h"
#include "RegisterFunctionTemplates.h"
#include "Unmoveable.h"


void PlayerOne::collide(Unmoveable & other)
{
	other.collide(*this);
}

PlayerOne::PlayerOne()
	:Player(sf::Vector2f(100,0))
{
	setLivesPos(10);
}


PlayerOne::~PlayerOne()
{
}
