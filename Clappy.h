#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Clappy
{
private:
	
	//Define starting location
	const Vector2f STARTING_POS = Vector2f(400.0f, 400.0f);

	//Define starting velocity, acceleration and gravity
	const float STARTING_VELOCITY = 0.0f;
	const float STARTING_ACCEL = 0.0f;
	const float STARTING_GRAV = 1000.0f;

	//Player location
	Vector2f m_Position;

	//Player sprite
	Sprite m_Sprite;

	//Player texture
	Texture m_TextureUp;
	Texture m_TextureDown;

	//Keep track of velocity, acceleration and gravity
	float m_Velocity;
	float m_Acceleration;
	float m_Gravity;

public:
	Clappy();

	Sprite getSprite();

	float getVelocity();

	Vector2f getPosition();

	void restart();

	void update(float elapsedTime, bool spacePressed);

};