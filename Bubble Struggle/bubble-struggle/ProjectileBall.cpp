#include "ProjectileBall.h"
#include "Ball.h"
#include "Wall.h"
#include "AbstractWeapon.h"
#include "Board.h"

ProjectileBall::ProjectileBall(sf::Vector2f StartPos, sf::Vector2f TargetPos)
	:AbsBall(20.f,	StartPos )
{
	setDir(claculateDirection(StartPos, TargetPos));
}

void ProjectileBall::split()
{
	Board & board = Board::inst();
	board.add(std::make_shared<Ball>(10.f , getCenter()));
	board.add(std::make_shared<Ball>(10.f, getCenter(), true));
	board.remove(this);
}

void ProjectileBall::collide(Wall & wall)
{
	if (wall.getBounds().intersects(getBounds()))
		split();
}

sf::Vector2f ProjectileBall::claculateDirection(sf::Vector2f start, sf::Vector2f target)
{
	sf::Vector2f v(target.x - start.x , target.y - start.y);
	float normal = std::sqrt(v.x*v.x + v.y*v.y);
	return sf::Vector2f(m_speedOfMovement*v.x / normal,
		m_speedOfMovement*v.y / normal);
}

ProjectileBall::~ProjectileBall()
{
}
