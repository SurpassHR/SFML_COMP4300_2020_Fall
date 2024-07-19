#ifndef LAB_FRAME_H
#define LAB_FRAME_H

#include <memory>
#include <map>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "vec2.h"

struct CirclePara {
    double r{ 32.0f };
    Vec2 pos{ r, r };
    Vec2 origin{ r, r };
    sf::Color fColor{ 89, 141, 243, 255 }; // fill color
    sf::Color oColor{ 255, 255, 255, 255 }; // outline color
    double oThick{ 2 }; // 2px
};

struct RectPara {
    Vec2 size{ 500.0f, 500.0f };
    Vec2 pos{ 0, 0 };
    Vec2 origin{ 0, 0 };
    sf::Color fColor{ 0, 0, 0, 255 }; // fill color
    sf::Color oColor{ 255, 255, 255, 255 }; // outline color
    double oThick{ 2 }; // 2px
};

enum EntityShape : unsigned short {
    INVALID_SHAPE = 0,
    RECT_SHAPE,
    CIRCLE_SHAPE,
};

class Entity {
public:
    Entity(int zIndex) : m_zIndex(zIndex) {}
    ~Entity() = default;
public:
    void init(EntityShape shape, const void *para);
    std::shared_ptr<sf::Shape> shape();
    int zIndex()
    {
        return m_zIndex;
    }
    virtual void update();
public:
    Vec2 pos{ 0.0f, 0.0f };
    Vec2 lastPos{ 0.0f, 0.0f };
    Vec2 velo{ 0.0f, 0.0f };
    Vec2 acc{ 0.0f, 0.0f };
    double r;
    Vec2 size{ 1.0f, 1.0f };
private:
    void initCircle(std::shared_ptr<sf::CircleShape> e, const CirclePara &para);
    void initRect(std::shared_ptr<sf::RectangleShape> e, const RectPara &para);
private:
    std::shared_ptr<sf::CircleShape> m_circle;
    std::shared_ptr<sf::RectangleShape> m_rect;
    EntityShape m_shape{ INVALID_SHAPE };
    int m_zIndex{ 0 };
};

class LabFrame {
public:
    LabFrame(unsigned frameLimit = 60, Vec2 windowSize = { 1024, 720 }, std::string title = "lab frame")
        : m_frameLimit(frameLimit),
          m_deltaT(1.0f / frameLimit),
          m_windowSize(windowSize),
          m_title() {}
    virtual ~LabFrame() = default;
public:
    int init();
    int run();
protected:
    virtual void initEntities() {}

    void procEvent();
    void procKeypress(sf::Event::KeyEvent kEvent);
    virtual void logic() {}
    virtual void movement() {}
    virtual void render();
    virtual void collisionDetect() {}
    virtual void updateCorrection() {}

    const double &deltaT() { return m_deltaT; }
protected:
    std::shared_ptr<sf::RenderWindow> m_window;
    std::map<std::string, std::shared_ptr<Entity>> m_entities;
    std::vector<std::shared_ptr<Entity>> m_entitiesSeq;
    bool m_isRunning{ true };
private:
    const unsigned m_frameLimit;
    const double m_deltaT;
    const Vec2 m_windowSize;
    const std::string m_title;
};

#endif // LAB_FRAME_H