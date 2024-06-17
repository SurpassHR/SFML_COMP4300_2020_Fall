#include "game_typdef.h"
#include "entity_manager.h"

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
    auto e = eMgr.AddEntity("Circle");
    sf::CircleShape circle(50);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition({50.0f, 50.0f});
    e->SetShape(std::make_shared<sf::CircleShape>(circle));

    // video loop
    while (window.isOpen()) {
        // proc key press event
        ProcKeyPressEvent(window);

        // update entity info
        eMgr.Update();

        window.clear(sf::Color::Black);

        // proc some logic

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