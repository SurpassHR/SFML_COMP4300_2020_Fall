#ifndef MAIN_H
#define MAIN_H

#include "lab_frame.h"
#include "vec2.h"

class ActGameEntity : public Entity {
public:
    ActGameEntity(int zIndex) : Entity(zIndex) {}
    ~ActGameEntity() = default;
public:
    void update() override;
};

class ActGameLab : public LabFrame {
public:
    ActGameLab(unsigned frameLimit, Vec2 windowSize)
        : LabFrame(frameLimit, windowSize, "act game lab") {}
    ~ActGameLab() = default;
private:
    void initEntities() override;

    void initGround();
    void initPlayer();

    void logic() override;

    void initLogic();

    void movement() override;
    void render() override;
    void collisionDetect() override;
    void updateCorrection() override;
private:
    std::map<std::string, std::vector<std::shared_ptr<Entity>>> m_entityMap;
    bool m_logicInit{ false };
    std::shared_ptr<Entity> m_player;
};

#endif // MAIN_H