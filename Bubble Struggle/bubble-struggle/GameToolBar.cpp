#include "GameToolBar.h"
#include <sstream>
#include <memory>

int GameToolBar::m_score = 0;

GameToolBar::GameToolBar()

{
	m_bkgRect.setPosition(0.f, 0.f);
	m_bkgRect.setSize(sf::Vector2f((float)Window::get().getSize().x, (float)Window::WIND_Y));
	m_bkgRect.setTexture(ResourceManager::instance()->getTexture(ResourceManager::Texture::bottom_bar));

	m_timeLeftRect.setPosition(sf::Vector2f(1.f, 1.f));
	m_timeLeftRect.setSize(sf::Vector2f(Window::WIND_X, Window::WIND_Y*0.5f));
	m_timeLeftRect.setFillColor(sf::Color::Red);

	m_quitRect.setSize(sf::Vector2f(150.f, 250.f));
	m_quitRect.setPosition(Window::WIND_X*0.3f, Window::WIND_Y*0.5f);
	m_quitRect.setFillColor(sf::Color(95, 95, 95));

	
	
	LoadText();

	sf::Vector2u size = Window::get().getSize();
	m_boardView.reset(sf::FloatRect(0.f, 0.f, (float)size.x, (float)size.y));
	m_boardView.setViewport(sf::FloatRect(0.f, 0.8f, 1.f, 0.20f));
}

void GameToolBar::init()
{
	m_lifeBars.clear();
	m_score = 0;	
}

void GameToolBar::draw()
{
	sf::RenderWindow & wind = Window::get();
	wind.setView(m_boardView);

	auto pos = m_timeLeftRect.getPosition();

	m_timeLeftRect.setPosition(pos.x - 5 * m_turnTimer.restart().asSeconds(), pos.y);
	wind.draw(m_timeLeftRect);

	wind.draw(m_quitRect);

	wind.draw(m_bkgRect);

	for (auto &x : m_lifeBars)
	{
	if (x->isMoreTime())addMoreTime();
	x->print();
	}
		
	validateLivesLost();

	drawText();

	m_flame2.draw();
	m_flame1.draw();

	
	wind.getDefaultView();
}

void GameToolBar::addMoreTime()
{
	m_timeLeftRect.move(20, 0);
}

bool GameToolBar::isQuitButtonPressed(sf::Event & event)
{
	sf::RenderWindow & wind = Window::get();
	wind.setView(m_boardView);
	
	auto & window = Window::get();
	
	sf::Vector2f mouseplace(window.mapPixelToCoords({ event.mouseMove.x ,event.mouseMove.y }));

	sf::Vector2f mouseClick(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }));
	
	auto bounds = m_quitRect.getGlobalBounds();

	wind.getDefaultView();

	if (bounds.contains(mouseClick))
		return m_sureButton.isQuit(*this);
	
			
					
	else if (bounds.contains(mouseplace))
		m_quitRect.setFillColor(sf::Color::Yellow);
	else
		m_quitRect.setFillColor(sf::Color(95, 95, 95));

	return false;
}

void GameToolBar::nextLvl()
{
	m_lvl++;
	restart();
	
}

const bool GameToolBar::LostLife() 
{
	if (m_lifeLost) {
		m_lifeLost = false;
		return true;
	}
	return false;
	
}

bool GameToolBar::isTimesUp() const
{
	return (m_timeLeftRect.getPosition().x + m_timeLeftRect.getSize().x < 0);
}

void GameToolBar::addLifeBar( std::shared_ptr<LivesBar> toAdd)
{
	int i = toAdd->getCount();	
	m_lifeBars.push_back(toAdd);
	m_validation.push_back(i);
}



void GameToolBar::restart()
{
	/*for (auto & x : m_lifeBars)
		x->restart();*/

	m_lifeLost = false;
	m_timeLeftRect.setPosition(sf::Vector2f(0.f, 0.f));	
	m_turnTimer.restart();
}

void GameToolBar::reset()
{
	restart();
	m_lvl = 1;
}

void GameToolBar::displayScore()
{
	Window::get().setView(Window::get().getDefaultView());
	txt = sf::Text("00", m_font, 84);
	txt.setFillColor(sf::Color::Black);
	txt.setPosition(225, 360);
	txt.setCharacterSize(30);
	txt.setString(std::to_string(m_score));
	Window::get().draw(txt);
}

bool GameToolBar::isLivesLeft() const
{
	for (auto &lives : m_lifeBars)
	{
		if (lives->isLivesLeft())
			return true;
	}
	return false;
}



GameToolBar::~GameToolBar()
{
}

void GameToolBar::validateLivesLost()
{
	int i = 0;
	for (auto &x : m_lifeBars)
	{
		int count = x->getCount();
		if (count < m_validation[i])
			m_lifeLost = true;

		m_validation[i] = count;
			i++;
	}
}

void GameToolBar::LoadText()
{
	m_font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

	m_levelText= sf::Text("00", m_font, 45);
	m_scoreText= sf::Text("00", m_font, 45);
	m_scoreText.scale(1.f, 3.f);
	m_levelText.scale(1.f, 4.f);
	
	m_levelText .setFillColor(sf::Color::Black);
	m_scoreText.setFillColor(sf::Color::Black);

	m_levelText .setPosition(Window::WIND_X*0.485f, Window::WIND_Y*0.68f);
	m_scoreText.setPosition(Window::WIND_X*0.2f, Window::WIND_Y *0.72f);
	
}
void GameToolBar::drawText()
{
	m_levelText.setString(std::to_string(m_lvl));
	m_scoreText.setString(std::to_string(m_score));
	

	sf::RenderWindow & wind = Window::get();
	wind.draw(m_levelText);
	wind.draw(m_scoreText);
}


