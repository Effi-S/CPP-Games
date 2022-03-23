#pragma once
//a class for the game background
	//any files called "level<num>.png" 
	//in the folder "textures" will be added
	//to a vector of background images
	//the <num> must have all prior numbers in order 
	//to be added.the addition is from 1 onwards.
//as well this class can shade the background to add effect.  
#include "WindowCONST.h"
#include "ResourceManager.h"
class Background 
	
{
public:
	Background();
	void nextLvl();
	void draw() { Window::get().draw(m_spr); };
	void setShade(sf::Vector2f pos);
	void Shade();

	void firstLvl();
	~Background();

private:
	std::vector<sf::Texture*> m_LvlTextures;
	int m_levels;
	
	int m_lvl=0;
	sf::Sprite m_spr;//the background sprite

	sf::Sprite m_shadeEffect;// an extra effect 
	sf::Clock m_shadingClock;// the effects timer
	bool m_isShading; // boolian for weather shading or not
};

