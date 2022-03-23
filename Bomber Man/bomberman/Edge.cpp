//***********this is the edge class******************
//this class is derrived from the Placeable base class
//no real functionality apart from blocking any character from entering it.

//**********************************************
//--------includes-------
#include "Edge.h"
//----------------------


//==================================================
//window Pos and img are for Placeable constructor.
Edge::Edge(sf::RenderWindow &window ,sf::Vector2f pos, sf::Texture * img)
	:Placeable(window, pos, img)
{
	m_empty = false;
}
//----------------------
//======================
Edge::~Edge()
{
}
//----------------------