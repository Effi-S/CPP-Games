#include "ImageLoader.h"

ImageLoader::ImageLoader()
{
	m_square.loadFromFile("images/gem.png");
	m_filledSquare.loadFromFile("images/gem2.png");
	m_XSquare.loadFromFile("images/gem3.png");
	

	m_tools[0].loadFromFile("images/replay.png");
	m_tools[1].loadFromFile("images/resize.png");
	m_tools[2].loadFromFile("images/multi.png");
	m_tools[3].loadFromFile("images/exit.png");
	m_otherMode.loadFromFile("images/single.png");
	
}

//singletone instance, getting static ImageLoader
ImageLoader & ImageLoader::instance()
{
	static ImageLoader r;
	return r;
}
//copy constructor
ImageLoader::ImageLoader(ImageLoader & other)
{
	*this = other.instance();
}


// = operator 
ImageLoader & ImageLoader::operator=(ImageLoader & other)
{
	return other.instance();
}

//getting a regular square texture
sf::Texture * ImageLoader::getSquare()
{
	return &m_square;
}

//getting a filled square texture.
sf::Texture * ImageLoader::getFilledSquare()
{
	return &m_filledSquare;
}

//getting a square with an x on it 
sf::Texture * ImageLoader::getXSquare()
{
	return &m_XSquare;
}

//getting a toolbar image ,index is the toolbar 
//image to be returned
sf::Texture * ImageLoader::getTool(int index)
{
	if (index == 2)
		std::swap(m_tools[2], m_otherMode);

	return &m_tools[index];
}


ImageLoader::~ImageLoader()
{
}
