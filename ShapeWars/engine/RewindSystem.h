#pragma once
#include "../engine/EntityManager.h"
#include "../engine/entities/entity.h"
#include "../engine/entities/Player.h"
#include "../engine/entities/Enemy.h"
#include "../engine/entities/Bullet.h"

#include "../engine/config/config.hpp"
#include <deque>


struct SnapshotEntityData {
	EntityType type;
	vec2 pos;
	vec2 velocity;
	float radius = 0.f;
	int vertices = 0;
	float lifetime = 0.f;
	float age = 0.f;
	bool isAlive = true;
};

using FrameSnapshot = std::vector<SnapshotEntityData>;


class RewindSystem
{
public:
	RewindSystem(EntityManager& entManager, int maxFrames);

	void update();
	void triggerRewind();
	void loadSnapShot(const FrameSnapshot& snapshot);
	bool isRewinding() const;
	void clearHistory();
	void pauseCapture();

private:
	EntityManager& entManager;
	std::deque<FrameSnapshot> history;
	const int maxFrameCount;
	int rewindIndex = 0;
	bool m_rewinding = false;
	int isPaused = false;
};

