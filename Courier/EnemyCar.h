#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class EnemyCar
{
private:
	Sprite m_Sprite;

	Texture m_Texture;

	// Where is the enemy car
	Vector2f m_Position;

	bool started = false;

	float m_Speed = 6.0f;
public:
	EnemyCar();
	void spawn(Vector2f resolution);
	FloatRect getPosition();
	Vector2f getCenter();
	Sprite getSprite();
	void update();
	~EnemyCar();
};

