#include "SheildItem.h"
#include "DrawableFactory.h"
#include "RegisterFunctionTemplates.h"
#include "Board.h"



bool SheildItem::m_reg = DrawableFactory::registerMe("SheildItem", &addItem<SheildItem>);

SheildItem::SheildItem(sf::Vector2f pos)
	:AbstractItem(pos , ResourceManager::Texture::SheildItem)
{
}


SheildItem::~SheildItem()
{
}

void SheildItem::collide(Player & p)
{
	p.collide(*this);
	removeMe();
}