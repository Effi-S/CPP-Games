//this is the game toolbar
//it holds a rectngle for the time 
//the lives of the players 
//the score of the game 
//and the level
//and prints all this at the bottom 20 
//percent of the screen.
#pragma once
#include <memory>
#include <vector>
#include "ResourceManager.h"
#include "WindowCONST.h"
#include "Unmoveable.h"
#include "LivesBar.h"
#include "Flame.h"
#include "youSure.h"
class GameToolBar  {

	
public:
	GameToolBar();
	void init();
	void draw();
	static void addScore(unsigned toAdd) {m_score += toAdd;};
	void addMoreTime();
	bool isQuitButtonPressed(sf::Event &event);
	void nextLvl();
	const bool LostLife();
	bool isTimesUp() const; 
	void addLifeBar(std::shared_ptr<LivesBar> toAdd);
	void restart();
	void reset();
	void displayScore();
	bool isLivesLeft() const;

	~GameToolBar();

private:

	void validateLivesLost();
	void LoadText();
	void drawText();

	sf::Clock m_turnTimer;// for timing the turns.
	//rectangles to be printed
	sf::RectangleShape m_timeLeftRect; // time left
	sf::RectangleShape m_quitRect; // the quit button 
	sf::RectangleShape m_bkgRect; // backgroung of the bar
	
	std::vector<std::shared_ptr<LivesBar>> m_lifeBars;// the players lifebars
	std::vector<int> m_validation;// for validating ^^
	bool m_lifeLost = false;// holds weather a life has been found to be lost using ^^

	//flame effects:
	Flame m_flame1=Flame(sf::Vector2f(Window::WIND_X*0.54f, Window::WIND_Y*0.15f), sf::Vector2f(75.f, 350.f)) 
		, m_flame2=Flame(sf::Vector2f(Window::WIND_X*0.37f, Window::WIND_Y*0.15f), sf::Vector2f(75.f, 350.f));
	sf::Font m_font;

	int m_lvl = 1;// the level to be printed
	static int m_score ;//the game score-- static for convenience

	//texters for printing:
	sf::Text m_levelText;
	sf::Text m_scoreText;
	sf::Text txt;

	//a button for asking if the player is sure he wants to quit.
	youSure m_sureButton;

	//view of bottom 20 percent of the board:
	sf::View m_boardView;
};

