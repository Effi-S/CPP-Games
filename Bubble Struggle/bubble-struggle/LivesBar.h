//this is a class for holding and 
//printing a vector of 
//upto 9 rectangles onto the 
//screen 
//a live is added and removed with ++, -- operators
//this class also holds a boolian for if the player adds time.
#pragma once
#include <SFML/Graphics.hpp>
class LivesBar {
public:
	void operator++();
	void operator--();
	bool isLivesLeft() const { return m_rects.size() > 0; }
	void restart();
	void print();
	bool isMoreTime();
	void setMoreTime() { m_moreTime = true; }
	int getCount();
	LivesBar(float start = 10);
	~LivesBar() = default;
private:

	bool m_moreTime = false; // boolian for if the player received time item
	std::vector<sf::RectangleShape> m_rects; // the vector of lives
	float m_start; // starting postion for drawing.

};

