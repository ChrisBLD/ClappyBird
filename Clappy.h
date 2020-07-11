#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Clappy
{
private:
	//Player location
	Vector2f m_Position;

	//Player sprite
	Sprite m_Sprite;

	//Player texture
	Texture m_TextureUp;
	Texture m_TextureDown;

	//Keep track of velocity, acceleration and gravity
	float m_Velocity = 0.0f;
	float m_Acceleration = 0.0f;
	float m_Gravity = 1000.0f;

public:
	Clappy();

	bool hit();

	Sprite getSprite();

	float getVelocity();

	void applyUpForce();

	void update(float elapsedTime, bool spacePressed);

	void spawn();

};