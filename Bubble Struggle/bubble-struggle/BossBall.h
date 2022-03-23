//this is the BossBall class
//a ball that hovers over the players shooting 
//Projectile Balls at them. 
#pragma once
#include "AbsBall.h"
#include "Player.h"
#include <queue>
class BossBall :
	public AbsBall
{
public:
	BossBall(sf::Vector2f pos = sf::Vector2f(45, 45) );
	
	void split() override;
	
	virtual sf::FloatRect getBounds() const override;
	void collide(class AbstractWeapon & weapon);
	void collide(class Wall &w) override;
	
	void collide(class Spikes &)override {};
	
	void update(float delta) override;

	virtual float Gravity() const { return 0; };
	
	~BossBall();

private:
	
	const  std::vector<std::unique_ptr<Player>> & m_players ;
	
	int m_lives=5; //the BossBall has 5 lives each time hit he loses one and at the end of his lives he dies
	 
	sf::Clock m_clock; // for timing the updates
	sf::Clock m_animationClock;// for the animation of the Ball

	std::deque < sf::IntRect> m_animationSet; // set of intRects for animation 
	
	sf::Clock m_loweringClock;// for if is getting closer to player or not
	
	bool m_isLowering =true; // boolian for ^^ 
	

	
	static bool m_reg;// for registration 

};

