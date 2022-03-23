#include "PlayerTwo.h"
#include "DrawableFactory.h"
#include "RegisterFunctionTemplates.h"
#include "Moveable.h"
#include "Unmoveable.h"


PlayerTwo::PlayerTwo()
	:Player(sf::Vector2f(Window::WIND_X*0.7f , Window::WIND_Y) , ResourceManager::Texture::Player2)
{
	setKeys({ sf::Keyboard::Key::A ,sf::Keyboard::Key::D ,
			sf::Keyboard::Key::W });
	setLivesPos(Window::WIND_X*0.7f);
	
}

void PlayerTwo::collide(Moveable & other)
{
	other.collide(*this);
}

void PlayerTwo::collide(Unmoveable & other)
{
	other.collide(*this);
}


PlayerTwo::~PlayerTwo()
{
}
