#pragma once
//this is an unmoveable wall.
#include "Unmoveable.h"

class Wall :public Unmoveable
{
public:
	Wall(sf::Vector2f pos , sf::Vector2f size ) ;
	~Wall()=default ;

	virtual void collide(class Moveable & other) ;
	virtual void collide(class Player & other);
	void collide(class BossBall &b) ;

private:
	static bool m_reg;//registration 

};

