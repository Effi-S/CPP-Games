//this is the Zero gravity ball 
//derrived from AbsBall
//it ovverites the gravity inflicted on the ball to 0.
#pragma once
#include "AbsBall.h"
#include "Spikes.h"
class ZeroGravityBall :public AbsBall
{
public:
	ZeroGravityBall(float radius,  sf::Vector2f pos = sf::Vector2f(600.f, 400.), bool inverse = false);
	void split() override;
	void collide(class Spikes &) override{};
	virtual float Gravity() const { return 0.001f; };
	~ZeroGravityBall();
private :
	static bool m_reg;

};

