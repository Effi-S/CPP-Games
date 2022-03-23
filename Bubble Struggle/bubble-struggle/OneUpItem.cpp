#include "OneUpItem.h"
#include "DrawableFactory.h"
#include "RegisterFunctionTemplates.h"
#include "Board.h"

bool OneUpItem::m_reg = DrawableFactory::registerMe("OneUpItem", &addItem< OneUpItem>);

OneUpItem::OneUpItem(sf::Vector2f pos)
	:AbstractItem(pos , ResourceManager::Texture::OneUpItem)
{
}

void OneUpItem::collide(Player & p)
{
	p.collide(*this); removeMe();
}


OneUpItem::~OneUpItem()
{
}
