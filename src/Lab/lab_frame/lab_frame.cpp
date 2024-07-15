#include "lab_frame.h"

int LabFrame::init()
{
    m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1366, 768), "continuous collision detection");
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