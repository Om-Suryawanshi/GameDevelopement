#pragma once
#include "imgui.h"
#include "imgui-SFML.h"

#include "SFML/Graphics.hpp"

#include <string>
#include <iostream>

//#include "Player.h"
#include "config/config.hpp"
#include "EntityManager.h"
#include "RewindSystem.h"
#include "entities/player.h"
#include "entities/Enemy.h"

class GameManager
{
protected:
	sf::RenderWindow g_window;
	sf::Clock g_deltaClock;
	ImGuiStyle g_ImguiStyle;
	bool g_running;
	sf::Event g_event;
	float randomSpeed;
	float randomSides;
	sf::Clock enemySpawnClock;
	int enemySpawnIntervalMs;
	int currentEnemies;
	int maxEnemies;
	bool m_isPaused = false;
	Collision collision;
	EntityManager entManager;
	RewindSystem rewindSystem;

	// Score
	int m_score = 0;
	int m_highScore = 0;
	int m_respawnPenalty = 500;
	sf::Text m_scoreText;
	sf::Font m_font;

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
	void updateScoreText();
};