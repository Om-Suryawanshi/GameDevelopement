#pragma once
#include <string>
#include <fstream>

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 1600
#define CONFIG "config.txt"
#define PI 3.14159f
#define FPS 240

class Config
{
public:
	void readConfig(std::string& filename);
	void writeConfig(std::string& filename);
};
