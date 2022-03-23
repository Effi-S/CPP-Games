//This is the abstract base class 
//derived from Moveable (so can add to board)
//for all of the different types of items.
#pragma once
#include "Moveable.h"
#include "ResourceManager.h"

class AbstractItem : public Moveable
{
public:
	AbstractItem(sf::Vector2f pos,  ResourceManager::Texture img) ;
	~AbstractItem() {m_TotalitemCounter--;};
	virtual void draw() ;
	virtual void update(float delta);
	virtual sf::FloatRect getBounds() const override{ return m_rectangle.getGlobalBounds(); };
	virtual void collide(class Moveable & other) {};
	
	static unsigned getTotalCount() { return m_TotalitemCounter; };
	virtual void collide(class Unmoveable & other) {};
	virtual void collide(class Player & p) = 0;
	virtual void removeMe();
private:
	sf::Clock m_groundTimer; // for countdown untill the item is removed after hitting 
	sf::Time m_groundTime=sf::seconds(0); // accumilating time for^^
	sf::RectangleShape m_rectangle;//the items rectangle itself
	float m_speedLowering=3; // the speed for lowering the item
	static unsigned m_TotalitemCounter; // counting how many items in the game 
										//- for managing the number 
										//of items in the game at any given time.
};

