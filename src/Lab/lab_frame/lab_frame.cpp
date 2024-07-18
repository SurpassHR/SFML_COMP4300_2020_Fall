#include "lab_frame.h"
#include "utils.h"

void Entity::init(EntityShape shape, const void *para)
{
    switch (shape) {
        case EntityShape::CIRCLE_SHAPE: {
            m_circle = std::make_shared<sf::CircleShape>();
            CirclePara *cirPara = reinterpret_cast<CirclePara *>(const_cast<void *>(para));
            initCircle(m_circle, *cirPara);
            break;
        }
        case EntityShape::RECT_SHAPE: {
            m_rect = std::make_shared<sf::RectangleShape>();
            RectPara *rectPara = reinterpret_cast<RectPara *>(const_cast<void *>(para));
            initRect(m_rect, *rectPara);
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
            return m_circle;
        case EntityShape::RECT_SHAPE:
            return m_rect;
        default:
            break;
    }
    return nullptr;
}

void Entity::update()
{
    shape()->setPosition(pos.vec2f());
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
    pos = para.pos;
    r = para.r;
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
    pos = para.pos;
    size = para.size;
}

int LabFrame::init()
{
    m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(m_windowSize.x, m_windowSize.y), m_title);
    m_window->setFramerateLimit(m_frameLimit);

    initEntities();

    return 0;
}

int LabFrame::run()
{
    if (m_window == nullptr) {
        return 1;
    }
    while (m_isRunning) {
        procEvent();
        movement();
        logic();
        render();
    }
    return 0;
}

void LabFrame::procEvent()
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

void LabFrame::procKeypress(sf::Event::KeyEvent kEvent)
{
    switch (kEvent.code) {
        case sf::Keyboard::Key::Q:
            m_isRunning = false;
        default:
            break;
    }
}

void LabFrame::render()
{
    m_window->clear(sf::Color::Black);
    for (auto &iter : m_entitiesSeq) {
        if (iter != nullptr) {
            auto shape = iter->shape();
            m_window->draw(*shape);
        }
    }
    m_window->display();
}