#include "TextureHolder.h"
#include "Pipe.h"

Pipe::Pipe()
{

	m_Texture = TextureHolder::GetTexture("graphics/tree.png");

	m_Sprite.setTexture(m_Texture);

	m_isActive = false;

	sf::Vector2f targetSize(200.0f, 1150.0f);
	m_Sprite.setScale(
		targetSize.x / m_Sprite.getLocalBounds().width,
		targetSize.y / m_Sprite.getLocalBounds().height);
	
	//We want the pipe to be of random height such that the gap
	//falls on the screen


}

void Pipe::spawn()
{
	m_Position = STARTING_X;
	m_Sprite.setPosition(Vector2f(m_Position, 20.0f));
	m_isActive = true;
}

float Pipe::getTextureHeight()
{
	return m_Texture.getSize().y;
}

void Pipe::setOffset(float offset)
{
	m_PipeOffset = offset;
}

bool Pipe::isActive()
{
	return m_isActive;
}

Sprite Pipe::getSprite()
{
	return m_Sprite;
}

void Pipe::update(float elapsedTime)
{
	m_Position -= (SCROLL_SPEED * elapsedTime);
	m_Sprite.setPosition(Vector2f(m_Position, 0.0f));
}