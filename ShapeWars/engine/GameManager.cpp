#include "GameManager.h"

Config g_Config;

GameManager::GameManager()
	:g_running(true)
	,rewindSystem(entManager, 300) // Save 300 frames
{
	if (g_Config.readConfig("CONFIG.txt"))
	{
		init();
	}
}

void GameManager::init()
{
	g_window.create(sf::VideoMode(g_Config.game.window.width, g_Config.game.window.height), "ShapeWars");
	ImGui::SFML::Init(g_window);

	g_window.setFramerateLimit(g_Config.game.window.frameLimit);
	g_window.setVerticalSyncEnabled(true);
	// Full Screen Implementation

	entManager.createEntity<Player>();

	// Enemy Spawner

	randomSpeed = static_cast<float> (g_Config.game.enemy.minSpeed) + static_cast<float>(rand()) / RAND_MAX * (static_cast<float> (g_Config.game.enemy.maxSpeed) - static_cast<float> (g_Config.game.enemy.minSpeed));
	randomSides = static_cast<float> (g_Config.game.enemy.minVertices) + (rand() % (static_cast<int>(g_Config.game.enemy.maxVertices) - static_cast<int>(g_Config.game.enemy.minVertices + 1)));

	enemySpawnIntervalMs = g_Config.game.enemy.spawnInterval * (1000 / g_Config.game.window.frameLimit);


	g_ImguiStyle = ImGui::GetStyle();

	if (!m_font.loadFromFile(g_Config.game.font.path))
	{
		std::cerr << "Failed to load font!" << std::endl;
	}

	// Set up score text
	m_scoreText.setFont(m_font);
	m_scoreText.setCharacterSize(g_Config.game.font.size); // from config maybe
	m_scoreText.setFillColor(sf::Color(
		g_Config.game.font.r,
		g_Config.game.font.g,
		g_Config.game.font.b
	));

	m_scoreText.setPosition(10.f, 10.f); // top-left corner
	m_scoreText.setString("Score: 0");
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
				quit();
				g_window.close();
			}
			

			//Bullet fire logic
			if (g_event.type == sf::Event::MouseButtonPressed &&
				g_event.mouseButton.button == sf::Mouse::Left && !m_isPaused && !rewindSystem.isRewinding())
			{
				sf::Vector2i mousePixel = sf::Mouse::getPosition(g_window);
				sf::Vector2f mouseWorld = g_window.mapPixelToCoords(mousePixel);
				vec2 mousePos(mouseWorld.x, mouseWorld.y);

				std::shared_ptr<entity> playerEnt = entManager.getPlayer();
				if (playerEnt && playerEnt->getType() == EntityType::Player)
				{
					vec2 playerPos = playerEnt->getPos();
					vec2 direction = mousePos - playerPos;
					entManager.createEntity<Bullet>(playerPos, direction);
				}
			}

			// Pause with P
			if (g_event.type == sf::Event::KeyPressed && g_event.key.code == sf::Keyboard::P)
			{
				m_isPaused = !m_isPaused;
				entManager.pauseEnt();
			}

			// Quit Game with esc
			if (g_event.type == sf::Event::KeyPressed && g_event.key.code == sf::Keyboard::Escape)
			{
				g_window.close();
			}

			if (g_event.type == sf::Event::KeyPressed && g_event.key.code ==  sf::Keyboard::R)
			{
				std::cerr << "Rewind triggered" << std::endl;
				rewindSystem.triggerRewind();
			}
		}
	}


	// Enemy Spawn Logic
	const int maxEnemies = 10;
	const float safeDistanceFromPlayer = 150.f; // Minimum distance from player to enemy

	if (enemySpawnClock.getElapsedTime().asMilliseconds() >= enemySpawnIntervalMs && !m_isPaused && !rewindSystem.isRewinding())
	{
		currentEnemies = entManager.countByType(EntityType::Enemy);
		if (currentEnemies < maxEnemies)
		{
			const auto& player = entManager.getPlayer();
			if (!player) return; // Make sure player exists

			const vec2& playerPos = player->getPos();
			const float enemyRadius = static_cast<float>(g_Config.game.enemy.shapeRadius);
			const float bufferZone = safeDistanceFromPlayer + enemyRadius;

			vec2 spawnPos;
			int maxAttempts = 100; // Avoid infinite loops
			bool validPositionFound = false;

			for (int i = 0; i < maxAttempts; ++i)
			{
				// Generate random spawn position within window
				spawnPos = {
					static_cast<float>(rand() % (g_Config.game.window.width - static_cast<int>(enemyRadius * 2)) + enemyRadius),
					static_cast<float>(rand() % (g_Config.game.window.height - static_cast<int>(enemyRadius * 2)) + enemyRadius)
				};

				float dx = spawnPos.x - playerPos.x;
				float dy = spawnPos.y - playerPos.y;
				float distanceSquared = dx * dx + dy * dy;

				if (distanceSquared >= bufferZone * bufferZone)
				{
					validPositionFound = true;
					break;
				}
			}

			if (validPositionFound)
			{
				float randomSpeed = g_Config.game.enemy.minSpeed +
					static_cast<float>(rand()) / RAND_MAX *
					(g_Config.game.enemy.maxSpeed - g_Config.game.enemy.minSpeed);

				int randomSides = g_Config.game.enemy.minVertices +
					(rand() % (g_Config.game.enemy.maxVertices - g_Config.game.enemy.minVertices + 1));

				auto newEnemy = entManager.createEntity<Enemy>(randomSpeed, enemyRadius, static_cast<float>(randomSides), EntityType::Enemy);
				newEnemy->setPos(spawnPos);
			}
		}
		enemySpawnClock.restart();
	}


	//Collision Code between player and enemy
	/*if (!m_isPaused && !rewindSystem.isRewinding())
	{
		std::cerr << "Rewind" << std::endl;
	}*/

	std::shared_ptr<entity> player = entManager.getPlayer();
	for (auto& enemy : entManager.getByType(EntityType::Enemy))
	{
		if (!enemy->getisAlive()) continue;
		if (collision.checkCollision(*player, *enemy))
		{
			player->die();
			if (!entManager.playerExists())
			{
				entManager.createEntity<Player>();
			}
			m_score -= enemy->getVertices() * 100;
			enemy->die();
		}

		for (auto& minienemy : entManager.getByType(EntityType::MiniEnemy))
		{
			if (!minienemy) continue;
			if (collision.checkCollision(*player, *minienemy))
			{
				// Prevents duplication of player if which happened in old logic 
				/* Old logic created multiple players if player died again before the update is executed again
				player->die();
				entManager.createEntity<Player>();
				m_score -= 500;
				enemy->die(); */
				player->die();
				if (!entManager.playerExists())
				{
					entManager.createEntity<Player>();
				}
				m_score -= enemy->getVertices() * 100;
				minienemy->die();
			}
		}
	}

	// Collision logic between bullet and enemy
	for (auto& bullet : entManager.getByType(EntityType::Bullet))
	{
		if (!bullet->getisAlive()) continue;
		for (auto& enemy : entManager.getByType(EntityType::Enemy))
		{
			if (!enemy->getisAlive()) continue;
			if (collision.checkCollision(*bullet, *enemy))
			{
				bullet->die();
				m_score += enemy->getVertices() * 100;

				//Enemy Split and scatter
				float angleIncrement = 2.0f * PI / enemy->getVertices();
				// Mini enemy spawnner
				for (int i = 0; i < static_cast<int>(enemy->getVertices()); ++i)
				{
					float angle = i * angleIncrement;
					vec2 dir(std::cos(angle), std::sin(angle));

					// Spawn the mini enemy
					std::shared_ptr<entity> minienemy_base = entManager.createEntity<Enemy>(
						enemy->getSpeed(),
						enemy->getSize() / 2,
						enemy->getVertices(),
						EntityType::MiniEnemy
					);

					std::shared_ptr<Enemy> minienemy = std::dynamic_pointer_cast<Enemy>(minienemy_base);

					minienemy->setPos(enemy->getPos());

					minienemy->setVelocity(dir * (enemy->getSpeed() / 10.0f));

					minienemy->setLifetime(10);
				}
				enemy->die();
				break;
			}
		}

		//Minienemy and bullet
		for (auto& minienemy : entManager.getByType(EntityType::MiniEnemy))
		{
			if (!minienemy->getisAlive()) continue;
			if (collision.checkCollision(*bullet, *minienemy))
			{
				m_score += minienemy->getVertices() * 300;
				bullet->die();
				minienemy->die();
				break;
			}
		}
	}

	ImGui::Begin("Entity Manager");

	if (ImGui::CollapsingHeader("Entities", ImGuiTreeNodeFlags_DefaultOpen))
	{
		auto& allEntities = entManager.getAllEnt();
		for (const auto& [id, ent] : allEntities)
		{
			ImGui::PushID(id);

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
				ent->die();
			}

			ImGui::PopID();
		}
	}

	ImGui::End();

	g_window.clear();
	
	updateScoreText();

	entManager.update();
	entManager.draw(g_window);

	//ImGui::SFML::Render(g_window);
	rewindSystem.update();
	g_window.draw(m_scoreText);
	g_window.display();
}

void GameManager::updateScoreText()
{
	m_scoreText.setString("Score: " + std::to_string(m_score));
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
