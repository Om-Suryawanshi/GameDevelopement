#include "Enemy.h"


Enemy::Enemy(int id)
	:entity(id, 5.0f, 20.0f, 4.0f)
	, enemy(size, sides)
{
	type = EntityType::Enemy;
	isAlive = true;
	angle = static_cast<float>((rand() % 360) * PI / 180.0f); // degrees to radians
	velocity.x = std::cos(angle) * speed;
	velocity.y = std::sin(angle) * speed;

	enemy.setOrigin(size, size);
	enemy.setFillColor(sf::Color::Magenta);
	enemy.setOutlineColor(sf::Color::White);
	enemy.setOutlineThickness(3.0f);

	// random spawn logic
	float spawnX = size + static_cast<float>(rand() % static_cast<int>(WINDOW_WIDTH - 2 * size));
	float spawnY = size + static_cast<float>(rand() % static_cast<int>(WINDOW_HEIGHT - 2 * size));
	pos = vec2(spawnX, spawnY);
	enemy.setPosition(pos.x, pos.y);
}

void Enemy::update()
{
	// Enemy Movement Logic
	pos += velocity;
	if (pos.x < size || pos.x > WINDOW_WIDTH - size) velocity.x *= -1;
	if (pos.y < size || pos.y > WINDOW_HEIGHT - size) velocity.y *= -1;
	enemy.setPosition(pos.x, pos.y);
}

//bool Enemy::colide(vec2& playerPos)
//{
//	// Individual enemy collision check with player ent
//}

void Enemy::draw(sf::RenderWindow& window)
{
	window.draw(enemy);
}

void Enemy::die()
{
	isAlive = false;
}

vec2 Enemy::getPos() const
{
	return pos;
}