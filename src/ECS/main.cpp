#include "game_typdef.h"
#include "entity_manager.h"
#include "entity.h"

void ProcKeyPressEvent(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::EventType::Closed) {
            window.close();
        }
    }
}

void GameLoop()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Entity Component System");
    EntityManager eMgr;
    Entity e({0.0f, 0.0f}, {0.0f, 0.0f});
    sf::CircleShape circle(50);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition({50.0f, 50.0f});
    e.SetShape(std::make_shared<sf::CircleShape>(circle));
    eMgr.RegEntity(e);

    // video loop
    while (window.isOpen()) {
        // proc key press event
        ProcKeyPressEvent(window);

        window.clear(sf::Color::Black);

        // proc entity status
        eMgr.ProcEntity(window);

        window.display();
    }
}

GAME_I32 main()
{
    GameLoop();

    return GAME_OK;
}