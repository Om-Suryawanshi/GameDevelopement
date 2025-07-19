#include "RewindSystem.h"
#include <SFML/System.hpp>
#include <iostream>

RewindSystem::RewindSystem(EntityManager& manager, int maxFrames)
    : entManager(manager), maxFrameCount(maxFrames), m_rewinding(false), rewindIndex(0) {
}

void RewindSystem::update() {
    // Log number of entities currently in the game world
    const auto& entities = entManager.getAllEnt();
    //std::cerr << "[RewindSystem] Entities in snapshot: " << entities.size() << "\n";

    if (m_rewinding) {
        //std::cerr << "[RewindSystem] Rewinding... index: " << rewindIndex << "\n";

        if (rewindIndex >= 0 && rewindIndex < static_cast<int>(history.size())) {
            loadSnapShot(history[rewindIndex--]);
            sf::sleep(sf::milliseconds(10)); // Visual slow-mo effect
        }
        else {
            std::cerr << "[RewindSystem] Rewind complete.\n";
            m_rewinding = false;
            history.clear();
        }
        return;
    }

    // Take a snapshot of current state
    FrameSnapshot snapshot;
    for (const auto& [id, ent] : entities) {
        snapshot.push_back(SnapshotEntityData{
            ent->getType(),
            ent->getPos(),
            ent->getVelocity(),
            ent->getSize(),
            ent->getVertices(),
            ent->getLifetime(),
            ent->getAge(),
            ent->getisAlive()
            });
    }

    // Only store meaningful (non-empty) snapshots
    if (!snapshot.empty()) {
        history.push_back(snapshot);
        //std::cerr << "[RewindSystem] Snapshot recorded with " << snapshot.size() << " entities. Total snapshots: " << history.size() << "\n";

        if (history.size() > maxFrameCount) {
            history.pop_front();
        }
    }
    // else {
    //   std::cerr << "[RewindSystem] Skipped empty snapshot.\n";
    // }
}

void RewindSystem::triggerRewind() {
    if (!history.empty()) {
        rewindIndex = static_cast<int>(history.size()) - 1;
        m_rewinding = true;
        //std::cerr << "[RewindSystem] Rewind triggered. Starting at index: " << rewindIndex << "\n";
    }
    else {
        //std::cerr << "[RewindSystem] Rewind failed - history is empty.\n";
    }
}

bool RewindSystem::isRewinding() const {
    return m_rewinding;
}

void RewindSystem::loadSnapShot(const FrameSnapshot& snapshot) {
    //std::cerr << "[RewindSystem] Loading snapshot with " << snapshot.size() << " entities...\n";

    entManager.clearAll();

    for (const auto& snap : snapshot) {
        std::shared_ptr<entity> ent;

        switch (snap.type) {
        case EntityType::Player:
            ent = entManager.createEntity<Player>();
            break;
        case EntityType::Enemy:
        case EntityType::MiniEnemy: {
            float speed = std::sqrt(snap.velocity.x * snap.velocity.x + snap.velocity.y * snap.velocity.y);
            ent = entManager.createEntity<Enemy>(speed, snap.radius, static_cast<float>(snap.vertices), snap.type);
            break;
        }
        case EntityType::Bullet:
            ent = entManager.createEntity<Bullet>(snap.pos, snap.velocity);
            break;
        }

        if (ent) {
            ent->setPos(snap.pos);
            ent->setVelocity(snap.velocity);
            ent->setLifetime(snap.lifetime);
            ent->setAge(snap.age);
        }
    }
}
