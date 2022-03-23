#include "FrozenArrowItem.h"
#include "DrawableFactory.h"
#include "RegisterFunctionTemplates.h"
#include "Player.h"


bool FrozenArrowItem::m_reg = DrawableFactory::registerMe("FrozenArrowItem", &addItem<FrozenArrowItem>);

FrozenArrowItem::FrozenArrowItem(sf::Vector2f pos)
	:AbstractItem(pos , ResourceManager::Texture::FrozenItem)
{
}


FrozenArrowItem::~FrozenArrowItem()
{
}

void FrozenArrowItem::collide(Player & p)
{
	p.collide(*this);
}
