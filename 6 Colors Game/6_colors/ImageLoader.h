//this is a singletone implementation of a image loader 
//the user can call an instance(static class object) and get any image 
//that is used in this program.
#pragma once

#include <SFML/Graphics.hpp>
 
const int TOOLS=5;


class ImageLoader
{
public:
	ImageLoader(ImageLoader &other);

	static ImageLoader& instance();

	ImageLoader & operator=(ImageLoader & other);

	sf::Texture * getSquare();
	sf::Texture *getFilledSquare();
	sf::Texture *getXSquare();
	sf::Texture *getTool(int index);


	~ImageLoader();
private:
	ImageLoader();

	sf::Texture  m_square;
	sf::Texture m_filledSquare;
	sf::Texture m_XSquare;
	sf::Texture m_tools[TOOLS];
	sf::Texture m_otherMode;
	
};

