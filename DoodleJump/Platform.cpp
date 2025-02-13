#include "Platform.h"
#include<cstdlib>

namespace DoodleJump
{
	Platform::Platform(const sf::Texture & texture)
	:	sprite(texture)
	{
	}
	void Platform::update(float time)
	{
		if (position.y > 533) spawn();

		sprite.setPosition(position);
	}
	void Platform::moveDown(float offset)
	{
		position.y += abs(offset);
	}
	void Platform::moveUp(float offset)
	{
		position.y -= abs(offset);
		if (position.y < -15) position.y = -15;
	}
	void Platform::spawn()
	{
		position.x = float(rand() % 400 - 34);
		position.y = 0;
	}
	void Platform::random()
	{
		position.x = float(rand() % 400 - 34);
		position.y = float(rand() % 533);
	}
	sf::FloatRect Platform::getBoxCollider() const
	{
		return sprite.getGlobalBounds();
	}
	void Platform::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(sprite);
	}
}