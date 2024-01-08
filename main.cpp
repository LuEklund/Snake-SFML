

#include "Game.h"


int main()
{
    sf::RenderWindow	window(sf::VideoMode(600, 608), "test");
    sf::Event event;

	// window.setFramerateLimit(1);



	Game	game(window);
	if (!game.initGame())
		return (-1);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
			else if(event.type == sf::Event::KeyPressed)
				game.isKeyPressed(event.key.code);
			else if (event.type == sf::Event::MouseButtonReleased)
				game.isMouseButtonReleased(event.mouseButton.button);
        }
		game.update();

		window.clear();
		game.drawMap(window);
		window.draw(game);
		window.display();
    }
}

