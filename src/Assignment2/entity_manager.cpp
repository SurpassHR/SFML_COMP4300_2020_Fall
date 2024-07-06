#include "entity_manager.h"

void EntityManager::init()
{

}

void EntityManager::update()
{
    std::vector<std::shared_ptr<Entity>> activeEntities;
    for (auto iter = m_toAdd.begin(); iter < m_toAdd.end(); ++iter) {
        if ((*iter)->m_active) {
            activeEntities.push_back(*iter);
        }
    }
    for (auto iter = m_entities.begin(); iter < m_entities.end(); ++iter) {
        if ((*iter)->m_active) {
            activeEntities.push_back(*iter);
        }
    }
    m_toAdd.clear();
    m_entities.clear();
    m_entities = activeEntities;
    for (auto &entities : m_entityMap) {
        for (auto iter = entities.second.begin(); iter < entities.second.end(); ++iter) {
            if (!(*iter)->m_active) {
                entities.second.erase(iter);
            }
        }
    }
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag, unsigned long long frameCreated, unsigned long long lifespan)
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>(tag, m_entityNum++);
    if (e == nullptr) {
        return nullptr;
    }
    e->lifespan = std::make_shared<Lifespan>(frameCreated, lifespan);
    e->m_active = true;
    m_toAdd.push_back(e);
    m_entityMap[tag].push_back(e);
    return e;
}

std::vector<std::shared_ptr<Entity>> EntityManager::getEntities()
{
    return m_entities;
}

std::vector<std::shared_ptr<Entity>> EntityManager::getEntities(const std::string &tag)
{
    return m_entityMap[tag];
}
