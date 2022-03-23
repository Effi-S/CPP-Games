//*********************smartGuard******************
//this is the smart guard class
// it is derrived from the base class guard 
//it uses bfs in order to find the shortest route to the robot
//that it receives a pointer to.

//it only uses bfs if  the folowing is true:
// 1) it in view
//2) it completed a full cell movement.
//*************************************************

//====include section==========
#pragma 
#include "CONSTS.h"
#include "Guard.h"
#include <queue>
#include <vector>
//-----------------------------

class smartGuard :
	public Guard
{
public:
	smartGuard(sf::RenderWindow & window, sf::Vector2f pos, sf::Texture * img,
		std::vector< Placeable *> &grid, class Robot *robot ,int gridX);
	void drawOnGrid() { m_window.draw(m_rect); };

	void move();

	void makeBfs();

	~smartGuard();

private:
	class Robot &m_robot;

	void revertOrigPos();
	
	sf::Vector2f m_NextPos;

	bool m_inView=false;

	sf::Vector2f m_savePos;

	
	
	
};

