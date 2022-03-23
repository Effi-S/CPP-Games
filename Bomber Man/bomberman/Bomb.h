//**************Bomb class**************
//this is the Bomb class derrived from Placeable 
//it holds a rectangle and a reference to a window 
//so that it can print the rectangle to the screen
//it is dorment until planted then it waits 5 seconds and then explodes 
//itself and the cells it is given when planted
//***************************************
//=======includes================
#include "Placeable.h"

#pragma once

class Bomb
	:public Placeable
{
public:
	Bomb(sf::RenderWindow &window, sf::Texture * img , std::vector<Character *> &chars ,gameInfo &info );

	virtual void collideWith(class Character & other) { };
	virtual void collideWith(class Placeable & other) { };
	virtual void collideWith(class Robot& other) { };
	virtual void collideWith(class Bomb & other) { };
	virtual void collideWith(class Guard & other);
	virtual void collideWith(class Present& other) {};
	virtual void drawOnGrid();
	 
	void shade();

	bool planted() const;

	bool blown() const; 
	
	void Plant( std::vector<Placeable *> &Adjacents);
	
	void Blow(sf::Vector2f place);

	void MainBlow();

	~Bomb();
private:

	bool m_blown = false;
	bool m_planted = false;

	sf::Clock m_countdown;

	std::vector<Placeable *> m_adjacents;
	
	std::vector<class Character *> &m_chars;

	gameInfo &m_gameInfo;
	
};

