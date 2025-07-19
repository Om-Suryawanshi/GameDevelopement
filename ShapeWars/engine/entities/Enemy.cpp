#include "Enemy.h"


Enemy::Enemy(int id, float speed, float size, float sides, EntityType enemyType)
	: entity(id,speed,size,sides)
	, enemy(size, static_cast<float>(sides))	
{
	isAlive = true;
	type = enemyType;
	age = 0;
	angle = static_cast<float>((rand() % 360) * PI / 180.0f); // degrees to radians

	velocity.x = std::cos(angle) * speed;
	velocity.y = std::sin(angle) * speed;

	lifetime = static_cast<float>(g_Config.game.enemy.lifespan);

	enemy.setOrigin(size, size);
	enemy.setFillColor(sf::Color::Transparent);
	enemy.setOutlineColor(sf::Color(
		g_Config.game.enemy.outlineR,
		g_Config.game.enemy.outlineG,
		g_Config.game.enemy.outlineB
	)); 
	enemy.setOutlineThickness(static_cast<float>(g_Config.game.enemy.outlineThickness));

	// random spawn logic
	if (type == EntityType::Enemy)
	{
		float spawnX = size + static_cast<float>(rand() % static_cast<int>(g_Config.game.window.width - 2 * size));
		float spawnY = size + static_cast<float>(rand() % static_cast<int>(g_Config.game.window.height - 2 * size));
		pos = vec2(spawnX, spawnY);
	}	
	enemy.setPosition(pos.x, pos.y);
}

void Enemy::update()
{
	if (!paused)
	{
		//Age
		age += 10.0f / g_Config.game.window.frameLimit;
		if (age >= lifetime)
		{
			die();
		}
		float progress = age / lifetime;
		progress = std::clamp(progress, 0.0f, 1.0f); // Ensure it's within bounds

		sf::Uint8 alpha = static_cast<sf::Uint8>(255 * (1.0f - progress));

		// Clamp to a minimum visible value (e.g., 80)
		alpha = std::max(alpha, static_cast<sf::Uint8>(80));

		sf::Color currentOutlineColor = enemy.getOutlineColor();
		currentOutlineColor.a = alpha;
		enemy.setOutlineColor(currentOutlineColor);


		// Enemy Movement Logic
		pos += velocity;
		if (pos.x < size || pos.x > g_Config.game.window.width - size) velocity.x *= -1;
		if (pos.y < size || pos.y > g_Config.game.window.height - size) velocity.y *= -1;
		enemy.setPosition(pos.x, pos.y);
	}

	rotate();
}

void Enemy::rotate()
{
	enemy.rotate(2.0f);
}

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

