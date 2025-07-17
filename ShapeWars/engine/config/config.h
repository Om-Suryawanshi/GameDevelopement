#pragma once
#include <string>
#include <fstream>

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 1600
#define CONFIG "config.txt"

class Config
{
public:
	void readConfig(std::string& filename);
	void writeConfig(std::string& filename);
};
