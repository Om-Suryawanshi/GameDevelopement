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

	entManager.createEntity<Player>();

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

	ImGui::Begin("Entity Manager");

	if (ImGui::CollapsingHeader("Entities", ImGuiTreeNodeFlags_DefaultOpen))
	{
		auto& allEntities = entManager.getAllEnt();
		for (const auto& [id, ent] : allEntities)
		{
			ImGui::PushID(id); // Avoid ImGui ID collision

			ImGui::Text("ID: %d", id);

			// Show type
			std::string typeName = "Unknown";
			switch (ent->getType())
			{
			case EntityType::Player: typeName = "Player"; break;
			case EntityType::Enemy: typeName = "Enemy"; break;
			case EntityType::Bullet: typeName = "Bullet"; break;
			default: break;
			}
			ImGui::SameLine();
			ImGui::Text("Type: %s", typeName.c_str());
			ImGui::SameLine();
			ImGui::Text("(%f, %f)", ent->getPos().x, ent->getPos().y);

			// Delete Button
			ImGui::SameLine();
			if (ImGui::Button("D"))
			{
				entManager.markForRemoval(id);
			}

			ImGui::PopID();
		}
	}

	ImGui::End();

	g_window.clear();
	

	entManager.update();
	entManager.draw(g_window);


	ImGui::SFML::Render(g_window);

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
