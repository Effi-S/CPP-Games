#include "SimpleArrowItem.h"
#include "DrawableFactory.h"
#include "RegisterFunctionTemplates.h"
#include "Player.h"

bool SimpleArrowItem::m_reg = DrawableFactory::registerMe("SimpleArrowItem", &addItem<SimpleArrowItem>);

SimpleArrowItem::SimpleArrowItem(sf::Vector2f pos)
	:AbstractItem(pos , ResourceManager::Texture::simpleItem)
{
}


SimpleArrowItem::~SimpleArrowItem()
{
}

void SimpleArrowItem::collide(Player & p)
{
	p.collide(*this);
}
