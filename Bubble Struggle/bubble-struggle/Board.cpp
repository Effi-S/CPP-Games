#include "Board.h"
#include "Drawable.h"
#include "LivesBar.h"
#include "Spikes.h"
#include "Background.h"
#include "LivesBar.h"
#include "Ball.h"
#include "Sound.h"
#include "GameToolBar.h"

Board::Board()
	
{
	//set board view
	sf::Vector2u size = Window::get().getSize();
	m_boardView.reset(sf::FloatRect(0.f, 0.f, (float)size.x, (float)size.y));
	m_boardView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 0.80f));

	//shading effect
	
}

void Board::update(float delta)
{
	collisionHandle();

	for (size_t i=0 ;  i < m_moving.size() ; ++i)
			m_moving.at(i)->update(delta);

	for (auto& player : m_players)
			player->update(delta);

}

void Board::draw()
{
	
	auto &wind = Window::get();
	//draw game  
	wind.setView(m_boardView);
	m_bkg.draw();
	

	for (const auto& stationary : m_stationary)
		if(stationary.get())
			stationary->draw();

	for (const auto& moving : m_moving)
			moving->draw();

	size_t i = 0;
	for (const auto& player : m_players )
	{
		if (i < m_players.size())
		player->draw();	
			i++;
	}
			

	wind.getDefaultView();

	
	m_bkg.Shade();
}



void Board::collisionHandle()
{
	for (size_t i=0;i<m_players.size() ; i++)
		for ( size_t j=0; j< m_stationary.size() ; ++j)
			if (m_players.at(i).get() && m_stationary.at(j) &&
			m_players.at( i)->getBounds().intersects(m_stationary.at(j)->getBounds()))
				m_stationary.at(j)->collide(*m_players.at(i).get());

		for (size_t j = 0; j < m_stationary.size(); ++j)
			for (size_t i = 0; i < m_moving.size(); ++i )
			if (m_moving.at(i).get() && m_stationary.at(j).get()
				&& m_moving.at(i)->getBounds().intersects(m_stationary.at(j)->getBounds()))
				m_stationary.at(j)->collide(*m_moving.at(i).get());

	
		for (size_t k = 0; k < m_players.size(); k++)
			for (size_t i = 0; i < m_moving.size(); i++)
			if (m_moving.at(i).get() && m_players.at(k).get() &&
				m_moving.at(i)->getBounds().intersects(m_players.at(k)->getBounds()))
				m_players.at(k)->collide(*m_moving.at(i).get());

		for (size_t j = 0; j < m_moving.size(); j++)
			for (size_t i = 0; i < m_moving.size(); ++i)
				if (j < m_moving.size() && m_moving.at(i).get() && m_moving.at(j).get()
					&& m_moving.at(i)->getBounds().intersects(m_moving.at(j)->getBounds()))
					m_moving.at(j)->collide(*m_moving.at(i));
}


void Board::remove(Moveable * obj)
{	
	for (size_t i = 0; i < m_moving.size(); i++)
		if (m_moving.at(i).get() == obj)
		m_moving.erase(m_moving.cbegin() +i);
				
}

void Board::remove(Player * obj)
{
	for (size_t i = 0; i < m_players.size(); i++)
		if (m_players.at(i).get() == obj)
		{ 
			m_players.at(i).reset();
			m_players.erase(m_players.cbegin() + i);
		}
}

void Board::remove(Unmoveable * obj)
{
	for (size_t i = 0; i < m_stationary.size(); i++)
		if (m_stationary.at(i).get() == obj)
			m_stationary.erase(m_stationary.cbegin() + i);
}
void Board::add(std::shared_ptr<Moveable> obj)
{
	m_moving.push_back(std::shared_ptr<Moveable>(obj));
}

	
void Board::add(std::shared_ptr<Unmoveable> obj)
{
	m_stationary.push_back(std::shared_ptr<Unmoveable>(obj));
}

void Board::addPlayer(std::unique_ptr<Player> p)
{

	m_players.push_back(std::move(p));
}

void Board::addLifeBar(GameToolBar & bar)
{
	for (auto& player : m_players)
		player->addLifetoBar(bar);
}

void Board::Handle(sf::Event & event)
{
	for (auto& player : m_players)
		player->setMoveDir(event);

	 

	//------------for debug------------------------------
	if (m_moving.size() > 0)
		if (event.type == sf::Event::KeyReleased)
	if (event.key.code == sf::Keyboard::BackSpace)
	{
		
		
		
			AbsBall * ball;
			AbsBall * mb = dynamic_cast<AbsBall *>(m_moving.at(0).get());
			float max = 0;
			for (auto i : m_moving)
			{
				ball = dynamic_cast<AbsBall *>(i.get());
				if (ball)
					if (ball->getRad() >= max)
					{
						mb = ball;
						max = ball->getRad();
					}
			}
			if (mb)
				mb->split();
		

	}
	else if (event.key.code == sf::Keyboard::Delete)
	{
	
		AbsBall * ball = ball = dynamic_cast<AbsBall *>( m_moving.at(m_moving.size() - 1).get());
		if (ball)
			ball->split();
	}
		
	//---------------end debug-----------------
}

void Board::LoseLife()
{
	for (auto &i : m_players)
		i->LoseLife();
}

void Board::clearPlayers()
{
	m_players.clear();
}


void Board::shadeHere(sf::Vector2f pos)
{
	Sound::instance()->stopArrow();
	Sound::instance()->reg(ResourceManager::Sound::death);
	m_bkg.setShade(pos);
}

void Board::restart()
{	
	m_moving.clear();
	m_stationary.clear();

	for (auto &x : m_players)
		x->resetPos();
	
}

void Board::nextLvl()
{		
	Sound::instance()->reg(ResourceManager::Sound::gong);
	restart();	
	m_bkg.nextLvl();
}


