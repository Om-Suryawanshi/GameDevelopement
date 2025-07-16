#include "GameManager.h"


GameManager::GameManager()
	:g_running(true)
{
	init();
}

void GameManager::init()
{
	g_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ShapeWars");
	ImGui::SFML::Init(g_window);

	g_window.setFramerateLimit(60);
	g_window.setVerticalSyncEnabled(true);


	g_ImguiStyle = ImGui::GetStyle();
}


void GameManager::update()
{
	ImGui::SFML::Update(g_window, g_deltaClock.restart());

	if (!isRunning()) { return; }
	if (g_window.isOpen())
	{
		while (g_window.pollEvent(g_event))
		{
			ImGui::SFML::ProcessEvent(g_event);

			if (g_event.type == sf::Event::Closed)
			{
				g_window.close();
			}
		}
	}


	ImGui::SFML::Render(g_window);
	g_window.clear();
	
	player.update();
	player.draw(g_window);

	g_window.display();
}

void GameManager::quit()
{
	g_running = false;
}

void GameManager::run()
{
	while (isRunning())
	{
		update();
	}
}

unsigned int GameManager::width() const
{
	return g_window.getSize().x;
}

unsigned int GameManager::height() const
{
	return g_window.getSize().y;
}

sf::RenderWindow& GameManager::getWindow()
{
	return g_window;
}

bool GameManager::isRunning()
{
	return g_running && g_window.isOpen();
}

void GameManager::readConfig(std::string& filename) 
{

}

void GameManager::writeConfig(std::string& filename)
{

}

