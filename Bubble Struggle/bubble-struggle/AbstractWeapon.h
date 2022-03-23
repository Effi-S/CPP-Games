#pragma once
//this is the base class for all weapons used in the game
//derrived from Moveable (so can be added to the board)
//a weapon is given aposition on the screen and then moves upwards 
//untill hitting a wall or door or leaving the screen.
#include "Moveable.h"
#include "ResourceManager.h"


class AbstractWeapon : public Moveable
{
public:
	sf::Vector2f getPosition() const { return m_sprite.getPosition(); }
	virtual sf::FloatRect getBounds() const override {return m_sprite.getGlobalBounds(); }

	AbstractWeapon(sf::Vector2f pos, ResourceManager::Texture tex);
	~AbstractWeapon() = default;

	
	void draw();


	virtual void collide(class Moveable & other) { other.collide(*this); };
	virtual void collide(class Unmoveable & other) ;

	virtual void update(float delta) override;
	void collide(class Wall & wall);
	void collide(class Spikes & spikes);
	void collide(class AbsBall & ball);
	void collide(class Player&) {};

	void setScale(const float factor) ;

private:
	sf::Sprite m_sprite; // the weapons sprite itself
	sf::Vector2f m_pos; // the position of the sprite in the game
	sf::Clock m_clock; // timer for updating movement smoothly.
	float m_speed = 400.f; // the speed of movement upwards
};

