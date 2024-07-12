#include "main.h"
#include "vec2.h"
#include "utils.h"
#include <SFML/Window/Event.hpp>

void Entity::init(EntityShape shape, const void *para)
{
    switch (shape) {
        case EntityShape::CIRCLE_SHAPE: {
            circle = std::make_shared<sf::CircleShape>();
            CirclePara *cirPara = reinterpret_cast<CirclePara *>(const_cast<void *>(para));
            initCircle(circle, *cirPara);
            break;
        }
        case EntityShape::RECT_SHAPE: {
            rect = std::make_shared<sf::RectangleShape>();
            RectPara *rectPara = reinterpret_cast<RectPara *>(const_cast<void *>(para));
            initRect(rect, *rectPara);
            break;
        }
        default:
            LOG("invalid shape err");
            break;
    }
    m_shape = shape;
}

std::shared_ptr<sf::Shape> Entity::shape()
{
    switch (m_shape) {
        case EntityShape::CIRCLE_SHAPE:
            return circle;
        case EntityShape::RECT_SHAPE:
            return rect;
        default:
            break;
    }
    return nullptr;
}

void Entity::initCircle(std::shared_ptr<sf::CircleShape> e, const CirclePara &para)
{
    if (e == nullptr) {
        LOG("nullptr err");
        return;
    }
    e->setRadius(para.r);
    e->setPosition(para.pos.vec2f());
    e->setOrigin(para.origin.vec2f());
    e->setFillColor(para.fColor);
    e->setOutlineColor(para.oColor);
    e->setOutlineThickness(para.oThick);
}

void Entity::initRect(std::shared_ptr<sf::RectangleShape> e, const RectPara &para)
{
    if (e == nullptr) {
        LOG("nullptr err");
        return;
    }
    e->setSize(para.size.vec2f());
    e->setPosition(para.pos.vec2f());
    e->setOrigin(para.origin.vec2f());
    e->setFillColor(para.fColor);
    e->setOutlineColor(para.oColor);
    e->setOutlineThickness(para.oThick);
}

int Lab::init()
{
    m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1366, 768), "continuous collision detection");

    RectPara rectPara;
    CirclePara cirPara;

    std::shared_ptr<Entity> rect1 = std::make_shared<Entity>();
    rectPara.pos = { 100, 130 };
    rect1->init(EntityShape::RECT_SHAPE, &rectPara);
    std::shared_ptr<Entity> cir11 = std::make_shared<Entity>();
    cirPara.pos = rectPara.pos + Vec2(cirPara.r, cirPara.r);
    cirPara.pos.print("cir11");
    cir11->init(EntityShape::CIRCLE_SHAPE, &cirPara);

    m_entities["rect1"] = rect1;
    m_entities["cir11"] = cir11;

    std::shared_ptr<Entity> rect2 =std::make_shared<Entity>();
    rectPara.pos = { 760, 130 };
    rect2->init(EntityShape::RECT_SHAPE, &rectPara);
    std::shared_ptr<Entity> cir21 = std::make_shared<Entity>();
    cirPara.pos = rectPara.pos + Vec2(cirPara.r, cirPara.r);
    cirPara.pos.print("cir21");
    cir21->init(EntityShape::CIRCLE_SHAPE, &cirPara);

    m_entities["rect2"] = rect2;
    m_entities["cir21"] = cir21;

    return 0;
}

void Lab::labNormalCollisionDetect()
{
    Entity lab = *m_entities["rect1"];
}

void Lab::labContinuousCollisionDetect()
{
    Entity lab = *m_entities["rect2"];
}

int Lab::run()
{
    if (m_window == nullptr) {
        return 1;
    }
    while (m_isRunning) {
        procEvent();
        logic();
        render();
    }
    return 0;
}

void Lab::procEvent()
{
    sf::Event event;
    while (m_window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::EventType::KeyPressed:
                procKeypress(event.key);
                break;
            case sf::Event::Closed:
                m_isRunning = false;
                break;
            default:
                break;
        }
    }
}

void Lab::procKeypress(sf::Event::KeyEvent kEvent)
{
    switch (kEvent.code) {
        case sf::Keyboard::Key::Q:
            m_isRunning = false;
        default:
            break;
    }
}

void Lab::logic()
{

}

void Lab::render()
{
    m_window->clear(sf::Color::Black);
    for (auto &iter : m_entities) {
        if (iter.second != nullptr) {
            sf::Shape *shape = iter.second->shape().get();
            if (shape == nullptr) {
                continue;
            }
            m_window->draw(*shape);
        }
    }
    m_window->display();
}

int main(int argc, char* argv[])
{
    Lab l;
    l.init();
    return l.run();
}