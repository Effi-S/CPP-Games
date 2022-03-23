#include "Command.h"
#include <memory>
#include "Menu.h"

void Controls::execute()
{
	bool flag = false;
	Menu menu(ResourceManager::instance()->getTexture(ResourceManager::Texture::HelpP1_bg));
	menu.add("back", std::make_unique<Back>(flag));
	menu.add("p1help", std::make_unique<p1Controls>());
	menu.add("p2help", std::make_unique<p2Controls>());
	Sound::instance()->reg(ResourceManager::Sound::transfer);
	while (!flag && Window::get().isOpen())
	{
		Window::get().clear();
		menu.run();
		Window::get().display();
	}
}

void Play::play(bool flag)
{
	Sound::instance()->reg(ResourceManager::Sound::transfer);
	Sound::instance()->stop_bg();
	m_controller.init(flag);
	m_controller.run();
}
