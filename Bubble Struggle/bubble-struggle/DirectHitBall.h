//this is a direct only hit ball
//derrived from abstractBall 
//this class is a ball that can only be removed if hit directly.
#pragma once
#include "AbsBall.h"
#include "WindowCONST.h"
class DirectHitBall :
	public AbsBall
{
public:
	DirectHitBall( sf::Vector2f pos=sf::Vector2f(600.f, Window::WIND_Y-20.f));

	float  Gravity() const override { return 0.3f; };
	void update(float delta) override;
	
	void split() override; 
	~DirectHitBall();
private:
	static bool m_reg;// registration
	const std::vector <std::unique_ptr<Player>> &m_players;// holds vector fo players 
														// for getting their updated 
															//postitions in the game.
};

