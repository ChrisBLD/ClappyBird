#include "Clappy.h"
#include "TextureHolder.h"
#include <iostream>

Clappy::Clappy()
{
	m_TextureDown = TextureHolder::GetTexture("graphics/clappyDown.png");
	m_TextureUp = TextureHolder::GetTexture("graphics/clappyUp.png");

	//When the game starts, clappy is falling. So set texture down.
	m_Sprite.setTexture(m_TextureDown);

	//Initialise starting position.
	m_Position.x = 400.0f;
	m_Position.y = 400.0f;

	m_Sprite.setPosition(m_Position);

	//Scale clappy image to not be enormous
	sf::Vector2f targetSize(120.0f, 110.66f);
	m_Sprite.setScale(
		targetSize.x / m_Sprite.getLocalBounds().width,
		targetSize.y / m_Sprite.getLocalBounds().height);
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
