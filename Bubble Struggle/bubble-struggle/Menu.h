//This is the Menu class 
//recieve background texture in the constructor,
//hold a vector of Commands that are added into the vector with the add method
//to allow the creation of different menus.
#pragma once
#include <memory>
#include <vector>
#include <utility>
#include "Command.h"
#include "Flame.h"

class Menu
{
public:
	Menu(sf::Texture* t) : m_bgTexture(t), m_defaultBgTexture(t) {}
	~Menu() = default;
	void add(std::string str, std::unique_ptr<Command> c) { m_options.emplace_back(option(str, std::move(c))); }
	void run();

private:
	using option = std::pair<std::string, std::unique_ptr<Command>>;
	std::vector<option> m_options;
	void show();
	void handleEvents();
	sf::Music m_music;
	sf::Sprite m_bg;
	sf::Texture* m_bgTexture;
	sf::Texture* m_defaultBgTexture;

	Flame m_flame1 = Flame(sf::Vector2f(-150.f, -20.f), sf::Vector2f(270.f, 220.f))
		, m_flame2 = Flame(sf::Vector2f(Window::WIND_X*0.8f, -15.f), sf::Vector2f(300.f, 220.f));
};