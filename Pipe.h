#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Pipe
{
private:
	//Position of pipe
	Vector2f m_Position;

	//Speed at which background will scroll
	const float SCROLL_SPEED = 175.0f;

	//Height of bottom level of pipe
	float m_Height;

	//Constant offset of pipes (gap between them)
	const float PIPE_OFFSET = 347.0f;

	//Constant starting x location of pipes (they will all spawn at the same location)
	const float STARTING_X = VideoMode::getDesktopMode().width + 20.0f;

	//Texture of pipe
	Texture m_Texture;

	//Sprite of pipe
	Sprite m_Sprite;

	//Is pipe active?
	bool m_isActive;

	//Pipe width
	float m_Width;

public:
	Pipe();

	void spawn();

	bool isActive();

	Sprite getSprite();

	Vector2f getPosition();

	float getWidth();

	void deactivate();

	bool hitByPlayer();

	void update(float elapsedTime);
};