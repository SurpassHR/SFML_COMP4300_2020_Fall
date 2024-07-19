#include "main.h"
#include "utils.h"

const unsigned FRAME_LIMIT = 60; // FPS
const double WINDOW_WIDTH = 1024; // px
const double WINDOW_HEIGHT = 768; // px

const unsigned BLOCK_SIZE = 64; // px

const std::string GROUND_BLOCK_DESC = "ground";
const std::string PLAYER_BLOCK_DESC = "player";

const Vec2 GRAVITY(0, 980.0f); // m/s^2

void ActGameEntity::update()
{
    Entity::update();
}

void ActGameLab::initEntities()
{
    initGround();
    initPlayer();
}

void ActGameLab::initGround()
{
    RectPara rectPara;
    rectPara.size = { BLOCK_SIZE, BLOCK_SIZE };
    Vec2 windowLeftDownCorner(0, WINDOW_HEIGHT);
    Vec2 pos = windowLeftDownCorner - Vec2(0, BLOCK_SIZE);
    // init ground for player to stand on
    int groundBlockNum = WINDOW_WIDTH / BLOCK_SIZE;
    for (int i = 0; i < groundBlockNum; ++i) {
        std::shared_ptr<Entity> e = std::make_shared<Entity>(0);
        rectPara.pos = pos;
        pos.x += BLOCK_SIZE + rectPara.oThick;
        e->init(EntityShape::RECT_SHAPE, &rectPara);
        m_entitiesSeq.push_back(e);
        m_entityMap[GROUND_BLOCK_DESC].push_back(e);
    }
}

void ActGameLab::initPlayer()
{
    RectPara playerPara;
    playerPara.size = { BLOCK_SIZE, BLOCK_SIZE };
    Vec2 windowLeftDownCorner(BLOCK_SIZE, WINDOW_HEIGHT);
    Vec2 playerInitPos = windowLeftDownCorner - Vec2(0, BLOCK_SIZE) * 2;
    playerInitPos.x += playerPara.oThick;
    // init player
    if (m_player == nullptr) {
        m_player = std::make_shared<Entity>(1);
    }
    playerPara.pos = playerInitPos;
    m_player->init(EntityShape::RECT_SHAPE, &playerPara);
    m_player->acc = GRAVITY;
}

void ActGameLab::logic()
{
    initLogic();

    collisionDetect();
    updateCorrection();
}

void ActGameLab::initLogic()
{
    // give player a initial gravity acceleration

}

void ActGameLab::movement()
{
    auto shape = m_player->shape();
    if (shape != nullptr) {
        auto &pos = m_player->pos;
        auto &velo = m_player->velo;
        auto &acc = m_player->acc;
        auto &lastPos = m_player->lastPos;

        // Δv = aΔt
        Vec2 deltaV = acc * deltaT();
        velo += deltaV;
        // Δd = 1/2 vΔt
        Vec2 deltaD = velo * deltaT() * 0.5f;
        pos += deltaD;

        lastPos = pos;
    }
}

void ActGameLab::render()
{
    m_window->clear(sf::Color::Black);
    for (auto &iter : m_entitiesSeq) {
        if (iter != nullptr) {
            auto shape = iter->shape();
            m_window->draw(*shape);
        }
    }
    m_window->draw(*m_player->shape());
    m_window->display();
}

void ActGameLab::collisionDetect()
{
    double left = m_player->shape()->getPosition().x;
    double width = m_player->size.x;
    double top = m_player->shape()->getPosition().y;
    double height = m_player->size.y;

    double right = left + width;
    double bottom = top + height;

    auto groundBlockList = m_entityMap[GROUND_BLOCK_DESC];

    for (auto &iter : groundBlockList) {
        bool topOverlap = (iter->pos.y - iter->size.y < top);
        bool leftOverlap = (iter->pos.x - iter->size.x < left);
        bool bottomOverlap = (iter->pos.y + iter->size.y > bottom);
        bool rightOverlap = (iter->pos.x + iter->size.x > right);

        auto &pos = iter->pos;
        auto &velo = iter->velo;
        // auto &acc = cir21.acc;
        // auto &lastPos = cir21.lastPos;

        // double x0 = lastPos.x;
        // double y0 = lastPos.y;
        double x1 = pos.x;
        double y1 = pos.y;

        // x(0) = a * x0 + b
        // x(1) = a * x1 + b
        // -> x(t) = (x1 - x0) * t + x0
        // same with y:
        // -> y(t) = (y1 - y0) * t + y0

        // find t when x(t) + r = right
        // (x1 - x0) * t + x0 + r = right
        // t = (right - x0 - r) / (x1 - x0)
        // x(t) = (x1 - x0) * (right - x0 - r) / (x1 - x0) + x0 = right - r
        if (rightOverlap) {
            pos.x = right - iter->size.x;
            pos.x = 2.0f * pos.x - x1;
            pos.y = pos.y;
            velo.x *= -1.0f;
        }

        // find t when x(t) - r = left
        // (x1 - x0) * t + x0 - r = left
        // t = (left - x0 + r) / (x1 - x0)
        // x(t) = (x1 - x0) * (left - x0 + r) / (x1 - x0) + x0 = left + r
        // x'(1) = x(t) + (x(t) - x(1))
        if (leftOverlap) {
            pos.x = left + iter->size.x;
            pos.x = 2.0f * pos.x - x1;
            pos.y = pos.y;
            velo.x *= -1.0f;
        }

        // find t when y(t) - r = top
        // (y1 - y0) * t + y0 - r = top
        // t = (top - y0 + r) / (y1 - y0)
        // y(t) = (y1 - y0) * (top - y0 + r) / (y1 - y0) + y0 = top + r
        // y'(1) = y(t) - (y(1) - y(t)) = 2 * y(t) - y(1)
        if (topOverlap) {
            pos.y = top + iter->size.y;
            pos.y = 2.0f * pos.y - y1;
            pos.x = pos.x;
            velo.y *= -1.0f;
        }

        // find t when y(t) + r = bottom
        // (y1 - y0) * t + y0 + r = bottom
        // t = (bottom - y0 - r) / (y1 - y0)
        // y(t) = (y1 - y0) * (bottom - y0 - r) / (y1 - y0) + y0 = bottomm - r
        // y'(1) = y(t) + (y(t) - y(1)) = 2 * y(t) - y(1)
        if (bottomOverlap) {
            pos.y = bottom - iter->size.y;
            pos.y = 2.0f * pos.y - y1;
            pos.x = pos.x;
            velo.y *= -1.0f;
        }
    }
}

void ActGameLab::updateCorrection()
{
    m_player->update();
}

int main()
{
    ActGameLab l(FRAME_LIMIT, { WINDOW_WIDTH, WINDOW_HEIGHT });
    if (l.init() != 0) {
        return 1;
    }
    return l.run();
}