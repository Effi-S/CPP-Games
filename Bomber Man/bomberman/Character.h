//**************Character class**************
//this is the character class  a purely virtual
//class derrived from the Placeable base class.
//a object of this class can move on the 
//grid of the game.
//for that the grid is referenced member of the object
//***************************************


//=======includes================
#pragma once
#include "Placeable.h" 
#include <vector>


class Character : public Placeable
{
public:
	Character(sf::RenderWindow &window, sf::Vector2f pos , sf::Texture * img, std::vector<Placeable *> &grid , int gridX , int slides=3 ,int slideRows =5);

	virtual void collideWith(Placeable & other) =0 ;
	virtual void collideWith(class Bomb & other) = 0;
	virtual	void move(sf::Event &event) = 0;

	virtual void collide(Character& other) = 0;
	virtual void collide(class Robot& other) = 0;
	virtual void collide(class Guard& other) = 0;

	int getGridPlace() const ;

	std::vector<Placeable *> Adjacents();
	std::vector<Placeable *> AdjacentsLong();

	std::vector<Placeable*>  Adjacents(int place) ;

	std::vector<Placeable *> getEmptyAdjacents() ;

	std::vector<Placeable *> getBFSAdjacents(int place , sf::FloatRect windowView)  ;

	void revertOrigPos();

	bool CellBlocked( unsigned cell)  const;

	sf::Vector2f getGridPos() const;

	~Character();
protected:

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	void addCell(int gridpos ,std::vector<Placeable *> &adjacents);

	void moveMe(move_t move);

	std::vector<Placeable *> & m_grid;
	
	void slideChange(move_t move);

	sf::FloatRect getCurrentViewRect() const;
	
	sf::Clock m_moveTimer;
	

	move_t m_move;

	int m_gridX;

private:


	sf::Clock m_slideTimer;

	int m_slide = 1;

	bool  decidePos(  sf::Vector2f &savePos);
	
	int SLIDES = 3;
	int SLIDEROWS = 5;
	
};

