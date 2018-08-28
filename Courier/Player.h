#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
private:
	bool started = false;
	const float START_SPEED = 200;
	const float START_HEALTH = 100;

	// Where is the player
	Vector2f m_Position;

	// Of course we will need a sprite
	Sprite m_Sprite;

	// And a texture
	// !!Watch this space!!
	Texture m_Texture;

	// Player health
	float m_Health = 90;

	// When was the player last hit?
	Time m_LastHit;

	// What is the screen resolution
	Vector2f m_Resolution;

	// What size is the current arena
	IntRect m_Arena;

	bool m_UpPressed;
	bool m_DownPressed;
	bool m_LeftPressed;
	bool m_RightPressed;

	// Angle the player is facing
	float m_Angle = -90;

	// How fast is the player
	float m_Speed = 4.0f;
public:
	Player();
	
	void spawn(IntRect arena, Vector2f resolution);

	// Handle the player getting hit by a zombie
	bool hit(Time timeHit);

	// How long ago was the player last hit
	Time getLastTimeHit();

	// Where is the player
	FloatRect getPosition();

	// Where is the center of the player
	Vector2f getCenter();

	// Send a copy of the sprite to main
	Sprite getSprite();

	// The next four functions move the player
	void moveLeft();

	void moveRight();

	void moveUp();

	void moveDown();

	// Stop the player moving in a specific direction
	void stopLeft();

	void stopRight();

	void stopUp();

	void stopDown();

	// We will call this function once every frame
	void update();
	
	float getDirection();

	void decreaseHealth(float hit);

	void increaseHealth(float increment);

	int getHealth();
	~Player();
};

