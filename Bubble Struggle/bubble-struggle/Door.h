//This is the door class 
//it creates a wall from the top of the 
//screen almost until the end their it creates 
//a small unmoveable object that fades up
//allowing the player to pass through only when 
//a ball that it is connected to is destroyed.
//it acheives this in two different ways 
//for a ball that does not need to create more balls 
//is simply creates a shared ptr of the ball type
//and once the shared ptr has 
//been released it can fade up
//if the ball needs to create other balls 
//the door needs to wait for all the balls that 
//it creates to be destroyed 
//it accheives this by creating a template Wrapper of the 
//ball "HeldBall" and gives it a shared ptr they both hold 
//the HeldBall when creating another ball instead creaates a heldBall 
//of that type with the same shared ptr
//only once the shared ptr is released from all of the balls 
//will the door fade up.
#pragma once
#include "Unmoveable.h"
#include "Board.h"
#include "HeldBall.h"
#include "BossBall.h"
#include "DirectHitBall.h"
class Door :public Unmoveable
{
public:
	Door(sf::Vector2f pos , sf::Vector2f sizes);	
	

	template <class T>
	void makeBall();

	template <class T>
	void makeFollowBall();

	virtual void collide( Moveable & other) ;
	virtual void collide( Player & other) ;
	 void collide(class Sheild & other) {  };
	 void collide( AbsBall & other) ;
	 void draw() override;
	~Door()=default;
private:
	std::shared_ptr<int> m_checker; // for adding to HeldBall
	std::shared_ptr<AbsBall> m_ball =nullptr; // for holding a ball 
	sf::Vector2f m_ballInfo; // information of the ball to create.

	//for registrating different types of doors:
	static bool m_reg1;
	static bool m_reg2;
	static bool m_reg3;
	static bool m_reg4;
	

};

//template functions for adding ball to the door:

//for ball HeldBall
template<class T>
inline void Door::makeBall()
{
	Board::inst().add(std::make_shared<HeldBall<T>>(m_ballInfo.x , sf::Vector2f(m_ballInfo.y, 400.f), false, m_checker));
}

//for ball that needs to be followed itself only.
template<class T>
inline void Door::makeFollowBall()
{
	m_ball = std::make_shared<T>(sf::Vector2f(m_ballInfo.y, 400.f));
	Board::inst().add(m_ball);
	
}
