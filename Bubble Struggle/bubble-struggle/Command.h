//This is the Command Base class and all it's derived classes
//for all of the different menu commands.
//the menu add commands according to it's needs.
//the base class holds a button and recieve the button position,
//texture and size in the constructor (most commands are hard 
//coded by default values but its possible to send them as args)
#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "Button.h"
#include "Controller.h"
#include "Sound.h"

class Command
{
public:
	Command(sf::Vector2f pos, sf::Texture* t, sf::Vector2f size = sf::Vector2f(316, 73)) 
	{ m_button = std::make_unique<Button>(pos, t, size); }
	virtual void execute() = 0;
	virtual void draw() { m_button->draw(); }
	//this funcs is for changing the background while mouse is over a button
	virtual sf::Texture* getBgTexture() const { return nullptr; }
	virtual bool isMouseOverButton(sf::Vector2f mousePos) const { return m_button->isMouseOverButton(mousePos); }
	virtual void setIsOver(bool flag) { m_button->setIsOver(flag); }

private:
	std::unique_ptr<Button> m_button;
};

class Controls : public Command
{
public:
	Controls(sf::Vector2f pos = sf::Vector2f(184, 424), 
			 sf::Texture* t = ResourceManager::instance()->getTexture(ResourceManager::Texture::Controls_button),
			 sf::Vector2f size = sf::Vector2f(316, 73))
		: Command(pos, t, size) {}
	virtual void execute() override;
	virtual sf::Texture* getBgTexture() const {
		return ResourceManager::instance()->getTexture(ResourceManager::Texture::Controls_bg);
	}
};

class Back : public Command
{
public:
	Back(bool& flag, sf::Vector2f pos = sf::Vector2f(185, 575)) : Command(pos,
		ResourceManager::instance()->getTexture(ResourceManager::Texture::Back_button), sf::Vector2f(260, 40)), m_flag(flag) {}
	virtual void execute() override { Sound::instance()->reg(ResourceManager::Sound::transfer); m_flag = true; };
private:
	bool& m_flag;
};

class p2Controls : public Controls
{
public:
	p2Controls() : Controls(sf::Vector2f(185, 270),
		ResourceManager::instance()->getTexture(ResourceManager::Texture::HelpP2_button)) {}
	virtual void execute() override {};
	virtual sf::Texture* getBgTexture() const {
		return ResourceManager::instance()->getTexture(ResourceManager::Texture::HelpP2_bg);
	}
};

class p1Controls : public Controls
{
public:
	p1Controls() : Controls(sf::Vector2f(185, 180),
		ResourceManager::instance()->getTexture(ResourceManager::Texture::HelpP1_button)) {}
	virtual void execute() override {};
	virtual sf::Texture* getBgTexture() const {
		return ResourceManager::instance()->getTexture(ResourceManager::Texture::HelpP1_bg);
	}
};

class Quit : public Command
{
public:
	Quit() : Command(sf::Vector2f(184, 504),
		ResourceManager::instance()->getTexture(ResourceManager::Texture::Quit_button)) {}
	virtual void execute() override { Window::get().close(); };
};

class Play : public Command
{
public:
	Play(sf::Vector2f pos, sf::Texture* t, Controller& c) :Command(pos, t), m_controller(c) {}

protected:
	Controller& m_controller;
	void play(bool flag = false);
};

class Single : public Play
{
public:
	Single(Controller& c)
		: Play(sf::Vector2f(184, 264),
			ResourceManager::instance()->getTexture(ResourceManager::Texture::Play_1p_button), c) {}
	virtual void execute() override { play(); }
	virtual sf::Texture* getBgTexture() const {
		return ResourceManager::instance()->getTexture(ResourceManager::Texture::Play_1p_bg);
	}
};

class Coop : public Play
{
public:
	Coop(Controller& c)
		: Play(sf::Vector2f(184, 344),
			ResourceManager::instance()->getTexture(ResourceManager::Texture::Play_2p_button), c) {}
	virtual void execute() override { play(true); }
	virtual sf::Texture* getBgTexture() const {
		return ResourceManager::instance()->getTexture(ResourceManager::Texture::Play_2p_bg);
	}
};

