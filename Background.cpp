#include "Background.h"
#include "TextureHolder.h"
#include <iostream>

Background::Background(bool whichBG)
{
	m_IsPrimary = whichBG;

	m_Texture = TextureHolder::GetTexture("graphics/backgroundDouble.png");
	m_Sprite.setTexture(m_Texture);
	
	if (m_IsPrimary)
	{
		m_PositionX = 0.0f;
	}
	else {
		m_PositionX = 3830.0f;
	}
}

void Background::setNextPos(float newPos)
{
	//Sets the position of the background to connect to the currently scrolling one.
	m_PositionX = newPos;
	m_Sprite.setPosition(Vector2f(newPos, 0.0f));
}

Sprite Background::getSprite()
{
	return m_Sprite;
}

float Background::getCurrentPosition()
{
	return m_PositionX;
}

void Background::update(float elapsedTime)
{
	m_PositionX -= (SCROLL_SPEED * elapsedTime);
	m_Sprite.setPosition(Vector2f(m_PositionX, 0.0f));

}