#include "Player.h"


Player::Player()
	:speed(5.0f)
	,radius(20.0f)
	,sides(360)
	,player(radius, sides)
{
	player.setOrigin(radius, radius);
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
	if (pos.x < radius) pos.x = radius;
	if (pos.x > WINDOW_WIDTH - radius) pos.x = WINDOW_WIDTH - radius;
	if (pos.y < radius) pos.y = radius;
	if (pos.y > WINDOW_HEIGHT - radius) pos.y = WINDOW_HEIGHT - radius;

	player.setPosition(pos.x, pos.y);
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(player);
}