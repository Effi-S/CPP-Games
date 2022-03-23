#include "Controller.h"
#include "WindowCONST.h"
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "LevelLoader.h"
#include "Board.h"
#include "PlayerOne.h"
#include "PlayerTwo.h"
#include "Menu.h"

void Controller::run()
{
	m_board.resetBkg();

	while (Window::get().isOpen())
	{
		 m_elapsed = m_clock.restart();

		if (handleEvents())return;
				
		else if (m_waitTimer.getElapsedTime().asSeconds() < 2)
			continue;

		else if (isGameOver())return;

		else if (isGameWon())return;
					
		else if( isLevelWon())continue;
		else if (m_bar.LostLife())
		{
			restartLevel();
			continue;
		}
		else if (m_bar.isTimesUp())
		{			
			doTimeUp();
				continue;						
		}
		else if (m_gameTimer.getElapsedTime() >= m_time)
			doTurn();

		
	}
}

void Controller::init(bool multiPlayer)
{
	m_board.restart();
	m_board.clearPlayers();
	m_loader.setCurrLvl(0);
	m_bar.init();
	m_board.bgFirstLvl();

	m_board.addPlayer(std::move(std::make_unique<PlayerOne>()));
	if (multiPlayer)
		m_board.addPlayer(std::move(std::make_unique<PlayerTwo>()));
	
	m_board.addLifeBar(m_bar);
	m_loader.ReloadLevel();
	m_bar.reset();
}

void Controller::doTurn()
{
	m_gameTimer.restart();
	Sound::instance()->clear();
	//update
	m_board.update(m_elapsed.asSeconds());

	//draw
	Window::get().clear(sf::Color(102, 102, 102));
	m_board.draw();
	m_bar.draw();
	Window::get().display();
}

void Controller::doTimeUp()
{
	display(ResourceManager::Texture::OutOfTime);
	Board::inst().LoseLife();
}

void Controller::resize()
{
	auto & wind = Window::get();
	sf::Vector2f size 
		= static_cast<sf::Vector2f>(wind.getSize());

	wind.setSize(static_cast<sf::Vector2u>(size));

	auto gridView = wind.getView();

	gridView.setCenter(size / 2.f);
	gridView.setSize(size); 

	wind.setView(gridView);
	
}

void Controller::outOfTime()
{
	sf::RectangleShape bkg;
	bkg.setSize(sf::Vector2f(Window::WIND_X, Window::WIND_Y));
	bkg.setTexture(ResourceManager::instance()->getTexture(ResourceManager::Texture::OutOfTime));
	auto &wind = Window::get();
	wind.draw(bkg);

}

void Controller::display(ResourceManager::Texture img)
{
	auto &wind = Window::get();
	wind.clear(sf::Color(102, 102, 102));
	m_board.draw();

	sf::RectangleShape bkg;
	bkg.setSize(sf::Vector2f(Window::WIND_X, Window::WIND_Y));
	bkg.setTexture(ResourceManager::instance()->getTexture(img));
	wind.draw(bkg);
	m_bar.draw();
	
	Window::get().display();
	
	m_gameTimer.restart();
	m_loader.ReloadLevel();
	m_bar.restart();
	m_gameTimer.restart();
	m_waitTimer.restart();
}

void Controller::restartLevel()
{
	Board::inst().restart();
	m_loader.ReloadLevel();
	m_gameTimer.restart();
	m_waitTimer.restart();
}

void Controller::displayScoreScreen()
{
	Menu menu(ResourceManager::instance()->getTexture(ResourceManager::Texture::ScoreBoard));
	bool flag = false;
	menu.add("back", std::make_unique<Back>(flag, sf::Vector2f(240, 580)));

	while (!flag && Window::get().isOpen())
	{
		Window::get().clear();
		menu.run();
		m_bar.displayScore();
		Window::get().display();
	}
}

bool Controller::handleEvents()
{
	while (Window::get().pollEvent(m_event))
	{ 
		if (m_event.type == sf::Event::Closed)
			Window::get().close();
		else if (m_event.type == sf::Event::Resized)
			resize();
		else if (m_event.type == sf::Event::KeyReleased)
		{
			if (m_event.key.code == sf::Keyboard::Down) //cheat for skipping levels.
				Board::inst().restart();
			
		}
		else if (m_event.type == sf::Event::MouseButtonPressed ||
			m_event.type == sf::Event::MouseMoved)
		{
			if (m_bar.isQuitButtonPressed(m_event))
				return true;
		}

		m_board.Handle(m_event);
	}
	return false;
}

bool Controller::isLevelWon()
{
	if (AbsBall::isBallsLeftGlobaly())
		return false;

	//init next level
	m_bar.nextLvl();
	m_loader.LoadNextLevel();
	m_gameTimer.restart();
	m_waitTimer.restart();
	return false;
}

bool Controller::isGameOver()
{
	if (!m_bar.isLivesLeft())
	{
		display(ResourceManager::Texture::OutOfLives);
		sf::Clock temp;
		while (temp.getElapsedTime().asSeconds() < 3);
		m_bar.reset();
		displayScoreScreen();
		return true;
	}

	return false;
}

bool Controller::isGameWon()
{
	if (AbsBall::isBallsLeftGlobaly())
		return false;

	if (m_loader.isLastLevel())
	{   
		m_bar.reset();
		display(ResourceManager::Texture::youWon);
		m_waitTimer.restart();
		while (m_waitTimer.getElapsedTime().asSeconds() < 2);
		displayScoreScreen();
		return true;
	}
	
	return false;
}

