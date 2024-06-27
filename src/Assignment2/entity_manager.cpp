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
    m_entities.clear();
    m_entities = activeEntities;
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag)
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>(tag, m_entityNum++);
    if (!e) {
        return nullptr;
    }
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
