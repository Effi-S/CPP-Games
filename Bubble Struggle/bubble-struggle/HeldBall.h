//this is a  template Wrapper class 
//for holding a ball with a shared ptr 
//that istead of creating a ball on its own 
//links them with this shared ptr.
#pragma once
#include "Board.h"
#include "AbsBall.h"
#include <memory>

template<class T>
class HeldBall:
	public T 
{
public:
	HeldBall(float radius, sf::Vector2f pos, bool inverse ,
		std::shared_ptr<int> orig);
	
	void split() override; // creating the balls differently.
	~HeldBall()=default;
private:
	std::shared_ptr<int>  m_checker; //the shared ptr for linking all of the balls.
};

template<class T>
inline HeldBall<T>::HeldBall(float radius, sf::Vector2f pos, bool inverse,
	std::shared_ptr<int> checker)
	:T(radius, pos, inverse) , m_checker(checker)
{
	
}

template<class T>
inline void HeldBall<T>::split()
{
	Board & board = Board::inst();
	auto rad = T::getRad();

	if (rad <= 10.f)
	{
		Board::inst().remove(this);
		return;
	};

	sf::Vector2f pos = T::getCenter();

	board.add(std::make_shared <HeldBall<T>>(rad - 5, pos, true, m_checker));

	board.add(std::make_shared <HeldBall<T>>(rad - 5, pos, false, m_checker));

	Board::inst().remove(this);
}

