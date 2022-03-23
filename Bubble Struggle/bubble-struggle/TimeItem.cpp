#include "TimeItem.h"
#include "DrawableFactory.h"
#include "RegisterFunctionTemplates.h"
#include "Board.h"

bool TimeItem::m_reg = DrawableFactory::registerMe("TimeItem", &addItem<TimeItem>);

TimeItem::TimeItem(sf::Vector2f pos)
	:AbstractItem(pos , ResourceManager::Texture::TimeItem)
{
}

void TimeItem::collide(Player & p)
{
	p.collide(*this); removeMe();
}


TimeItem::~TimeItem()
{
}
