#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Road
{
private:
	Sprite m_Sprite;

	Texture m_Texture;

	// Where is the road
	Vector2f m_Position;

	float m_Speed = 4.0f;
public:
	Road();
	void setPosition(float x, float y);
	void spawn(Vector2f resolution);
	FloatRect getPosition();
	Sprite getSprite();
	void update();
	~Road();
};

