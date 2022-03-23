//this is the Resource Manager class
//a singelton class to insure one time load
//of all the game resources: textures, sounds, fonts.
//and allow for easy access to them by holding each resource
//type in an unordered map: key- resource ename
//						    value- pointer to the loaded resource
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <queue>

class ResourceManager
{
public:
	enum class Texture {
		Player1,
		Player2,
		ShadeEffect,
		//arrows:
		Arrow,
		LaserArrow,
		FrozenArrow,
		Sheild,

		//board objects:
		ball,
		wall,		
		spikes,
		bossBall,
		bossBallFlip,
		Fire,
		MovingFire,

		//items:
		simpleItem,
		FrozenItem,
		LaserItem,
		SheildItem,
		TimeItem,
		OneUpItem,
		CashItem,

		//toolbars/menus:
		bottom_bar,
		MainMenu_bg,
		Play_1p_bg,
		Play_2p_bg,
		Controls_bg,
		HelpP1_bg,
		HelpP2_bg,
		Play_1p_button,
		Play_2p_button,
		Controls_button,
		Quit_button,
		HelpP1_button,
		HelpP2_button,
		Back_button,
		youSure,

		//game events
		OutOfTime,
		OutOfLives,
		youWon,
		ScoreBoard

	};
		
	enum class Sound {
		Pop,
		Arrow,
		Laser,
		frozenArrow,
		smallPop,
		item,
		death,
		gong,
		//menu sounds
		transfer,
		flame,
		Click
	};
	enum class Font {
		Font1
	};

	~ResourceManager();
	
	static ResourceManager* instance();
	std::deque<sf::IntRect> getAnimationArray(int, int, Texture);
	sf::Texture* getTexture(Texture name);
	sf::SoundBuffer* getSound(Sound name);
	sf::Font* getFont(Font name);

private:
	ResourceManager();
	std::unordered_map<Texture, sf::Texture*> m_textures;
	std::unordered_map<Sound, sf::SoundBuffer*> m_sounds;
	std::unordered_map<Font, sf::Font*> m_fonts;
	void loadTexture(std::string path, Texture name);
	void loadSound(std::string path, Sound name);
	void loadFont(std::string path, Font name);
	
};

