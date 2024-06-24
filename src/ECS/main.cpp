#include <cstdlib>
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

int GetRandomNumber(int floor, int ceil) 
{
    int sign = (ceil - floor) / std::abs(ceil - floor);
    // the number of integers from floor to ceil
    int diff = std::abs(ceil - floor) + 1;
    // set the seed of rand generator
    srand(time(nullptr));
    int randomVal = std::rand();
    // get the possible value in range(abs(floor), abs(ceil))
    return sign * (floor + (randomVal % diff));
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
        // int floor = 10;
        // int ceil = 20;
        // std::cout << "rand: " << GetRandomNumber(floor, ceil) << std::endl;

        // proc entity status
        eMgr.ProcEntity(window);

        window.display();
    }
}

int main()
{
    GameLoop();

    return 0;
}