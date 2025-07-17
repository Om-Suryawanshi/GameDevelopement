#pragma once
#include "imgui.h"
#include "imgui-SFML.h"

#include "SFML/Graphics.hpp"

#include <string>
#include <iostream>

//#include "Player.h"
#include "config/config.h"
#include "EntityManager.h"
#include "entities/player.h"

class GameManager
{
protected:
	sf::RenderWindow g_window;
	sf::Clock g_deltaClock;
	ImGuiStyle g_ImguiStyle;
	bool g_running;
	sf::Event g_event;

	EntityManager entManager;

	void update(); // Main Game method called every frame


public:
	GameManager();
	void init();
	void quit();
	void run();

	unsigned int width() const;
	unsigned int height() const;
	sf::RenderWindow& getWindow();
	bool isRunning();
};