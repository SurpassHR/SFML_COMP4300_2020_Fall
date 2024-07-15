#ifndef MAIN_H
#define MAIN_H

#include "lab_frame.h"

class CollisionEntity : public Entity {
public:
    CollisionEntity(int zIndex) : Entity(zIndex) {}
    ~CollisionEntity() = default;
public:
    void init(EntityShape shape, const void *para);
    std::shared_ptr<sf::Shape> shape();
};

class CollisionLab : public LabFrame {
public:
    CollisionLab(unsigned frameLimit) : LabFrame(frameLimit) {}
    ~CollisionLab() override = default;
private:
    void initEntities() override;

    void logic() override;
    void movement() override;
    void collisionDetect() override;
    void updateCorrection() override;

    void initLogic();

    void labNormalCollisionDetect();
    void labContinuousCollisionDetect();
private:
    bool m_init{ false };
};

#endif // MAIN_H