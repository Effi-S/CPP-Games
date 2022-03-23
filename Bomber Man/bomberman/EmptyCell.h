//*********************EmptyCell************
//this is the emptyCell class
//it randomly generates a background from the img it receives 
//and can hold a present 
//has no other functionality other than allowing character movement into 
//its space.
//******************************************

//------includes---------
#pragma once
#include "Placeable.h"
#include "Present.h"
//---------------------
class EmptyCell :
	public Placeable
{
public:
	EmptyCell(sf::RenderWindow & window, sf::Vector2f Pos, sf::Texture * img, sf::Texture * presImg = new sf::Texture , bool addPres =false);
	virtual void collideWith(class Character & other) {};
	virtual void collideWith(class Robot& other) ;
	virtual void collideWith(class Bomb& other) { };
	virtual void collideWith(class Present& other) {};
	virtual void drawOnGrid() ;

	void addPres(sf::Texture *img);

	void shade(); 
	void unShade();
	

private:
	void setBkg();
	Present *m_present;
	bool m_hasPres=false;

	~EmptyCell();
};

