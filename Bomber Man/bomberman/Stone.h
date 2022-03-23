//***********************************
//this is the stone class
//derrived from the placeable base class
//it can hold a present theat is only reveladed after 
//collision with bomb 
//collision with bomb also turns the stone 
//to an empty cell.
//**********************************
//============================
#pragma once
#include "Placeable.h"
#include "Bomb.h"
#include "Present.h"
//----------------------------

class Stone :
	public Placeable
{

public:
	
	Stone(sf::RenderWindow &window, sf::Vector2f Pos, sf::Texture * img , sf::Texture * presImg =( new sf::Texture) , bool Pres = false);
	virtual void collideWith(class Character & other) {};
	virtual void collideWith(class Robot& other);
	virtual void collideWith(class Bomb& other);
	virtual void collideWith(class Present& other) {};
	void revertOrigPos();
	void drawOnGrid() ;
	void shade();
	
	void unShade();
	


	~Stone();
private:
	void removeStone();
	bool m_hasPres = false;
	
	sf::Texture * m_PresImg;
	Present *m_Pres;
};

