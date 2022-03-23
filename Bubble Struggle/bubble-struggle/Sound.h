//this is Sound class
//sounds are registered into a deque 
// (use of the deque because vector cut off sounds while
//  copying in order to resize the vector.
//  queue is not enough because we needed random access iterator)
//each sounds that registered also starts playing immediately
//and stopped sounds are cleared by the clear function called in the controller
#pragma once
#include <SFML/Audio.hpp>
#include "ResourceManager.h"

class Sound
{
public:
	~Sound() = default;
	static Sound* instance();
	void reg(ResourceManager::Sound sound);
	void play_bg() { if(m_bgMusic.getStatus() != sf::Music::Playing) m_bgMusic.play(); }
	void stop_bg() { m_bgMusic.stop(); };
	void stopArrow();
	void clear();
private:
	Sound();
	sf::Music m_bgMusic;
	std::deque<sf::Sound> m_sounds;
};