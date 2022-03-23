#include "Background.h"
#include "WindowCONST.h"


Background::Background()	
{	
	m_spr.setTextureRect(sf::IntRect(0,0,Window::WIND_X, Window::WIND_Y));
	std::string str = "resources/textures/level";
	std::string png = ".png";


	for (m_levels=1; ; m_levels++)
	{
		std::string num(std::to_string(m_levels));
		sf::Texture *temp=new sf::Texture;
			temp->setSmooth(true);
			if (temp->loadFromFile(str + num + png))
				m_LvlTextures.push_back(temp);
			else
				break;
		
		
	}

	firstLvl();	

	//shading effect
	m_shadeEffect.setTexture(*ResourceManager::instance()->getTexture(ResourceManager::Texture::ShadeEffect));
	
	auto size = m_shadeEffect.getLocalBounds();
	m_shadeEffect.setOrigin(sf::Vector2f(size.width/2, size.height / 2));
	
}

void Background::nextLvl()
{		
	m_spr.setTexture(*m_LvlTextures.at((++m_lvl)%m_levels));
}

void Background::setShade(sf::Vector2f pos)
{
	m_shadeEffect.setPosition(pos);
	m_isShading = true;
	m_shadingClock.restart();
}

void Background::Shade()
{
	if (!m_isShading)return;

	auto time = m_shadingClock.getElapsedTime().asSeconds();
	if (time < 2)
		Window::get().draw(m_shadeEffect);
	else
	{
	m_isShading = false;
	m_shadingClock.restart();
	}
		
}

void Background::firstLvl()
{
	m_spr.setTexture(*m_LvlTextures.at(0));
}



Background::~Background()
{
}
