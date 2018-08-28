#include "stdafx.h"
#include "Road.h"


Road::Road()
{
	m_Texture.loadFromFile("graphics/road.png");
	m_Sprite.setTexture(m_Texture);

	// Set the origin of the sprite to the centre, 
	// for smooth rotation
	m_Sprite.setOrigin(0, 0);
}

void Road::setPosition(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

void Road::spawn(Vector2f resolution)
{
	m_Position.y = -480;
}

FloatRect Road::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Sprite Road::getSprite()
{
	return m_Sprite;
}

void Road::update()
{
	m_Position.y += m_Speed;

	m_Sprite.setPosition(m_Position);

	if (m_Position.y >= 480)
	{
		spawn(m_Position);
	}
}

Road::~Road()
{
}