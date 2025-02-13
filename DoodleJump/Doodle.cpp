#include "Doodle.h"
#include "Platform.h"

namespace DoodleJump
{
	Doodle::Doodle(const sf::Texture& texture, sf::Vector2f position): sprite(texture),
		position(position),
		height(200),
		dx(0),
		dy(-0.6f),
		fell(false)
	{
		sprite.setOrigin(sprite.getGlobalBounds().width / 2.f + 10, 0);

		if (!this->jumpSoundBuffer.loadFromFile("sounds/jump.wav")) {
			throw std::runtime_error("Error with open jump.wav");
		}
		jumpSound.setBuffer(jumpSoundBuffer);
	}

	void Doodle::update(float time)
	{
		if (isFell()) fell = true;

		if (!fell)
			control();

		if (dx > 0) sprite.setScale(-1, 1);
		if (dx < 0) sprite.setScale(1, 1);

		dy += 0.0006 * time;
		if (fell) dy = 0;
		position.x += dx * time;
		position.y += dy * time;
		dx = 0;

		if (position.x > 400) position.x = -sprite.getGlobalBounds().width;
		if (position.x < -sprite.getGlobalBounds().width) position.x = 400;

		sprite.setPosition(
			position.x + sprite.getGlobalBounds().width / 2 + 10,
			position.y);
	}
	void Doodle::control()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Mouse::isButtonPressed(sf::Mouse::Right)) dx = 0.2;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) dx = -0.2;
	}

	void Doodle::collision(const sf::FloatRect& rect)
	{
		if (
			(position.x + 50 > rect.left) &&
			(position.x + 20 < rect.left + 68) &&
			(position.y + 70 > rect.top) &&
			(position.y + 70 < rect.top + 14) &&
			(dy > 0))
		{
			dy = -0.6f;
			jumpSound.play();
		}
	}
	void Doodle::freeze()
	{
		position.y = height;
	}
	void Doodle::moveDown(float offset)
	{
		position.y += abs(offset);
		if (position.y > 533) position.y = 533;
	}
	void Doodle::reset()
	{
		fell = false;
		position = sf::Vector2f(200, 200);
		dy = -0.6;
	}
	float Doodle::getVerticalAcceleration() const
	{
		return dy;
	}
	bool Doodle::isJump() const
	{
		return position.y < height;
	}
	bool Doodle::isFell() const
	{
		return position.y + 70 > 533;
	}
	void Doodle::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite);
	}
}