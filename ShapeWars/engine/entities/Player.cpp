#include "Player.h"


Player::Player(int id)
	: entity(id, static_cast<float>(g_Config.game.player.speed), static_cast<float>(g_Config.game.player.shapeRadius), static_cast<float>(g_Config.game.player.vertices))
	, player(static_cast<float>(g_Config.game.player.shapeRadius), static_cast<size_t>(g_Config.game.player.vertices)) // sf::CircleShape init
{
	type = EntityType::Player;
	isAlive = true;


	player.setOrigin(size, size);
	player.setFillColor(sf::Color(g_Config.game.player.fillR, g_Config.game.player.fillG, g_Config.game.player.fillB));
	player.setOutlineColor(sf::Color(g_Config.game.player.outlineR, g_Config.game.player.outlineG, g_Config.game.player.outlineB));
	player.setOutlineThickness(static_cast<float>(g_Config.game.player.outlineThickness));

	pos.x = static_cast<float>(g_Config.game.window.width) / 2;
	pos.y = static_cast<float>(g_Config.game.window.height) / 2;
	player.setPosition(pos.x, pos.y);
}

void Player::update()
{
	if (!paused)
	{
		if (justRespawned)
		{
			justRespawned = false;
			return;
		}
		// Movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) pos.y -= speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) pos.y += speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) pos.x -= speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) pos.x += speed;

		// Boundry Checking so the player dosent clip out
		if (pos.x < size) pos.x = size;
		if (pos.x > g_Config.game.window.width - size) pos.x = g_Config.game.window.width - size;
		if (pos.y < size) pos.y = size;
		if (pos.y > g_Config.game.window.height - size) pos.y = g_Config.game.window.height - size;

		player.setPosition(pos.x, pos.y);
	}
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(player);
}

vec2 Player::getPos() const
{
	return pos;
}

void Player::die()
{
	isAlive = false;
}
