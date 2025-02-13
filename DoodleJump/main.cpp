#include<SFML/Graphics.hpp>
#include<ctime>
#include<iostream>
#include"Game.h"

using namespace DoodleJump;

int main()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(400, 530), "Doodle Jump", sf::Style::Close);
	window.setMouseCursorVisible(false);

	sf::Texture backgroud, platform, doodle;
	sf::Font font;
	
	backgroud.loadFromFile("images/background_soccer.png");
	platform.loadFromFile("images/platform_white.png");
	doodle.loadFromFile("images/doodle_ukr.png");
	font.loadFromFile("fonts/doodleJump.ttf");

	Game game(backgroud, platform, doodle, font);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R || event.type == sf::Event::MouseButtonPressed)
				if (game.isGameOver())
				{
					game.reset();
				}
		}
		game.update();
		window.clear();
		game.render(window);
		window.display();
	}
	return 0;
}