#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Pipe
{
private:
	//Position of pipe in the x direction
	float m_Position;

	//Speed at which background will scroll
	const float SCROLL_SPEED = 175.0f;

	//Height of bottom level of pipe
	float m_Height;

	//Offset of pipes (gap between them)
	float m_PipeOffset;

	//Constant starting x location of pipes (they will all spawn at the same location)
	const float STARTING_X = VideoMode::getDesktopMode().width + 20.0f;

	//Texture of pipe
	Texture m_Texture;

	//Sprite of pipe
	Sprite m_Sprite;

	//Is pipe active?
	bool m_isActive;

public:
	Pipe();

	void spawn();

	void setOffset(float offset);

	float getTextureHeight();

	bool isActive();

	Sprite getSprite();

	void update(float elapsedTime);
};