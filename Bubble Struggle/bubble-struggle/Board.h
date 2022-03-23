//This is the singleton Board of the game 
//it holds a vector of all of 
//the moveable or unmoveable 
//objects of the game and can print them and 
//updating them as the game is run.
#pragma once
#include "ResourceManager.h"
#include "Player.h"
#include "Unmoveable.h"
#include "Moveable.h"
#include "Background.h"
#include "Spikes.h"
#include "LivesBar.h"
#include "Wall.h"

class Board
{
public:
	
	static Board & inst() { static Board b; return b; };
	Board &operator=(Board &other) { return inst(); }
	void update(float);
	void collisionHandle();
	void draw();
	void Handle(sf::Event &event);
	void bgFirstLvl() { m_bkg.firstLvl(); }
	void LoseLife();
	void clearPlayers();
	void resetBkg() { m_bkg.firstLvl(); }
	
	void shadeHere(sf::Vector2f pos);
	void restart();
	void nextLvl();

	
	void remove(Moveable * obj);
	void remove(Unmoveable * obj);
	void remove(Player * obj);
	void add(std::shared_ptr<class Moveable>);
	void add(std::shared_ptr<class Unmoveable>);
	void addPlayer(std::unique_ptr<class Player>);
	void addLifeBar(class GameToolBar& bar);
	void add(std::shared_ptr<class LivesBar>);
	
	const std::vector<std::unique_ptr<class Player >>
		&getPlayers() const { return m_players; };
	
	
	~Board() = default;
private:
	Board();

	sf::View m_boardView;//holding the boards view --top 80 percent of the board
	std::vector<std::shared_ptr<class Moveable >> m_moving;//the moveable vector 
	std::vector<std::unique_ptr<class Player >> m_players; // the players vector
	std::vector<std::shared_ptr<class Unmoveable >> m_stationary; // the unmoveable objects vector
	Background m_bkg; // class for printing the background 
	

	
	

};

