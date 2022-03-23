#include "SimpleArrow.h"
#include "ResourceManager.h"
#include "WindowCONST.h"
#include "AbsBall.h"
#include "ResourceManager.h"
#include "Sound.h"


SimpleArrow::SimpleArrow(sf::Vector2f pos)
	:AbstractWeapon(sf::Vector2f(pos.x-0.5f , pos.y), ResourceManager::Texture::Arrow)
{
	Sound::instance()->reg(ResourceManager::Sound::Arrow);
}

