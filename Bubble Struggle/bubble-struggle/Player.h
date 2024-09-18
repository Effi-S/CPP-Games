#pragma once
#include <memory>
#include <vector>
#include "Moveable.h"
#include "LivesBar.h"
#include <array>
#include "AbstractWeapon.h"
#include "ResourceManager.h"
#include <vector>


enum class Direction
{
	Left,
	Right,
	Idle
};
enum WeaponType {
	Simple,
	Laser,
	Frozen,
};

 class Player : public Moveable
{
public:
	Player(sf::Vector2f pos, ResourceManager::Texture img =ResourceManager::Texture::Player1);
	~Player() = default;

	void setKeys(std::array<sf::Keyboard::Key, 3> mykeys);
	void setLivesPos(float x);
	void resetPos();
	void LoseLife();

	sf::FloatRect getWeaponBounds() const;
	sf::FloatRect getBounds() const override { return m_rect.getGlobalBounds(); };

	void shoot();
	
	void setMoveDir(sf::Event &event);
	
	virtual void update(float delta) override;
	virtual void draw() override;

	virtual void collide(class Moveable & other) { };
	virtual void collide(class Unmoveable & other) { };
	virtual void collide(class AbstractWeapon&) {};
	virtual void collide(class AbsBall & ball);
	virtual void collide(class Wall & wall);
	virtual void collide(class LaserItem & item);
	virtual void collide(class SimpleArrowItem & item);
	virtual void collide(class FrozenArrowItem & item);
	virtual void collide(class SheildItem & item);
	virtual void collide(class OneUpItem & item) { ++*m_myLives; };
	virtual void collide(class CashItem & item);
	virtual void collide(class TimeItem & item) ;
	
	virtual void collide(class Door & d);
	void addLifetoBar(class GameToolBar & bar);

	 sf::Vector2f getPos() const { return m_rect.getPosition(); };

private:
	std::array<sf::Keyboard::Key ,3>m_movingKeys = {sf::Keyboard::Left ,sf::Keyboard::Right ,sf::Keyboard::Space };
	
	Direction m_dir = Direction::Idle;
	
	sf::RectangleShape m_rect;

	sf::Clock m_animationClock;
	
	int source_x = 2;
	sf::Vector2f m_startPos;
	float m_speed = 250.f;
	
	float m_delta;

	std::shared_ptr<AbstractWeapon> m_weapon = nullptr;
	std::shared_ptr<class Sheild> m_sheild = nullptr;

	void animate();
	WeaponType m_weaponType = Simple;

	std::shared_ptr<LivesBar> m_myLives;

};

