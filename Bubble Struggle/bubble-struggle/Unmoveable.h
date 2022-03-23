#pragma once
//this is the unmoveable abstract Base class
//for creating a unmoveable object to be added to the board.
#include "Drawable.h"
#include "ResourceManager.h"

class Unmoveable : public Drawable
{
public:
	Unmoveable(sf::Vector2f pos, sf::Vector2f size ,ResourceManager::Texture img=ResourceManager::Texture::wall) ;
	virtual void draw();
	void setTextur(sf::Texture * img) ;
	void setTextureRect( sf::Vector2f size , sf::Vector2f  pos);
	
	void fadeUp();

	sf::FloatRect getBounds() { return m_rect.getGlobalBounds(); };
	virtual void collide(class Moveable & other) =0;
	virtual void collide(class Unmoveable & other) { };
	virtual void collide(class AbsBall & other) { }
	virtual void collide(class Player & other) { };
	virtual void collide(class AbstractWeapon & other) { };
private:
	sf::RectangleShape m_rect; // the rectangle of the unmoveable object.
};

