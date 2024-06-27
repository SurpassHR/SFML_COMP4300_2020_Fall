#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "entity.h"

class EntityManager {
public:
    void init();
    void update();
    std::shared_ptr<Entity> addEntity(const std::string &tag);
    std::vector<std::shared_ptr<Entity>> getEntities();
    std::vector<std::shared_ptr<Entity>> getEntities(const std::string &tag);
public:
    int m_entityNum{ 0 };
    std::vector<std::shared_ptr<Entity>> m_entities;
    std::map<std::string, std::vector<std::shared_ptr<Entity>>> m_entityMap;
    std::vector<std::shared_ptr<Entity>> m_toAdd;
};

#endif // ENTITY_MANAGER_H