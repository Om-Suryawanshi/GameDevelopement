#include "Bullet.h"

Bullet::Bullet(int id, vec2& startPos, vec2& direction)
	:entity(id, 5.0f, 15.0f, 360.0f, startPos)
	,direction(direction)
{
	type = EntityType::Bullet;
	isAlive = true;
	lifetime = 3.0f;
	age = 0.0f;
	bullet.setRadius(size);
	bullet.setOrigin(size, size);
	bullet.setFillColor(sf::Color::White);

	float mag = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	velocity = (mag > 0) ? vec2(direction.x / mag, direction.y / mag) : vec2(0, 0);
	velocity *= speed;

	bullet.setPosition(pos.x, pos.y);
}

void Bullet::update()
{
	pos += velocity;
	age += 10.0f / FPS;

	if (age >= lifetime)
	{
		die();
	}

	sf::Uint8 alpha = static_cast<sf::Uint8>(255 * (1.0f - (age / lifetime)));
	sf::Color currentColor = bullet.getFillColor();
	currentColor.a = alpha; // 'a' is the alpha component
	bullet.setFillColor(currentColor);

	bullet.setPosition(pos.x, pos.y);
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