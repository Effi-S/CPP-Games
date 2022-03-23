//creates a thread for loading 
//for 7 seconds until the game loads.
#pragma once
#include <SFML/Graphics.hpp>
#include <thread>
class LoadScreen
{
public:
	LoadScreen();
	void wait();
	
	~LoadScreen();
	
private:
	
	std::thread m_thread;
};

