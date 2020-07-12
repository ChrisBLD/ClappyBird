#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureHolder.h"
#include "Clappy.h"
#include "Background.h"
#include "Pipe.h"

using namespace sf;

int main()
{
	TextureHolder holder;

	const float GRAVITY = 200.0f;

    //Get the screen resolution and create an SFML window
    Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

    RenderWindow window(VideoMode(resolution.x, resolution.y), "Clappy Bird", Style::Fullscreen);

    //Create an SFML view for the main action
    View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

    //And a clock for timing everything
    Clock clock;
    //How long has the PLAYING state been active?
    Time gameTimeTotal;

	//Load the font
	Font flappyFont;
	flappyFont.loadFromFile("fonts/FlappyBirdy.ttf");

	//Create two instances of the Background object to alternate and create scrolling effect
	Background primaryBG(true);
	Background secondaryBG(false);




	//Load in up and down textures for Clappy
	Texture textureClappyUp = TextureHolder::GetTexture("graphics/clappyUp.png");
	Texture textureClappyDown = TextureHolder::GetTexture("graphics/clappyDown.png");

	//Create an instance of Clappy
	Clappy clappy;

	//Create an instance of the Pipe
	Pipe pipe;
	float pipeHeight = pipe.getTextureHeight();
	pipe.setOffset(pipeHeight * (5.0f/23.0f));

	//Create a boolean to monitor whether the game is currently playing or paused
	bool playing = false;

	//Create a boolean to monitor whether the game is over or not
	bool gameOver = false;

	//Text to tell the player the game is currently paused
	Text gamePausedText;
	gamePausedText.setFont(flappyFont);
	gamePausedText.setCharacterSize(85);
	gamePausedText.setString("Game Paused");


    while (window.isOpen()) {

		/*
		****************************************
		Handle the players input
		****************************************
		*/

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Enter)
				{
					playing = !playing;
					if (gameOver)
					{
						clappy.restart();
						primaryBG.restart(true);
						secondaryBG.restart(false);
						playing = true;
						gameOver = false;

						gamePausedText.setString("Game Paused");
						FloatRect textRect = gamePausedText.getLocalBounds();
						//Centre text based on size
						gamePausedText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
						gamePausedText.setPosition(resolution.x / 2.0f, resolution.y / 2.0f);
						clock.restart();
					}
				}
				else if (event.key.code == Keyboard::Escape)
				{
					window.close();
				}
			}
		}

		

		/*
		****************************************
		Update the scene
		****************************************
		*/
		if (playing)
		{
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
				primaryBG.setNextPos(secondaryBG.getCurrentPosition() + (primaryBG.getTextureDimensions().x - 10.0f));
			}

			if (secondaryBG.getCurrentPosition() < -secondaryBG.getTextureDimensions().x)
			{
				secondaryBG.setNextPos(primaryBG.getCurrentPosition() + (secondaryBG.getTextureDimensions().x - 10.0f));
			}

			//Update the first pipe object
			if (pipe.isActive()) {
				pipe.update(dtAsSeconds);
			}
			else
			{
				pipe.spawn();
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

			//If Clappy is below the resolution
 			if (clappy.getPosition().y > resolution.y)
			{
				playing = !playing;
				gameOver = true;
				gamePausedText.setString("Game Over 0 Press Enter to restart");
				FloatRect textRect = gamePausedText.getLocalBounds();
				//Centre text based on size
				gamePausedText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				gamePausedText.setPosition(resolution.x / 2.0f, resolution.y / 2.0f);
			}
		}
		else
		{
			FloatRect textRect = gamePausedText.getLocalBounds();
			//Centre text based on size
			gamePausedText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
			gamePausedText.setPosition(resolution.x / 2.0f, resolution.y / 2.0f);
			//Need to restart the clock every frame since the clock time is used to move objects,
			//and if we don't then when the game is unpaused objects will skip to where they would've
			//been had we not paused at all.
			clock.restart();
		}

		/*
		****************************************
		Draw the scene
		****************************************
		*/

		// Clear everything from the last frame
		window.clear();

		// Draw the two backgrounds
        window.draw(primaryBG.getSprite());
		window.draw(secondaryBG.getSprite());

		//Draw the pipe
		window.draw(pipe.getSprite());

		//Draw Clappy
		window.draw(clappy.getSprite());

		//Draw game paused text if game is paused
		if (!playing)
		{
			window.draw(gamePausedText);
		}
		
		// Show everything we just drew
        window.display();
    }

    return 0;
}
