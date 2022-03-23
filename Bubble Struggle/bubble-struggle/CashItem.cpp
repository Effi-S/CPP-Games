#include "CashItem.h"
#include "DrawableFactory.h"
#include "RegisterFunctionTemplates.h"
#include "Board.h"

bool CashItem::m_reg = DrawableFactory::registerMe("CashItem", &addItem<CashItem>);

CashItem::CashItem(sf::Vector2f pos)
	:AbstractItem(pos, ResourceManager::Texture::CashItem)
{
}


CashItem::~CashItem()
{
}

void CashItem::collide(Player & p)
{
	p.collide(*this); removeMe();
}
