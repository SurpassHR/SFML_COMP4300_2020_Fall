#include "main.h"
#include "utils.h"

const unsigned FRAME_LIMIT = 60; // FPS
const double WINDOW_WIDTH = 1024; // px
const double WINDOW_HEIGHT = 768; // px

const unsigned GROUND_BLOCK_SIZE = 64; // px

const std::string GROUND_BLOCK_DESC = "ground";

void ActGameEntity::update()
{
    Entity::update();
}

void ActGameLab::initEntities()
{
    initGround();
}

void ActGameLab::initGround()
{
    RectPara rectPara;
    rectPara.size = { GROUND_BLOCK_SIZE, GROUND_BLOCK_SIZE };
    Vec2 windowLeftDownCorner(0, WINDOW_HEIGHT);
    Vec2 pos = windowLeftDownCorner - Vec2(0, GROUND_BLOCK_SIZE);
    // init ground for player to stand on
    int groundBlockNum = WINDOW_WIDTH / GROUND_BLOCK_SIZE;
    for (int i = 0; i < groundBlockNum; ++i) {
        std::shared_ptr<Entity> e = std::make_shared<Entity>(0);
        rectPara.pos = pos;
        pos.x += GROUND_BLOCK_SIZE + rectPara.oThick;
        e->init(EntityShape::RECT_SHAPE, &rectPara);
        m_entitiesSeq.push_back(e);
        m_entityMap[GROUND_BLOCK_DESC].push_back(e);
    }
}

void ActGameLab::logic()
{

}

void ActGameLab::movement()
{

}

void ActGameLab::collisionDetect()
{

}

void ActGameLab::updateCorrection()
{

}

int main()
{
    ActGameLab l(FRAME_LIMIT, { WINDOW_WIDTH, WINDOW_HEIGHT });
    if (l.init() != 0) {
        return 1;
    }
    return l.run();
}