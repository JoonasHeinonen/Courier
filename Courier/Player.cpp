#include "stdafx.h"
#include "Player.h"
#include <iostream>

using namespace std;

Player::Player()
{
	m_Texture.loadFromFile("graphics/PlayerCar.png");
	m_Sprite.setTexture(m_Texture);

	// Set the origin of the sprite to the centre, 
	// for smooth rotation
	m_Sprite.setOrigin(38, 16);
	m_Sprite.setRotation(270);
	std::cout << m_Sprite.getRotation() << "\n";
}

void Player::spawn(IntRect arena, Vector2f resolution)
{
	if (started == false)
	{
		// Place the player in the middle of the arena
		m_Position.x = 640 / 2;
		m_Position.y = 480 / 2;
		started = true;
	}

	// Copy the details of the arena to the player's m_Arena
	m_Arena.left = 0;
	m_Arena.width = 640;
	m_Arena.top = 0;
	m_Arena.height = 480;

	// Strore the resolution for future use
	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;
}

Time Player::getLastTimeHit()
{
	return m_LastHit;
}

// Handle the player getting hit by a zombie
bool Player::hit(Time timeHit)
{
	if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200)
	{
		m_LastHit = timeHit;
		m_Health -= 30;
		cout << "Collision occurred.\n";
		return true;
	}
	else
	{
		return false;
	}
}

FloatRect Player::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f Player::getCenter()
{
	return m_Position;
}

Sprite Player::getSprite()
{
	return m_Sprite;
}

void Player::moveLeft()
{
	m_LeftPressed = true;
}

void Player::moveRight()
{
	m_RightPressed = true;
}

void Player::moveUp()
{
	m_UpPressed = true;
}

void Player::moveDown()
{
	m_DownPressed = true;
}

void Player::stopLeft()
{
	m_LeftPressed = false;
}

void Player::stopRight()
{
	m_RightPressed = false;
}

void Player::stopUp()
{
	m_UpPressed = false;
}

void Player::stopDown()
{
	m_DownPressed = false;
}

void Player::update()
{
	if (m_Health < 90)
	{
		increaseHealth(0.3);
	}

	if (m_UpPressed)
	{
		m_Position.y -= m_Speed;
	}

	if (m_DownPressed)
	{
		m_Position.y += m_Speed;
	}

	if (m_RightPressed)
	{
		m_Position.x += m_Speed;
		if (!m_UpPressed)
		{
			m_Sprite.setRotation(m_Sprite.getRotation() + 2);
			if (m_Sprite.getRotation() >= 280)
			{
				m_Sprite.setRotation(280);
			}
		}
		
	}

	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed;
		if (!m_UpPressed)
		{
			m_Sprite.setRotation(m_Sprite.getRotation() - 2);
			if (m_Sprite.getRotation() <= 260)
			{
				m_Sprite.setRotation(260);
			}
		}
	}

	// Rotate when both up and left/right are pressed

	if (m_RightPressed && m_UpPressed)
	{
		m_Sprite.setRotation(m_Sprite.getRotation() + 2);
		if (m_Sprite.getRotation() >= 315)
		{
			m_Sprite.setRotation(315);
		}
	}

	if (m_LeftPressed && m_UpPressed)
	{
		m_Sprite.setRotation(m_Sprite.getRotation() - 2);
		if (m_Sprite.getRotation() <= 225)
		{
			m_Sprite.setRotation(225);
		}
	}

	// When up + left/right are released

	if (m_Sprite.getRotation() >= 270 && !m_LeftPressed && !m_UpPressed)
	{
		if (m_Sprite.getRotation() <= 270)
		{
			m_Sprite.setRotation(270);
		}
	}
	else if (m_Sprite.getRotation() <= 270 && !m_RightPressed && !m_UpPressed)
	{
		if (m_Sprite.getRotation() >= 270)
		{
			m_Sprite.setRotation(270);
		}
	}

	// When only left/right are released

	if (m_Sprite.getRotation() <= 270 && !m_LeftPressed)
	{
		m_Sprite.setRotation(m_Sprite.getRotation() + 2);
		if (m_Sprite.getRotation() >= 270)
		{
			m_Sprite.setRotation(270);
		}
	}
	else if (m_Sprite.getRotation() >= 270 && !m_RightPressed)
	{
		m_Sprite.setRotation(m_Sprite.getRotation() - 2);
		if (m_Sprite.getRotation() <= 270)
		{
			m_Sprite.setRotation(270);
		}
	}

	std::cout << m_Sprite.getRotation() << std::endl;

	// Keep the player car in the road
	if (m_Position.x > 439)
	{
		m_Position.x = 439;
	}

	if (m_Position.x < 201)
	{
		m_Position.x = 201;
	}

	if (m_Position.y > 446)
	{
		m_Position.y = 446;
	}

	if (m_Position.y < 35)
	{
		m_Position.y = 35;
	}

	m_Sprite.setPosition(m_Position);
}

float Player::getDirection()
{
	return m_Sprite.getRotation();
}

int Player::getHealth()
{
	return m_Health;
}

void Player::decreaseHealth(float hit)
{
	m_Health -= hit;
}

void Player::increaseHealth(float increment)
{
	m_Health += increment;
}

Player::~Player()
{
}