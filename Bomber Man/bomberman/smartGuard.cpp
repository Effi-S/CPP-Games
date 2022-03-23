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
#include "smartGuard.h"
#include "Robot.h"
//===============================

// =====consts ===================
const int WHITE = 0, GRAY= 1, BLACK = 2;
const int SPEED_UP_TIME = 40 ,HANDICAP=1.5 ;
const int INF = 100000;
//================================

//===========constructor======================
//receives render window sf::vector2f texture and vector 
//for guard construction .
//aswell it receives a pointer to the robot 
//to update its position in realtime
smartGuard::smartGuard(sf::RenderWindow & window, sf::Vector2f pos, sf::Texture * img,
	std::vector< Placeable *> &grid,Robot *robot ,int gridX)
	:Guard(window,pos,img,grid ,gridX), m_robot(*robot) 
{	
	m_NextPos = m_rect.getPosition();
	m_savePos=m_rect.getPosition();
}
//---------------------------

//=================move=============
//this is the gards move 
//it uses bfs when it reaches the target cell in the grid 
//to find the next target cell.
void smartGuard::move()
{
	sf::FloatRect currentViewRect(getCurrentViewRect());

	if (m_moveTimer.getElapsedTime().asSeconds() < TURN_UNIT.asSeconds() * HANDICAP)
		return;

	if (!currentViewRect.contains(m_rect.getPosition()))
	{
		m_moveTimer.restart();
		revertOrigPos();
		return;
	}

	if (m_NextPos.x == m_rect.getPosition().x && m_NextPos.y == m_rect.getPosition().y)
	{
		makeBfs();
	}
		
	else
	{
		sf::Vector2f firstPos = m_rect.getPosition();

		moveMe(m_move);

		if (firstPos.x == m_rect.getPosition().x && firstPos.y == m_rect.getPosition().y)//for when completely blocked.
		{
			m_rect.setPosition(firstPos);

			m_NextPos = firstPos;

			m_move = (move_t)(rand() % MOVES);

			moveMe(m_move);
		}					
	}	
	m_moveTimer.restart();
}
//------------------------------------

//=============bfs function =============
//this is the bfs function.
//it places the objects on the grid that are in view into a linked list
//as well as an array for each node of distances and color 
//that can be white for if not visited yet 
//grey for if in transition 
//and black if visted already.
//the function creats a queue and places into the 
//queue each node it visits.
// starting from the robot , 
//each node visited gets the distance of the node 
//that it came from plus one.
//at the end of the algorithm each node gets 
//the distance from the robot.
//the next move is then decided bassed on the adjacent node
//with the smallest distance.
void smartGuard::makeBfs()
{

	//allocation 
	std::vector <int> dists; //distances

	std::vector <int> color; //coloring white for not visited grey for in the middle black for done

	std::vector <  std::vector <Placeable * > > list; //the list of Edges(adjacent cells in grid)

	std::vector <Placeable *> nodes; //the nodes(cells in the grid)
	
	sf::FloatRect currentViewRect(getCurrentViewRect());


	//initialization
	for (size_t i = 0; i < m_grid.size(); i++)
	{
		if (currentViewRect.contains(m_grid[i]->getPos()))
		{
			std::vector <Placeable * > adjace = getBFSAdjacents(i , currentViewRect);

			list.push_back(adjace);
			
			nodes.push_back(m_grid[i]);

			m_grid[i]->inputPlace(dists.size());

			dists.push_back(INF);

			color.push_back(WHITE);

		}
	}


	//finding start cell
	int startCell =0;

	for (size_t i = 0; i < nodes.size(); i++)
		if (nodes[i]->getGlobalBoundrie().intersects(m_robot.getGlobalBoundrie()))
			startCell = i;

	if (startCell > dists.size())return; //extra precaution.
	

	//placing startcell in queue.
	std::queue <Placeable *> Q;
		
	dists[startCell] = 0;

	color[startCell] = GRAY;
	
	Q.push(nodes[startCell]);
	
	//making the bfs list

	while (!Q.empty() > 0)
	{
		Placeable * U = Q.front();

		int uPos = U->getplace();

		if (uPos >= dists.size())continue;//extra precaution

		Q.pop();
	
		for (size_t v = 0; v < list[uPos].size(); ++v)
		{			
			int vPos = list[uPos][v]->getplace();

			if (vPos >= color.size())continue; // extra precaution

			if(color[vPos] == WHITE)
			{
				color[vPos] = GRAY;

				dists[vPos] = dists[uPos]+1;

				Q.push(list[uPos][v]);

			}
		}
		color[uPos] = BLACK;
	}
	//done making list

	//finding this guards place in the list
	int myPlace = 0;
	for (size_t i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->getGlobalBoundrie().intersects(m_rect.getGlobalBounds()))
		{
			myPlace = i;
			break;
		}
	}
	
	//finding next move
	int minDist = INF;
	int minI = 0;
	for (size_t i = 0; i < list[myPlace].size(); i++)
	{
		int p = list[myPlace][i]->getplace();
		if (dists[p] < minDist)
		{
			minI = p;
			minDist = dists[p];
		}		
	}

	m_NextPos = nodes[minI]->getPos();
	
	sf::Vector2f nextPos(nodes[minI]->getPos());
	sf::Vector2f myPos(getPos());

	
	
	//setting move
	
	
	if (nextPos.y > myPos.y)	
		m_move = down_t;
	else if (nextPos.y < myPos.y)
		m_move = up_t;	
	else if (nextPos.x > myPos.x)
		m_move = right_t;	
	else if (nextPos.x < myPos.x)
		m_move = left_t;	
	
	
	
		

	//clearing memory allocated.
	dists.empty();
	nodes.empty();
	color.empty();
	Q.empty();
	
}
//---------------------------------------

//=====same as base just with updating next pos======
void smartGuard::revertOrigPos()
{
	Guard::revertOrigPos();

	m_NextPos = m_rect.getPosition();
	m_savePos = m_rect.getPosition();
}
//-----------------------------

//====================================
smartGuard::~smartGuard()
{

}
//------------------------
