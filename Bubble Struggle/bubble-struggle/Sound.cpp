#include "Sound.h"
#include "ResourceManager.h"
#include "WindowCONST.h"

Sound* Sound::instance()
{
	static Sound instance;
	return &instance;
}

void Sound::reg(ResourceManager::Sound sound)
{
	if (!Window::get().isOpen())
		return;

#ifndef MAKELINUX
	if (sound == ResourceManager::Sound::Pop || sound == ResourceManager::Sound::smallPop)
		stopArrow();

	m_sounds.emplace_back(sf::Sound(*ResourceManager::instance()->getSound(sound)));
	m_sounds.back().play();
#endif
}

void Sound::stopArrow()
{
#ifndef MAKELINUX
	for (auto& sound : m_sounds)
		if (sound.getBuffer() == ResourceManager::instance()->getSound(ResourceManager::Sound::Arrow))
			sound.stop();
#endif
}

void Sound::clear()
{
	while (!m_sounds.empty() && m_sounds.front().getStatus() == sf::Sound::Stopped)
		m_sounds.pop_front();
}

Sound::Sound()
{
#ifndef MAKELINUX
	m_bgMusic.openFromFile("resources/sounds/menu_sounds/flame.wav");
	m_bgMusic.setVolume(50.f);
	m_bgMusic.setLoop(true);
#endif
}
