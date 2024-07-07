#include "entity_manager.h"

std::shared_ptr<Entity> EntityManager::AddEntity(const std::string tag)
{
    // create a new entity obj
    auto e = std::make_shared<Entity>(tag, m_entityNum++);
    if (e == nullptr) {
        return nullptr;
    }

    // store entity ptr
    m_entityToAdd.push_back(e);

    // store entity by its tag
    m_entityMap[e->Tag()].push_back(e);

    return e;
}

EntityVec EntityManager::GetEntities()
{
    return m_entityVec;
}

EntityVec EntityManager::GetEntities(const std::string tag)
{
    return m_entityMap[tag];
}

void EntityManager::Update()
{
    EntityVec entityUpdate;
    for (auto iter = m_entityVec.begin(); iter < m_entityVec.end(); ++iter) {
        if ((*iter)->IsDead()) {
            m_entityMap[(*iter)->Tag()].erase(iter);
            continue;
        }
        entityUpdate.push_back(*iter);
    }

    for (auto iter = m_entityToAdd.begin(); iter < m_entityToAdd.end(); ++iter) {
        entityUpdate.push_back(*iter);
    }

    m_entityToAdd.clear();
    m_entityVec = entityUpdate;
}

void EntityManager::ProcEntity(sf::RenderWindow &window)
{
    ProcEntityPos();
    DrawEntity(window);
}

void EntityManager::ProcEntityPos()
{
    for (auto & e : m_entityVec) {
        e->SetPos(e->Pos() + e->Velocity());
    }
}

void EntityManager::DrawEntity(sf::RenderWindow &window)
{
    for (auto & e : m_entityVec) {
        if (!e->Shape()) {
            continue;
        }
        window.draw(*e->Shape());
    }
}
