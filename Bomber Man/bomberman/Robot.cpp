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
#include "Robot.h"
#include "CONSTS.h"
#include "Bomb.h"
#include "Door.h"
#include "Present.h"
#include "Guard.h"
//-----------------------------------------

//===========robot constructor================
//receives a render window int window, image into img
//std::vector <Placeables *> int grid and std::vector <Character *> 
//into chars all for constructing the Character base class.
//aswell he has  bombImg texture for the bombs picture 
//receiiveing a pos is optional.
Robot::Robot(sf::RenderWindow & window,  sf::Texture * img ,
	sf::Texture * BombImg,
	std::vector<Placeable *> &grid,
	std::vector<Character *> &chars , int gridX ,int bombLimit ,sf::Vector2f pos  )

	:Character(window, pos, img , grid , gridX ), m_chars(chars) ,m_bombImg(BombImg) ,m_bombLimit(bombLimit)
{
	m_info.bombs = bombLimit;
	restartBombs();

	m_image->setSmooth(true);
	
	
	m_empty = false;
	m_longBomb = false;
}
//--------------------

//========
//for setting the robots place
//ot pos this function is only
//to be used only by the levelLoader
void Robot::setPos(sf::Vector2f pos)
{
	m_origPos = pos;
	m_rect.setPosition(pos);
}
//------------------

//shading all other grid apart from the robot and the other placeable 
//given in other.
void Robot::shadeEffect(Placeable & placeable)
{
	m_window.clear(sf::Color(76, 76, 76, 255));

	for (size_t i = 0; i < m_grid.size(); i++)
	{
		m_grid[i]->shade();
		m_grid[i]->drawOnGrid();
	}

	for (size_t i = 0; i < m_bombs.size(); i++)
		m_bombs[i]->shade();

	placeable.unShade();

	placeable.drawOnGrid();

	drawOnGrid();

	m_window.display();

		sf::Clock clock;
	while (clock.getElapsedTime().asSeconds() < 1);

	for (size_t i = 0; i < m_grid.size(); i++)
		m_grid[i]->unShade();
	
}

//=====losing game=======
void Robot::lostGame()
{
	m_info.bombs = 0;
	m_info.score = 0;
}
//----------------------

//===================================
//the robots move
//receives event to retreive the key pressed 
void Robot::move(sf::Event & event)
{
	for (size_t i = 1; i < m_chars.size(); ++i) //check collisions with other characters.
	{
		if (m_chars[0]->getGlobalBoundrie().intersects(m_chars[i]->getGlobalBoundrie()))
			m_chars[0]->collide(*m_chars[i]);
	}

	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case (sf::Keyboard::Down): moveDown();

			m_move = down_t; break;


		case (sf::Keyboard::Up): moveUp();

			m_move = up_t; break;

		case (sf::Keyboard::Left): moveLeft();

			m_move = left_t; break;

		case (sf::Keyboard::Right):
			moveRight();

			m_move = right_t; break;

		}

	}

	if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::B)
	{
		if (m_move != extra_t)
			plantBomb();

		m_move = extra_t;
	}

	setViewPoint();
}
//----------------------

//=======================
//drawing on the grid 
//robot and the bombs.
void Robot::drawOnGrid()
{
	for (size_t i = 0; i < m_bombs.size(); ++i)
	{
		if(m_bombs[i]->blown())
			m_bombs.erase(m_bombs.cbegin() + i);
		else
			m_bombs[i]->drawOnGrid();
	}

	m_bombs.shrink_to_fit();

	m_window.draw(m_rect);
}
//----------------

//reverting /dying
void Robot::revertOrigPos()
{
	die();		
}
//----------------------

//============COLISIONS====================
//door colision
void Robot::collideWith(Door &other)
{

	m_rect.setFillColor(sf::Color::Yellow);

	m_info.score += 20 * (m_chars.size() - 2);

	m_info.nextlvl = true;


}

//bomb collision
void Robot::collideWith(Bomb & other)
{
	shadeEffect(other);

	die();
}

//presant collision
void Robot::collideWith(Present & other)
{
	switch (other.getType())
	{
	case(oneUp_t):m_info.lives++; break;
	case(bombUp_t):m_longBomb = true; break;
	case(scoreUp_t):m_info.score += m_chars.size(); break;
	case(ammoUp_t):rechargeBombs();	break;
	case(noUp_t):break;

	}
}

//placeable
void Robot::collideWith(Placeable & other)
{
	m_info.nextlvl = false;

	other.collideWith(*this);
}
//robot collision
void Robot::collide(Character & other)
{
	other.collide(*this);
}

//guard collision
void Robot::collide(Guard & other)
{
	shadeEffect(other);

	die();
	
}
//========================


//==================
//robot dies ,reverts back to original position
//and reverts all the characters back.
void Robot::die()
{	
	Placeable::revertOrigPos();

	for (size_t i = 1; i < m_chars.size(); i++)
		m_chars[i]->revertOrigPos();

	restartBombs();

	m_info.lives--;

	setViewPoint();
}
//-------------------

//======================
//restarts the bombs 
//deletes all bombs in arsenal 
//and adds bomblimit  amount of bombs.
void Robot::restartBombs()
{	
	if (m_bombLimit == -1)return;

	m_bombs.empty();

	m_info.bombs = 0;

	rechargeBombs();
}
//------------------------

//returns the game info
//=======================
gameInfo Robot::getInfo()
{
	return m_info;
}
//============================

//here the robot plants a bomb
//when planting a bomb the robot 
//gives the cells the bomb can effect 
//============================
void Robot::plantBomb()
{	
	std::vector<Placeable*> adjace;
	if(!m_longBomb)
		 adjace = Adjacents();
	else
	 adjace = AdjacentsLong();

	slideChange(extra_t);

	if (m_bombLimit == -1)
	{
		Bomb * bombPtr = (new Bomb(m_window, m_bombImg, m_chars, m_info));
		m_bombs.push_back(bombPtr);

		m_bombs[m_bombs.size() - 1]->Plant(adjace);
	}
	else if (m_info.bombs < 1)
		return;
	else
	for (int i = 0; i < m_bombs.size(); ++i)	
		if(!m_bombs[i]->planted())
		{			
			m_bombs[i]->Plant(adjace);

			break;
		}			
}
//------------------------------

//============================================
//this funtion sets the viewpoint around the robot if 
//the robot is nearing the ends of the windows view
//i made it so when he passes the view on the right
//or from the top the view 
//is centerd from his position forward while 
//from the left or from the bbottom 
//the view is centered around his position
//this extra step is not neccessary but i think adds a nice effect.
void Robot::setViewPoint()
{
	sf::Vector2f viewCenter(m_window.getView().getCenter());

	sf::FloatRect currentViewRect(getCurrentViewRect());

	currentViewRect.height -= TOOLBAR_BUTTONSIZE.y +CELLSIZE.y;
	currentViewRect.width -= CELLSIZE.x;
	currentViewRect.top += TOOLBAR_BUTTONSIZE.y;

	sf::View view(m_window.getView());

	if (!currentViewRect.contains(sf::Vector2f(m_rect.getPosition().x, viewCenter.y))) //x out of bounds
	{
		/*if (m_rect.getPosition().x < viewCenter.x- currentViewRect.width/2.f)

			view.setCenter(sf::Vector2f(m_rect.getPosition().x , m_window.getView().getCenter().y));		
		else*/
		view.setCenter(sf::Vector2f(m_rect.getPosition().x , m_window.getView().getCenter().y));

	}
		
	if (!currentViewRect.contains(sf::Vector2f(viewCenter.x, m_rect.getPosition().y))) //y out of bounds
	{
		/*if (m_rect.getPosition().y < viewCenter.y - currentViewRect.height / 2.f + TOOLBAR_BUTTONSIZE.y + CELLSIZE.y)

			view.setCenter(sf::Vector2f(m_window.getView().getCenter().x, m_rect.getPosition().y));
		else*/
		view.setCenter(sf::Vector2f(m_window.getView().getCenter().x, m_rect.getPosition().y - TOOLBAR_BUTTONSIZE.y));
					
	}
		
	m_window.setView(view);
}
//----------------------------------------

//the robot adds bombLimit bombs to arsenal.
//===============================
void Robot::rechargeBombs()
{
	for (int i = 0; i < m_bombLimit; ++i)
	{
		m_bombs.push_back(new Bomb(m_window, m_bombImg, m_chars, m_info));
		m_info.bombs++;
	}
		
}
//-----------------

//==========================
Robot::~Robot()
{

}
//---------------------------
