#include "Spikes.h"
#include "ResourceManager.h"
#include "WindowCONST.h"
#include "DrawableFactory.h"
#include "RegisterFunctionTemplates.h"
#include "Moveable.h"
#include "Player.h"
bool Spikes::m_reg=DrawableFactory::registerMe("Spikes", &addSpikes);

Spikes::Spikes( float y)
	:Unmoveable(sf::Vector2f(0.f,y) , sf::Vector2f(Window::WIND_X*1.f , 19.f), ResourceManager::Texture::spikes)
{
	
}

void Spikes::collide(Moveable & other)
{
	other.collide(*this);
}

void Spikes::collide(Player & other)
{
	other.collide(*this);
}

