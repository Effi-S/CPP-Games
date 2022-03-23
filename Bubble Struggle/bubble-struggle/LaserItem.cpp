#include "LaserItem.h"
#include "Board.h"
#include "DrawableFactory.h"
#include "RegisterFunctionTemplates.h"
#include "Wall.h"
#include "Player.h"

bool LaserItem::m_reg= DrawableFactory::registerMe("LaserItem", &addItem<LaserItem>);

LaserItem::LaserItem( sf::Vector2f pos)
	:AbstractItem( pos, ResourceManager::Texture::LaserItem)
{
}


LaserItem::~LaserItem()
{
}

void LaserItem::collide(Player & p)
{
	p.collide(*this);
}
