#include "Player.h"


Player::Player(int id)
	: entity(id, 5.0f, 20.0f, 8)
	, player(size, sides)
{
	type = EntityType::Player;
	isAlive = true;


	player.setOrigin(size, size);
	player.setFillColor(sf::Color::Green);
	player.setOutlineColor(sf::Color::Blue);
	player.setOutlineThickness(3.0f);

	pos.x = WINDOW_WIDTH / 2;
	pos.y = WINDOW_HEIGHT / 2;
	player.setPosition(pos.x, pos.y);
}

void Player::update()
{
	// Movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) pos.y -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) pos.y += speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) pos.x -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) pos.x += speed;

	// Boundry Checking so the player dosent clip out
	if (pos.x < size) pos.x = size;
	if (pos.x > WINDOW_WIDTH - size) pos.x = WINDOW_WIDTH - size;
	if (pos.y < size) pos.y = size;
	if (pos.y > WINDOW_HEIGHT - size) pos.y = WINDOW_HEIGHT - size;

	player.setPosition(pos.x, pos.y);
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(player);
}

vec2 Player::getPos() const
{
	return pos;
}

