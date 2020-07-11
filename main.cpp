#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureHolder.h"
#include "Clappy.h"
#include "Background.h"

using namespace sf;

int main()
{
	TextureHolder holder;

	const float GRAVITY = 200.0f;

    //Get the screen resolution and create an SFML window
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena", Style::Fullscreen);

    //Create an SFML view for the main action
    View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

    //And a clock for timing everything
    Clock clock;
    //How long has the PLAYING state been active?
    Time gameTimeTotal;

	//Load the texture for our background

	//Create two instances of the Background object to alternate and create scrolling effect
	Background primaryBG(true);
	Background secondaryBG(false);


	//Texture textureBackground = TextureHolder::GetTexture("graphics/backgroundDouble.png");
	//Sprite background;
	//background.setTexture(textureBackground);

	//Load in up and down textures for Clappy
	Texture textureClappyUp = TextureHolder::GetTexture("graphics/clappyUp.png");
	Texture textureClappyDown = TextureHolder::GetTexture("graphics/clappyDown.png");

	//Create an instance of Clappy
	Clappy clappy;

    while (window.isOpen()) {

		/*
		****************************************
		Handle the players input
		****************************************
		*/

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		/*
		****************************************
		Update the scene
		****************************************
		*/

		//Update the delta time
		Time dt = clock.restart();
		//Update the total game time
		gameTimeTotal += dt;
		//Make a decimal fraction of 1 from the delta time
		float dtAsSeconds = dt.asSeconds();

		//Update the backgrounds to move them at the required speed
		primaryBG.update(dtAsSeconds);
		secondaryBG.update(dtAsSeconds);

		//These statements control whether the backgrounds have passed all the way through and are no longer
		//visible to the user. If they are, they are appended to the end of the current background. This
		//means that each time a background disappears from view on the left, it is sent to the far right,
		//creating an infinitely scrolling background.

		if (primaryBG.getCurrentPosition() < -primaryBG.getTextureDimensions().x)
		{
			primaryBG.setNextPos(secondaryBG.getCurrentPosition() + (primaryBG.getTextureDimensions().x -10.0f));
		}

		if (secondaryBG.getCurrentPosition() < -secondaryBG.getTextureDimensions().x)
		{
			secondaryBG.setNextPos(primaryBG.getCurrentPosition() + (secondaryBG.getTextureDimensions().x - 10.0f));
		}


		//If the space key has just been pressed, clappy needs to go up (if he can)
		//Otherwise, he needs to go down
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			if (clappy.getVelocity() > 0) //If clappy is rising, he can't jump again!
			{
				clappy.update(dtAsSeconds, true);
			} 
			else
			{
				clappy.update(dtAsSeconds, false);
			}
		} 
		else 
		{
			clappy.update(dtAsSeconds, false);
		}

		/*
		****************************************
		Draw the scene
		****************************************
		*/

		// Clear everything from the last frame
		window.clear();

		// Draw our game scene here
        window.draw(primaryBG.getSprite());
		window.draw(secondaryBG.getSprite());

		//Draw Clappy
		window.draw(clappy.getSprite());

		// Show everything we just drew
        window.display();
    }

    return 0;
}