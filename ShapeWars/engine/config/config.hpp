#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 1600
#define CONFIG "config.txt"
#define PI 3.14159f
#define FPS 240

struct WindowConfig {
	int width, height, frameLimit, fullscreen;
};

struct FontConfig {
	std::string path;
	int size;
	int r, g, b;
};

struct PlayerConfig {
	int shapeRadius, collisionRadius, outlineThickness, vertices;
	float speed;
	int fillR, fillG, fillB;
	int outlineR, outlineG, outlineB;
};

struct EnemyConfig {
	int shapeRadius, collisionRadius, outlineThickness;
	int minVertices, maxVertices;
	float minSpeed, maxSpeed;
	int outlineR, outlineG, outlineB;
	int lifespan;
	int spawnInterval;
};

struct BulletConfig {
	int shapeRadius, collisionRadius, outlineThickness, vertices, lifespan;
	float speed;
	int fillR, fillG, fillB;
	int outlineR, outlineG, outlineB;
};

struct GameConfig {
	WindowConfig window;
	FontConfig font;
	PlayerConfig player;
	EnemyConfig enemy;
	BulletConfig bullet;
};

class Config {
public:
	GameConfig game;
	bool readConfig(const std::string& filename) 
	{
		std::ifstream file(filename);
		if (!file.is_open()) {
			std::cerr << "Failed to open config file: " << filename << std::endl;
			return false;
		}

		std::string line;
		while (std::getline(file, line)) {
			std::istringstream iss(line);
			std::string type;
			iss >> type;

			if (type == "Window") {
				iss >> game.window.width >> game.window.height >> game.window.frameLimit >> game.window.fullscreen;
			}
			else if (type == "Font") {
				iss >> game.font.path >> game.font.size >> game.font.r >> game.font.g >> game.font.b;
			}
			else if (type == "Player") {
				iss >> game.player.shapeRadius >> game.player.collisionRadius >> game.player.speed
					>> game.player.fillR >> game.player.fillG >> game.player.fillB
					>> game.player.outlineR >> game.player.outlineG >> game.player.outlineB
					>> game.player.outlineThickness >> game.player.vertices;
			}
			else if (type == "Enemy") {
				iss >> game.enemy.shapeRadius >> game.enemy.collisionRadius
					>> game.enemy.minSpeed >> game.enemy.maxSpeed
					>> game.enemy.outlineR >> game.enemy.outlineG >> game.enemy.outlineB
					>> game.enemy.outlineThickness
					>> game.enemy.minVertices >> game.enemy.maxVertices
					>> game.enemy.lifespan >> game.enemy.spawnInterval;
			}
			else if (type == "Bullet") {
				iss >> game.bullet.shapeRadius >> game.bullet.collisionRadius >> game.bullet.speed
					>> game.bullet.fillR >> game.bullet.fillG >> game.bullet.fillB
					>> game.bullet.outlineR >> game.bullet.outlineG >> game.bullet.outlineB
					>> game.bullet.outlineThickness >> game.bullet.vertices >> game.bullet.lifespan;
			}
		}
		file.close();
		return true;
	}
};

extern Config g_Config;