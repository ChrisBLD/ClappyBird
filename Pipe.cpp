#include "TextureHolder.h"
#include "Pipe.h"

Pipe::Pipe()
{

	m_Texture = TextureHolder::GetTexture("graphics/tree.png");

	m_Sprite.setTexture(m_Texture);

	m_isActive = false;

	m_Width = m_Texture.getSize().x;

	m_scoreCounted = false;

	//sf::Vector2f targetSize(200.0f, 1150.0f);
	//m_Sprite.setScale(
	//	targetSize.x / m_Sprite.getLocalBounds().width,
	//	targetSize.y / m_Sprite.getLocalBounds().height);
	

}

void Pipe::spawn()
{
	m_Position.x = STARTING_X;
	//We want the pipe to be of random height such that the gap
	//falls on the screen
	//The highest the gap can be would have the object's location be y = -827
	// 
	//The lowest the gap can be would have the object's location be y = -92
	//So we need a random number between -815 and -104

	m_Position.y = (rand() % 711) - 815;
	m_Sprite.setPosition(m_Position);
	m_isActive = true;
}

bool Pipe::isActive()
{
	return m_isActive;
}

Sprite Pipe::getSprite()
{
	return m_Sprite;
}

Vector2f Pipe::getPosition()
{
	return m_Position;
}

float Pipe::getWidth()
{
	return m_Width;
}

void Pipe::deactivate()
{
	m_isActive = false;
	m_scoreCounted = false;
}

bool Pipe::scoreCounted()
{
	return m_scoreCounted;
}

void Pipe::counted()
{
	m_scoreCounted = true;
}

bool Pipe::hitByPlayer(FloatRect playerPosition)
{	
	if (playerPosition.intersects(m_Sprite.getGlobalBounds()))
	{
		//When the player intersects the tree, we need to make sure that the player
		//is in the gap.
		float topLeftY = playerPosition.top + 20.0f;
		float bottomRightY = playerPosition.top + playerPosition.width - 20.0f;

		float yRangeMin = m_Position.y + PIPE_LENGTH;
		float yRangeMax = m_Position.y + PIPE_LENGTH + PIPE_OFFSET;

		if (topLeftY > yRangeMin && bottomRightY < yRangeMax)
		{
			return false;
		}
		else
		{
			return true; 
		}
	}
	return false;

}

void Pipe::update(float elapsedTime)
{
	m_Position.x -= (SCROLL_SPEED * elapsedTime);
	m_Sprite.setPosition(m_Position);
}

void Pipe::restart()
{
	m_isActive = false;
	m_Position.x = 0.0f;
	m_Sprite.setPosition(m_Position);
	m_scoreCounted = false;
}