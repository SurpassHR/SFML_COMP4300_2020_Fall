#ifndef MAIN_H
#define MAIN_H

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
    Entity() = default;
    ~Entity() = default;
public:
    void init(EntityShape shape, const void *para);
    std::shared_ptr<sf::Shape> shape();
    int zIndex()
    {
        return m_zIndex;
    }
private:
    std::shared_ptr<sf::CircleShape> circle;
    std::shared_ptr<sf::RectangleShape> rect;
private:
    void initCircle(std::shared_ptr<sf::CircleShape> e, const CirclePara &para);
    void initRect(std::shared_ptr<sf::RectangleShape> e, const RectPara &para);
private:
    EntityShape m_shape{ INVALID_SHAPE };
    int m_zIndex{ 0 };
};

class Lab {
public:
    Lab() = default;
    ~Lab() = default;
public:
    int init();
    int run();
private:
    void procEvent();
    void procKeypress(sf::Event::KeyEvent kEvent);
    void logic();
    void render();

    void labNormalCollisionDetect();
    void labContinuousCollisionDetect();
private:
    std::shared_ptr<sf::RenderWindow> m_window;
    bool m_isRunning{ true };
    std::map<std::string, std::shared_ptr<Entity>> m_entities;
};

#endif // MAIN_H