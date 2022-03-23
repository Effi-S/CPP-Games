//This is the abstract Base class 
//for all of the different types of balls 
//that will apear in the game.
#pragma once
#include <array>
#include "Moveable.h"
#include "ResourceManager.h"



class AbsBall : public Moveable
{
public:
	AbsBall(float radius ,sf::Vector2f pos = sf::Vector2f(600.f, 400.) , bool inverse=false);
	
	void draw() ;
	
	virtual void update(float delta) override;
	
	virtual void split() = 0;
	virtual float Gravity() const;
	
	void setColor(sf::Color color);

	sf::Vector2f getCenter() const;
	
	float getRad() const;
	
	virtual sf::FloatRect getBounds() const override;

	void setTexture(ResourceManager::Texture);

	void setAnimation(sf::IntRect rect);

	sf::Vector2f getNextPos() const { return m_nextPos; };

	void hitWall();
	void setDir(sf::Vector2f dirction);
	static bool isBallsLeftGlobaly() { return (m_GlobalAbsBallCounter > 0); };

	virtual void collide(class Moveable & other); 
	virtual void collide(class Unmoveable & other);
	void collide(class Wall & wall);
	void collide(class Door & d);
	void collide(class Sheild & sh) { hitFloor(); };
	void collide(class Spikes & spike);	
	void collide(class Player & player);
	void collide(class AbstractWeapon & w) ;

	 
	

	

	 ~AbsBall();
private:
	

	void addingItem(std::string str , sf::Vector2f pos);
	void checkInBounds();
	void rangeCheck(float &radius);
	void rangeCheck(sf::Vector2f &pos);
	void hitCeiling();
	virtual void hitFloor();
	void generateItem(sf::Vector2f pos);

	sf::CircleShape m_ball;//the circleshape of the ball itself.
	sf::Vector2f m_nextPos;//the next position of the ball.

	sf::Vector2f m_direction = sf::Vector2f(3.f, -9.6f);//the direction in which the ball is going.
	
	static unsigned m_GlobalAbsBallCounter;//counting how many balls are in play.
	//
	
	const std::array<sf::Color ,8> COLOR={ //array of different ball colours.
	sf::Color::Red,
	sf::Color::Green,
	sf::Color::Cyan,
	sf::Color::Magenta ,
	sf::Color(150 , 50 , 250 ),
	sf::Color::Green,
	sf::Color(255,150,0),
	sf::Color(95,95,95)
	};

};


