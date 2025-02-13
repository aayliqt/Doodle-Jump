#include "Game.h"

namespace DoodleJump
{
	Game::Game(
		sf::Texture& background_t,
		sf::Texture& platform_t,
		sf::Texture& doodle_t,
		sf::Font& font
	)
		: doodle(doodle_t, sf::Vector2f(200, 200)),
		platforms(10, Platform(platform_t)),
		gameover_text("Game Over", font, 90),
		score_text("0", font, 70),
		left_control_text("A - Move left", font, 40),
		right_control_text("D - Move right", font, 40),
		restart_text("Press R to restart...", font, 40),
		bestscore_text("Best score: ", font, 55),
		gameOver(false),
		gameOverTimer(0),
		bestScore(0),
		hasPlayedFallSound(false)
	{
		background_s.setTexture(background_t);
		gameover_text.setFillColor(sf::Color::White);
		gameover_text.move(20, 120);
		score_text.setFillColor(sf::Color::White);
		score_text.setStyle(sf::Text::Style::Bold);
		score_text.setPosition(10, 0);
		restart_text.setFillColor(sf::Color::White);
		restart_text.setPosition(60, 480);
		bestscore_text.setFillColor(sf::Color::White);
		left_control_text.setFillColor(sf::Color::White);
		left_control_text.setPosition(210, 0);
		right_control_text.setFillColor(sf::Color::White);
		right_control_text.setPosition(190, 35);

		for (auto& platform : platforms)
			platform.random();
		if (!this->startSoundBuffer.loadFromFile("sounds/start.wav")) {
			throw std::runtime_error("Error with open start.wav");
		}
		startSound.setBuffer(startSoundBuffer);
		startSound.play();
		if (!this->fallSoundBuffer.loadFromFile("sounds/fall.wav")) {
			throw std::runtime_error("Error with open fall.wav");
		}
		fallSound.setBuffer(fallSoundBuffer);
	}

	void Game::update()
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 500;
		doodle.update(time);
		for (auto& platform : platforms)
		{
			platform.update(time);
			doodle.collision(platform.getBoxCollider());
		}
		if (doodle.isJump())
		{
			score += abs(doodle.getVerticalAcceleration()) / 30.f;

			doodle.freeze();
			for (auto& platform : platforms)
				platform.moveDown(doodle.getVerticalAcceleration() * time);
		}
		if (doodle.isFell()) {
			gameOver = true;
			if (!hasPlayedFallSound) {
				fallSound.play();
				hasPlayedFallSound = true;
			}
		}
		if (gameOver)
		{
			for (auto& platform : platforms)
				platform.moveUp(0.6 * time);

			gameOverTimer += time;

			if (!(gameOverTimer > 1000))
				score_text.move(0, -0.6 * time);
			if (score > bestScore)
			{
				bestScore = score;
				setBestScore(bestScore);
			}
		}
		else
		{
			score_text.setString(std::to_string((int)score) + " m");
		}
		if (gameOverTimer > 1000 && gameOver)
		{
			score_text.setString("Score: " + std::to_string((int)score));
			score_text.setPosition(60, 230);

			doodle.moveDown(0.2 * time);
		}
	}
	void Game::render(sf::RenderWindow& window)
	{
		window.draw(background_s);
		window.draw(doodle);
		for (const auto& platform : platforms)
			window.draw(platform);

		window.draw(score_text);

		if (!gameOver)
		{
			window.draw(left_control_text);
			window.draw(right_control_text);
		}

		if (gameOver)
		{
			window.draw(gameover_text);

			if (gameOverTimer > 1000)
			{
				window.draw(restart_text);
				window.draw(bestscore_text); 
			}
		}
	}
	void Game::reset()
	{
		gameOver = false;
		score = 0.f;
		gameOverTimer = 0.f;
		hasPlayedFallSound = false;
		doodle.reset();
		score_text.setPosition(10, 0);

		for (auto& platform : platforms)
			platform.random();

		startSound.play();
	}
	bool Game::isGameOver() const
	{
		return gameOverTimer > 1000 && gameOver;
	}
	void Game::setBestScore(float score)
	{
		bestScore = score;
		bestscore_text.setString("Best score: " + std::to_string((int)bestScore));
		bestscore_text.setPosition(40, 310);
	}
	float Game::getBestScore() const
	{
		return bestScore;
	}
}