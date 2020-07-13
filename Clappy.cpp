#include "Clappy.h"
#include "TextureHolder.h"
#include <iostream>

Clappy::Clappy()
{
	m_TextureDown = TextureHolder::GetTexture("graphics/clappyDown.png");
	m_TextureUp = TextureHolder::GetTexture("graphics/clappyUp.png");
	m_TextureDead = TextureHolder::GetTexture("graphics/rip.png");

	restart();
}



Sprite Clappy::getSprite()
{
	return m_Sprite;
}

float Clappy::getVelocity()
{
	return m_Velocity;
}

void Clappy::update(float elapsedTime, bool spacePressed)
{
	if (spacePressed) {
		m_Acceleration = 0.0f;
		m_Velocity = -m_Gravity / 3.0f;
	} 
	else //If the user hasn't pressed space, clappy will fall:
	{
		m_Acceleration += m_Gravity * elapsedTime;
	}

	if (m_Acceleration >= m_Gravity)
	{
		m_Acceleration = m_Gravity;
	}


	m_Velocity += m_Acceleration * elapsedTime;
	m_Position.y += m_Velocity * elapsedTime;

	if (m_Velocity > 0) { //Clappy is falling -> show falling tex
		m_Sprite.setTexture(m_TextureDown);
	}
	else //Clappy is rising -> show rising tex
	{
		m_Sprite.setTexture(m_TextureUp);
	}

	//m_Position.y = m_Position.y + (elapsedTime * gravity);
	m_Sprite.setPosition(m_Position);
}

Vector2f Clappy::getPosition()
{
	return m_Position;
}

void Clappy::kill()
{
	m_AliveSprite = m_Sprite;
	m_DeadSprite.setPosition(m_Position);
	m_Sprite = m_DeadSprite;

}

void Clappy::restart()
{
	m_Position.x = STARTING_POS.x;
	m_Position.y = STARTING_POS.y;

	m_Velocity = STARTING_VELOCITY;
	m_Acceleration = STARTING_ACCEL;
	m_Gravity = STARTING_GRAV;

	m_Sprite = m_AliveSprite;
	m_DeadSprite.setTexture(m_TextureDead);

	m_Sprite.setTexture(m_TextureDown);
	sf::Vector2f targetSize(CLAPPY_SIZE_X, CLAPPY_SIZE_Y);
	m_Sprite.setScale(
		targetSize.x / m_Sprite.getLocalBounds().width,
		targetSize.y / m_Sprite.getLocalBounds().height);

	m_Sprite.setOrigin(CLAPPY_SIZE_X / 2.0f, CLAPPY_SIZE_Y / 2.0f);

	m_Sprite.setPosition(m_Position);

	
}