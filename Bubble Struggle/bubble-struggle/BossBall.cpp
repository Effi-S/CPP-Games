#include "BossBall.h"
#include "Board.h"
#include "ProjectileBall.h"
#include "ResourceManager.h"
#include "DrawableFactory.h"
#include "RegisterFunctionTemplates.h"

bool BossBall::m_reg = DrawableFactory::registerMe("BossBall", &addFollowingBall<BossBall>);
BossBall::BossBall(sf::Vector2f pos )
	:AbsBall(80.f,sf::Vector2f( pos.x+80 , 95)), m_players(Board::inst().getPlayers())
{
	setDir(sf::Vector2f(2.f, 0.f));
	setTexture(ResourceManager::Texture::bossBall);
	m_animationSet = ResourceManager::instance()
		->getAnimationArray(3,5,ResourceManager::Texture::bossBall );
	

}


void BossBall::split()
{
	if (m_lives == 0)
		Board::inst().remove(this);

	
	m_lives--;
}

sf::FloatRect BossBall::getBounds() const
{
	return AbsBall::getBounds();
}

void BossBall::collide(AbstractWeapon & weapon)
{
	m_isLowering = true;
	m_loweringClock.restart();
	setDir(sf::Vector2f(0.f , 3.f));
	AbsBall::collide(weapon);
}

void BossBall::collide(Wall & w)
{
	auto bounds = w.getBounds();
	if (bounds.left+bounds.width <= getCenter().x+getRad())
	{
			setTexture(ResourceManager::Texture::bossBall);
	}
	else if (bounds.left > getCenter().x-getRad())
	{
		setTexture(ResourceManager::Texture::bossBallFlip);
	}
				
	AbsBall::collide(w);
}

void BossBall::update(float delta)
{
	if (m_isLowering && m_loweringClock.getElapsedTime().asSeconds() > 1)
	{
		setDir(sf::Vector2f(4.f, 0.f));
		setTexture(ResourceManager::Texture::bossBall);
		m_isLowering = false;
	}
	Board & board= Board::inst();
	
	
	if (m_animationClock.getElapsedTime().asSeconds() > 0.1)
	{
		sf::IntRect x;
		x = m_animationSet.front();
		m_animationSet.pop_front();
		m_animationSet.push_back(x);
		setAnimation(x);

		m_animationClock.restart();

	}
		
	 if (m_clock.getElapsedTime().asSeconds() >2.5)
	{		 
		 for (size_t i = 0; i < m_players.size(); ++i)
		 {
			const auto& vec = m_players;
			auto pos=vec.at(i)->getPos();
			board.add(std::make_shared<ProjectileBall>(getCenter(), pos));

		 }
			
		m_clock.restart();
	}
	AbsBall::update(delta);

}

BossBall::~BossBall()
{
}
