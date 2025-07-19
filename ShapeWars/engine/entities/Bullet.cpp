#include "Bullet.h"

Bullet::Bullet(int id, vec2 startPos, vec2 direction)
	:entity(id, static_cast<float>(g_Config.game.bullet.speed), static_cast<float>(g_Config.game.bullet.shapeRadius), static_cast<float>(g_Config.game.bullet.vertices), startPos)
	,direction(direction)
{
	type = EntityType::Bullet;
	isAlive = true;
	lifetime = static_cast<float>(g_Config.game.bullet.lifespan);
	age = 0;
	bullet.setRadius(size);
	bullet.setOrigin(size, size);
	bullet.setFillColor(sf::Color(g_Config.game.bullet.fillR, g_Config.game.bullet.fillG, g_Config.game.bullet.fillB));
	bullet.setOutlineColor(sf::Color(g_Config.game.bullet.outlineR, g_Config.game.bullet.outlineG, g_Config.game.bullet.outlineB));
	bullet.setOutlineThickness(static_cast<float>(g_Config.game.bullet.outlineThickness));


	float mag = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	velocity = (mag > 0) ? vec2(direction.x / mag, direction.y / mag) : vec2(0, 0);
	velocity *= speed;

	bullet.setPosition(pos.x, pos.y);
}

void Bullet::update()
{
	if (!paused)
	{
		pos += velocity;
		age += 50.0f / g_Config.game.window.frameLimit; // Randomly Trial and error value 50.0f for ageing lower it to decrease ageing

		if (age >= lifetime)
		{
			die();
		}

		sf::Uint8 alpha = static_cast<sf::Uint8>(255 * (1.0f - (age / lifetime)));
		sf::Color currentColor = bullet.getFillColor();
		sf::Color currentOutlineColor = bullet.getOutlineColor();
		currentColor.a = alpha; // 'a' is the alpha component
		currentOutlineColor.a = alpha;
		bullet.setFillColor(currentColor);
		bullet.setOutlineColor(currentOutlineColor);
		bullet.setPosition(pos.x, pos.y);
	}
}

void Bullet::draw(sf::RenderWindow& window)
{
	window.draw(bullet);
}

vec2 Bullet::getPos() const
{
	return pos;
}

void Bullet::die()
{
	isAlive = false;
}