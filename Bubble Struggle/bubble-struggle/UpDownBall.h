#pragma once
//this is a ball that only 
//moves up and down until hit and then splits into two 
//balls of "Ball" class.
#include "AbsBall.h"
class UpDownBall :
	public AbsBall
{
public:
	UpDownBall(float radius,  sf::Vector2f pos = sf::Vector2f(600.f, 400.), bool inverse = false);
	void split() override; 
	float Gravity() const  override;
	~UpDownBall();
private:
	static bool m_reg;
};

