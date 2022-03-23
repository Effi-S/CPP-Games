#include "ResourceManager.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <queue>

ResourceManager* ResourceManager::instance()
{
	static ResourceManager instance;
	return &instance;
}

std::deque<sf::IntRect> ResourceManager::getAnimationArray(int rows, int cols , Texture img)
{
	std::deque<sf::IntRect> q;

	auto size = getTexture(img)->getSize();
	auto rectSize = sf::Vector2i(size.x / cols, size.y / rows);


	for (int i = 0; i < rows ; ++i)
		for (int j = 0; j < cols ; ++j)		
			q.emplace_back(sf::IntRect( j*rectSize.x ,i*rectSize.y , rectSize.x,rectSize.y));

	return q;
}

sf::Texture* ResourceManager::getTexture(Texture name)
{
	if (m_textures[name])
		return m_textures[name];

	return nullptr;
}

sf::SoundBuffer* ResourceManager::getSound(Sound name)
{
	if (m_sounds.at(name))
		return m_sounds.at(name);

	return nullptr;
}

sf::Font* ResourceManager::getFont(Font name)
{
	if (m_fonts[name])
		return m_fonts[name];

	return nullptr;
}

ResourceManager::ResourceManager()
{
	//load textures
	loadTexture("resources/textures/player1.png", Texture::Player1);
	loadTexture("resources/textures/player2.png", Texture::Player2);
	loadTexture("resources/textures/shade_effect.png", Texture::ShadeEffect);
	

	loadTexture("resources/textures/ball.png", Texture::ball);
	loadTexture("resources/textures/wall.png", Texture::wall);
	loadTexture("resources/textures/spikes.png", Texture::spikes);
	loadTexture("resources/textures/bottom_bar.png", Texture::bottom_bar);
	loadTexture("resources/textures/BossBall.png", Texture::bossBall);
	loadTexture("resources/textures/BossBallFliped.png", Texture::bossBallFlip);
	loadTexture("resources/textures/sheild.png", Texture::Sheild);
	loadTexture("resources/textures/fire.png", Texture::Fire);
	
	loadTexture("resources/textures/Movingfire .png", Texture::MovingFire);

	//arrow textures:
	loadTexture("resources/textures/arrow.png", Texture::Arrow);
	loadTexture("resources/textures/projectile.png", Texture::LaserArrow);
	loadTexture("resources/textures/frozen_arrow.png", Texture::FrozenArrow);

	//item textures:
	loadTexture("resources/textures/frozen_arrow_item.png", Texture::FrozenItem);
	loadTexture("resources/textures/laser_weapon_item.png", Texture::LaserItem);
	loadTexture("resources/textures/reg_arrow_item.png", Texture::simpleItem);
	loadTexture("resources/textures/sheild_item.png", Texture::SheildItem);
	loadTexture("resources/textures/time_item.png", Texture::TimeItem);
	loadTexture("resources/textures/one_up_item.png", Texture::OneUpItem);
	loadTexture("resources/textures/cash_item.png", Texture::CashItem);

	//menu textures
	loadTexture("resources/textures/menu/menu.png", Texture::MainMenu_bg);
	loadTexture("resources/textures/menu/1player.png", Texture::Play_1p_bg);
	loadTexture("resources/textures/menu/2player.png", Texture::Play_2p_bg);
	loadTexture("resources/textures/menu/controls.png", Texture::Controls_bg);
	loadTexture("resources/textures/menu/1player_button.png", Texture::Play_1p_button);
	loadTexture("resources/textures/menu/2player_button.png", Texture::Play_2p_button);
	loadTexture("resources/textures/menu/controls_button.png", Texture::Controls_button);
	loadTexture("resources/textures/menu/quit_button.png", Texture::Quit_button);
	loadTexture("resources/textures/menu/help_p1_button.png", Texture::HelpP1_button);
	loadTexture("resources/textures/menu/help_p2_button.png", Texture::HelpP2_button);
	loadTexture("resources/textures/menu/back_button.png", Texture::Back_button);
	loadTexture("resources/textures/menu/help_p1.png", Texture::HelpP1_bg);
	loadTexture("resources/textures/menu/help_p2.png", Texture::HelpP2_bg);
	loadTexture("resources/textures/menu/youSure.png", Texture::youSure);
	//game events
	loadTexture("resources/textures/timesUp.png", Texture::OutOfTime);
	loadTexture("resources/textures/GameOver.png", Texture::OutOfLives);
	loadTexture("resources/textures/youWon.png", Texture::youWon);
	loadTexture("resources/textures/scoreBoard.png", Texture::ScoreBoard);
	
	//load sounds
	loadSound("resources/sounds/pop.wav", Sound::Pop);
	loadSound("resources/sounds/arrow.wav", Sound::Arrow);
	loadSound("resources/sounds/pop_small.wav", Sound::smallPop);
	loadSound("resources/sounds/items.wav", Sound::item);
	loadSound("resources/sounds/projectile.wav", Sound::Laser);
	loadSound("resources/sounds/death.wav", Sound::death);
	loadSound("resources/sounds/gong.wav", Sound::gong);
	loadSound("resources/sounds/frozen_arrow.wav", Sound::frozenArrow);
	loadSound("resources/sounds/menu_sounds/transfer.wav", Sound::transfer);
	loadSound("resources/sounds/menu_sounds/click.wav", Sound::Click);

	//load fonts
}

void ResourceManager::loadTexture(std::string path, Texture name)
{
	sf::Texture *temp = new sf::Texture();
	temp->setRepeated(true);
	temp->loadFromFile(path);
	m_textures[name] = temp;
}

void ResourceManager::loadSound(std::string path, Sound name)
{
	sf::SoundBuffer *temp = new sf::SoundBuffer();
	temp->loadFromFile(path);
	m_sounds[name] = temp;
}

void ResourceManager::loadFont(std::string path, Font name)
{
	
	sf::Font *temp = new sf::Font();
	temp->loadFromFile(path);
	m_fonts[name] = temp;
}

ResourceManager::~ResourceManager()
{
	
	for (auto& item : m_textures)
	{
		delete item.second;
		item.second = nullptr;
	}
	for (auto& item : m_sounds)
	{
		delete item.second;
		item.second = nullptr;
	}
	for (auto& item : m_fonts)
	{
		delete item.second;
		item.second = nullptr;
	}
}