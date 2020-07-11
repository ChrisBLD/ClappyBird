#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Background
{
private:
	//Speed at which background will scroll
	const float SCROLL_SPEED = 175.0f;

	//Current x position of background
	float m_PositionX;

	//Is background primary or secondary?
	bool m_IsPrimary;

	//Holds texture of background
	Texture m_Texture;

	//Holds sprite of background
	Sprite m_Sprite;

public:
	Background(bool whichBG);

	void setNextPos(float newPos);

	Sprite getSprite();

	float getCurrentPosition();

	void update(float elapsedTime);
};