#include "stdafx.h"
#include "EnemyCar.h"

EnemyCar::EnemyCar()
{
	m_Texture.loadFromFile("graphics/EnemyCar.png");
	m_Sprite.setTexture(m_Texture);

	// Set the origin of the sprite to the centre, 
	// for smooth rotation
	m_Sprite.setOrigin(37, 18);
	m_Sprite.rotate(90);

	spawn(m_Position);
}

void EnemyCar::spawn(Vector2f resolution)
{
	srand((int)time(0) * 10);
	
	m_Position.x = (rand() % 250);

	if (m_Position.x < 218)
		m_Position.x = m_Position.x + 218;

	if (m_Position.x > 454)
		m_Position.x = m_Position.x - 454;

	m_Position.y = -71;
}

FloatRect EnemyCar::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f EnemyCar::getCenter()
{
	return m_Position;
}

Sprite EnemyCar::getSprite()
{
	return m_Sprite;
}

void EnemyCar::update()
{
	m_Position.y += m_Speed;

	m_Sprite.setPosition(m_Position);

	if (m_Position.y > 530)
	{
		spawn(m_Position);
	}
}

EnemyCar::~EnemyCar()
{
}
