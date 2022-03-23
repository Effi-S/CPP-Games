#pragma once
//derrived from AbstractItem 
//this is a item  for adding to the players score.
#include "AbstractItem.h"

class CashItem :
	public AbstractItem
{
public:
	CashItem(sf::Vector2f pos);
	~CashItem();
	virtual void collide(class Player & p) override;
	
private:
	static bool m_reg;// registration 
};

