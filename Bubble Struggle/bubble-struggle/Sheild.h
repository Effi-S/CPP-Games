//this is the sheild 
//derived form Moveable 
//this sheild follows a player 
//until its time is up then it is removed
//balls bounce off of this sheild 
#pragma once
#include "Moveable.h"
#include "Player.h"
#include "Door.h"
class Sheild :
	public Moveable
{
public:
	Sheild(Player & player);
	virtual void update(float delta) ;
	
	virtual void draw() ;
	virtual sf::FloatRect getBounds() const override { return m_circ.getGlobalBounds(); };

	virtual void collide(class Moveable & other) { other.collide(*this); };
	virtual void collide(class Unmoveable & other) {  };
	void collide(class AbsBall & ball);
	void collide(class Player & p) { } ;
	void collide(class Wall & wall) { };
	void collide(class Door & wall) { };
	void collide(class Spikes &) { };

	~Sheild();
private:

	sf::CircleShape m_circ; // the circle of the sheild drawn
	Player & m_player;// reference of player sheild surrounds
	sf::Clock m_Countdowntimer; // countdown for sheilds life.

};

