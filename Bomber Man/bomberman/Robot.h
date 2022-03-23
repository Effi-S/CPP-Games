//Robot
//******************************************
//this is the main character of the game 
//he is derrived from the base class character 
//and holds a vector of Bomb
//he moves based on the user pressing on the keyboard.
//the robot centers the view around him when neccessary 
//and reverts all the characters back to their original positions 
//when he gets hit by bomb or guard.
//*****************************************

//==============include section=============
#pragma once
#include "Character.h"
#include "CONSTS.h"
//---------------------------------------

class Robot :
	public Character
{
public:
	Robot(sf::RenderWindow & window, sf::Texture * img ,
		sf::Texture * BombImg ,
		std::vector<Placeable *> &grid, 
		std::vector<Character *> &chars ,	
	int gridX, int bombLimit = 10 , sf::Vector2f pos=sf::Vector2f(0.f,0.f) ) ;

	void setPos(sf::Vector2f pos);
	
	
	void lostGame();
	
	virtual	void move(sf::Event &event);
	
	virtual void drawOnGrid(); 

	void revertOrigPos();

	virtual void collideWith(class Character & other) { };
	
	virtual void collideWith(class Robot& other) { };
	virtual void collideWith(Placeable & other);
			void collideWith(class Door & other);
	virtual void collideWith(class Bomb& other) ;
	virtual void collideWith(class Present& other);

	virtual void collide(class Guard & other);
	virtual void collide(Robot &other) { };
	virtual void collide(Character &other);

	void setViewPoint();
	virtual void die();

	 gameInfo getInfo();

	~Robot();

private:

	void restartBombs();

	void rechargeBombs();

    gameInfo m_info;

	std::vector<Character *> &m_chars;
	
	void plantBomb();
	
	std::vector <class Bomb *> m_bombs;
	std::vector <class Blaster *> m_blaster;

	sf::Texture *m_bombImg;
	int m_bombLimit=10;
	
	void shadeEffect(Placeable & character);

	bool m_longBomb = false;
};

