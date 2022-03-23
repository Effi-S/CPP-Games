#pragma once
//this is a class derrived from abstract ball
//the most basic type of ball
//it receives a radius for the size and an optional position 
//and creates a ball of that size.
#include "AbsBall.h"
#include <memory>
#include <string>
class Ball:public AbsBall
{
public:
	Ball(float radius, sf::Vector2f pos = sf::Vector2f(600.f, 400.f), bool inverse = false);
	void split() override;
	virtual float Gravity() const override { return 0.5; };
	~Ball();

private:
	static bool m_reg; //registering onto the drawable factory.
	
};

