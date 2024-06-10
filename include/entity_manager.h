#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include "game_typdef.h"
#include "entity.h"

class EntityManager {
public:
    void RegEntity(Entity entity);
    void ProcEntity(sf::RenderWindow &window);
private:
    void ProcEntityPos();
    void DrawEntity(sf::RenderWindow &window);
private:
    std::vector<Entity> m_entities;
};

#endif // ENTITY_MANAGER_H
