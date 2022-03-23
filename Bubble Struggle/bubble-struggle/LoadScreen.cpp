#include "LoadScreen.h"
#include "WindowCONST.h"
#include "ZeroGravityBall.h"
#include "Moveable.h"
#include "Unmoveable.h"
#include <thread>

bool isDone = false;

void threadFunc()
{
	ZeroGravityBall ball(50.f);
	sf::Texture img;	
	sf::RectangleShape rect;
	sf::Clock clock;
	auto &wind = Window::get();
	sf::Event event;
	sf::Time time;

	img.loadFromFile("resources/textures/menu/loading.png");
	rect.setTexture(&img);
	rect.setSize(sf::Vector2f(Window::WIND_X, Window::WIND_Y));	
	ball.setColor(sf::Color::Red);	
	wind.setActive(true);
	
	while (wind.isOpen())
	{
		while (wind.pollEvent(event))
			if (event.type == sf::Event::Closed)Window::get().close();

		if (clock.getElapsedTime().asSeconds() < 0.04)continue;
		time += clock.restart();

		
		ball.update(1.f);
		wind.clear(sf::Color(192, 221, 202));
		wind.draw(rect);
		ball.draw();
		wind.display();

		if (time.asSeconds() > 5)
			if (isDone)
				break;
			else
				time = sf::seconds(0);
		
	}
	
	wind.setActive(false);
}

LoadScreen::LoadScreen()
	:m_thread(threadFunc)
{
		
}

void LoadScreen::wait()
{
	auto &wind = Window::get();
	isDone = true;
	m_thread.join();
	wind.setActive(true);
	wind.setKeyRepeatEnabled(false);
	wind.setMouseCursorGrabbed(false);
}



LoadScreen::~LoadScreen()
{
}



