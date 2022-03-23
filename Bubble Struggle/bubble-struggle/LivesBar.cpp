#include "LivesBar.h"
#include "ResourceManager.h"
#include "WindowCONST.h"


void LivesBar::operator++()
{
	size_t size = m_rects.size();

	if (size >= 9)return;

	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(40.f, 120.f));
	rect.setPosition(m_start + (size*45 ), Window::WIND_Y / 2 - 55.f);
	rect.setTexture(ResourceManager::instance()->getTexture(ResourceManager::Texture::Fire));
	m_rects.push_back(rect);

}

void LivesBar::operator--()
{
	size_t size = m_rects.size();
	if (size > 0)
		m_rects.pop_back();
}

void LivesBar::restart()
{
	LivesBar tmp(m_start);
	m_rects.empty();
	m_rects = tmp.m_rects;
}

void LivesBar::print()
{
	for (auto i : m_rects)
		Window::get().draw(i);
}

bool LivesBar::isMoreTime()
{
	if (m_moreTime)
	{
		m_moreTime = false;
		return true;
	}
	else
	return false;
}

int LivesBar::getCount()
{
	return (int)m_rects.size();
}

LivesBar::LivesBar(float start)
{
	m_start = start;
	for (int i = 0; i < 5; i++)
		operator++();

}


