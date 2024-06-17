#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "entity.h"

/*
* EntityManager重构功能规划:
* 1. 创建和维护所有实体:
* 1.1 工厂的功能，创建一个Entity，并返回它的指针std::shared_ptr；
* 1.2 管理的功能，并将该Entity指针存储到std::vector成员m_entityVector，每个成员具有唯一标识m_entityNum，m_entityNum每次创建Entity后自增；
* 1.3 分类的功能，每个Entity又属于某个类型，如Tile、Player等，该类型通过Entity成员m_tag来标识，构造时赋值，通过EntityManager的成员m_entityMap来维护；
*   itf: std::shared_ptr<Entity> AddEntity(const std::string tag);
* 2. 获取管理的所有实体:
*   itf: std::vector<Entity> GetEntities();
*   itf: std::vector<Entity> GetEntities(const std::string tag);
* 3. 按照sfml video loop框架提供更新管理的所有实体的状态:
*   brief: 由于在逻辑运行过程中新增一个实体或销毁一个实体对于使用refrence的管理方法来说增加了维护的风险，所以需要增加一个缓冲区，
*       里面的内容不会在当前帧立即生效，而是在下一帧生效；
*   itf: void Update();
*/

using EntityVec = std::vector<std::shared_ptr<Entity>>;
using EntityMap = std::map<const std::string, EntityVec>;

class EntityManager {
public:
    std::shared_ptr<Entity> AddEntity(const std::string tag);
    EntityVec GetEntities();
    EntityVec GetEntities(const std::string tag);
    void Update();

    void ProcEntity(sf::RenderWindow &window);
private:
    void ProcEntityPos();
    void DrawEntity(sf::RenderWindow &window);
private:
    unsigned int m_entityNum{ 0 };
    EntityVec m_entityToAdd;
    EntityVec m_entityVec;
    EntityMap m_entityMap;
};

#endif // ENTITY_MANAGER_H
