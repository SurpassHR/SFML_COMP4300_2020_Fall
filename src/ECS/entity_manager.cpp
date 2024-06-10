#include <vector>
#include "entity_manager.h"

void EntityManager::RegEntity(Entity entity)
{
    m_entities.push_back(entity);
}

void EntityManager::ProcEntity(sf::RenderWindow &window)
{
    ProcEntityPos();
    DrawEntity(window);
}

void EntityManager::ProcEntityPos()
{
    for (auto & e : m_entities) {
        e.SetPos(e.Pos() + e.Velocity());
    }
}

void EntityManager::DrawEntity(sf::RenderWindow &window)
{
    for (auto & e : m_entities) {
        if (!e.Shape()) {
            continue;
        }
        window.draw(*e.Shape());
    }
}

