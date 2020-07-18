# Clappy Bird - Simple C++ Flappy Bird Clone
Clappy Bird is the first game I built using C++ and SFML. I built this game after completing the C++ Game Programming 1 course on LinkedIn Learning, during which I developed two other games following a tutorial to learn the basic structure of a game and simple concepts such as taking user input, implementing simple game logic etc.

I decided to build a Flappy Bird clone as the game is relatively simple, but also presents some challenges for development that I had yet to encounter, for which I had to develop my own solution or research previous implementations.

For this project, I used two sections of code from other sources.

1. The TextureHolder.cpp and TextureHolder.h files define a singleton object which serves as a cache for textures in the game. Instead of needing to pull in textures from their files every single time they are used, the TextureHolder object ensures that textures are only ever imported once � if a texture is requested after being imported, it will simply be loaded from the cache. This code was used in the C++ Game Programming 1 course, and all credit for this approach is given to John Horton, the instructor for that course.
2. The simply physics implemented for Clappy (including the use of the m\_Acceleration and m\_Velocity variables) follows the [Code-It-Yourself! Flappy Bird (Quick and Simple C++)](https://www.youtube.com/watch?v=b6A4XHkTjs8) tutorial by javidx9. This version of the game was implemented using a console-based game engine, but the mechanism for applying the physics is the same. I used this code as my understanding of physics is quite poor and I wanted to implement something that felt smooth (as opposed to a static gravity value being applied).

The assets used are recycled from the C++ Game Programming 1 course mentioned earlier � these assets were for a different game, but I edited them to be more appropriate for this game. The rest of the code for this game is my own independent work.

Some of the key challenges of this game were:

1. Implementing an infinitely scrolling background. I researched this briefly but there didn&#39;t seem to be much information, and I was reluctant to follow Flappy Bird C++ tutorials any further. The way I implemented the scrolling background is to have two background objects scrolling in tandem such that the seam is indistinguishable. Once the first background object has scrolled off the screen, its position is set to move it to the right of the second object. Please refer to the diagram Fig 1 to see this in diagram form.
2. Implementing infinitely generating pipes. To do this, I created an array of five Pipe objects which will cycle into view when necessary. As the game starts, a counter is set to 0 and the first pipe of the array is spawned. Once that pipe reaches a certain location on the screen, the counter is incremented, and the next pipe is spawned. After a pipe has moved off screen, it is deactivated until the counter cycles back to it, at which point it is respawned. This is a very similar technique to the backgrounds, however maintaining an array of objects as opposed to just two objects.
3. Implementing random pipe height. When pipes are spawned, the position of the sprite is randomly generated as a value within a given range. This will move the &quot;gap&quot; on the pipe image to a different height each time. See the pipe image in the graphics folder to see how the object is built for this.
4. Collision detection for the pipes/Clappy. This aspect is important for both game over checks and incrementing the score. If a player has entered the pipe (i.e. if the rightmost point on Clappy has intersected with the leftmost point on the pipe), the game checks to see if the player is currently in the &quot;gap&quot; of the pipe, or colliding with the pipe itself by comparing Clappy&#39;s coordinates with the coordinates of the pipe gap&#39;s boundaries. As soon as Clappy&#39;s leftmost point enters the pipe, the score is incremented.

![](RackMultipart20200718-4-2smpm3_html_91f44086cbbce0ae.png)

See [https://youtu.be/y\_BaLGDbhZM](https://youtu.be/y_BaLGDbhZM) for a quick demonstration of the game, showing the game itself, score increments, pressing Enter to pause, losing the game by hitting a pipe, losing the game by falling out the map, and restarting the game by pressing Enter after losing.