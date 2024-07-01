#include "game.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <random>
#include <ctime>

int Game::init()
{
    if (loadConfig() != 0) {
        return 1;
    }
    if (applyConfig() != 0) {
        return 1;
    }
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    return 0;
}

int Game::run()
{
    if (m_window == nullptr) {
        return 1;
    }
    while (m_running) {
        update();
        userInput();
        if (!m_paused) {
            movement();
            collision();
        }
        render();
    }
    return 0;
}

int Game::loadConfig()
{
    std::cout << "loading config from: " << m_configPath << std::endl;

    std::ifstream fin(m_configPath, std::ios::binary);

    if (!fin.is_open()) {
        std::cerr << "open config file failed" << std::endl;
        return 1;
    }

    std::string head = "";
    std::string tail = "";

    if ((fin >> head >> m_windowConfig.WW >> m_windowConfig.WH >> m_windowConfig.FL >> m_windowConfig.FS >> tail)) {
        std::cout << "parse " << head << ", " << tail << " config succ" << std::endl;
    }
    if ((fin >> head >> m_fontConfig.FP >> m_fontConfig.FS >> m_fontConfig.FR >> m_fontConfig.FG >> m_fontConfig.FB >> tail)) {
        std::cout << "parse " << head << ", " << tail << " config succ" << std::endl;
    }
    if ((fin >> head >> m_playerConfig.SR >> m_playerConfig.CR  >> m_playerConfig.S >> m_playerConfig.FR >>
        m_playerConfig.FG >> m_playerConfig.FB >> m_playerConfig.OR >> m_playerConfig.OG >> m_playerConfig.OB >>
        m_playerConfig.OT >> m_playerConfig.SV >> tail)) {
        std::cout << "parse " << head << ", " << tail << " config succ" << std::endl;
    }
    if ((fin >> head >> m_enemyConfig.SR >> m_enemyConfig.CR >> m_enemyConfig.FR >> m_enemyConfig.FG >>
        m_enemyConfig.FB >> m_enemyConfig.SMIN >> m_enemyConfig.SMAX >> m_enemyConfig.OR >> m_enemyConfig.OG >>
        m_enemyConfig.OB >> m_enemyConfig.OT >> m_enemyConfig.VMIN >> m_enemyConfig.VMAX >> m_enemyConfig.L >>
        m_enemyConfig.SI >> tail)) {
        std::cout << "parse " << head << ", " << tail << " config succ" << std::endl;
    }
    if ((fin >> head >> m_bulletConfig.SR >> m_bulletConfig.CR >> m_bulletConfig.S >> m_bulletConfig.FR >>
        m_bulletConfig.FG >> m_bulletConfig.FB >> m_bulletConfig.OR >> m_bulletConfig.OG >> m_bulletConfig.OB >>
        m_bulletConfig.OT >> m_bulletConfig.SV >> m_bulletConfig.L >> tail)) {
        std::cout << "parse " << head << ", " << tail << " config succ" << std::endl;
    }

    return 0;
}

int Game::applyConfig()
{
    if (m_windowConfig.FS) {
        m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(m_windowConfig.WW, m_windowConfig.WH), "Assignment2", sf::Style::Fullscreen);
    } else {
        m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(m_windowConfig.WW, m_windowConfig.WH), "Assignment2", sf::Style::Resize);
    }
    if (m_window == nullptr) {
        return 1;
    }
    m_window->setFramerateLimit(m_windowConfig.FL);
    return 0;
}

std::map<int, std::string> g_keycodeMap = {
    {sf::Keyboard::Unknown, "Unknown"},
    {sf::Keyboard::A, "A"},
    {sf::Keyboard::B, "B"},
    {sf::Keyboard::C, "C"},
    {sf::Keyboard::D, "D"},
    {sf::Keyboard::E, "E"},
    {sf::Keyboard::F, "F"},
    {sf::Keyboard::G, "G"},
    {sf::Keyboard::H, "H"},
    {sf::Keyboard::I, "I"},
    {sf::Keyboard::J, "J"},
    {sf::Keyboard::K, "K"},
    {sf::Keyboard::L, "L"},
    {sf::Keyboard::M, "M"},
    {sf::Keyboard::N, "N"},
    {sf::Keyboard::O, "O"},
    {sf::Keyboard::P, "P"},
    {sf::Keyboard::Q, "Q"},
    {sf::Keyboard::R, "R"},
    {sf::Keyboard::S, "S"},
    {sf::Keyboard::T, "T"},
    {sf::Keyboard::U, "U"},
    {sf::Keyboard::V, "V"},
    {sf::Keyboard::W, "W"},
    {sf::Keyboard::X, "X"},
    {sf::Keyboard::Y, "Y"},
    {sf::Keyboard::Z, "Z"},
    {sf::Keyboard::Num0, "Num0"},
    {sf::Keyboard::Num1, "Num1"},
    {sf::Keyboard::Num2, "Num2"},
    {sf::Keyboard::Num3, "Num3"},
    {sf::Keyboard::Num4, "Num4"},
    {sf::Keyboard::Num5, "Num5"},
    {sf::Keyboard::Num6, "Num6"},
    {sf::Keyboard::Num7, "Num7"},
    {sf::Keyboard::Num8, "Num8"},
    {sf::Keyboard::Num9, "Num9"},
    {sf::Keyboard::Escape, "Escape"},
    {sf::Keyboard::LControl, "LControl"},
    {sf::Keyboard::LShift, "LShift"},
    {sf::Keyboard::LAlt, "LAlt"},
    {sf::Keyboard::LSystem, "LSystem"},
    {sf::Keyboard::RControl, "RControl"},
    {sf::Keyboard::RShift, "RShift"},
    {sf::Keyboard::RAlt, "RAlt"},
    {sf::Keyboard::RSystem, "RSystem"},
    {sf::Keyboard::Menu, "Menu"},
    {sf::Keyboard::LBracket, "LBracket"},
    {sf::Keyboard::RBracket, "RBracket"},
    {sf::Keyboard::SemiColon, "SemiColon"},
    {sf::Keyboard::Comma, "Comma"},
    {sf::Keyboard::Period, "Period"},
    {sf::Keyboard::Quote, "Quote"},
    {sf::Keyboard::Slash, "Slash"},
    {sf::Keyboard::BackSlash, "BackSlash"},
    {sf::Keyboard::Tilde, "Tilde"},
    {sf::Keyboard::Equal, "Equal"},
    {sf::Keyboard::Dash, "Dash"},
    {sf::Keyboard::Space, "Space"},
    {sf::Keyboard::Return, "Return"},
    {sf::Keyboard::BackSpace, "BackSpace"},
    {sf::Keyboard::Tab, "Tab"},
    {sf::Keyboard::PageUp, "PageUp"},
    {sf::Keyboard::PageDown, "PageDown"},
    {sf::Keyboard::End, "End"},
    {sf::Keyboard::Home, "Home"},
    {sf::Keyboard::Insert, "Insert"},
    {sf::Keyboard::Delete, "Delete"},
    {sf::Keyboard::Add, "Add"},
    {sf::Keyboard::Subtract, "Subtract"},
    {sf::Keyboard::Multiply, "Multiply"},
    {sf::Keyboard::Divide, "Divide"},
    {sf::Keyboard::Left, "Left"},
    {sf::Keyboard::Right, "Right"},
    {sf::Keyboard::Up, "Up"},
    {sf::Keyboard::Down, "Down"},
    {sf::Keyboard::Numpad0, "Numpad0"},
    {sf::Keyboard::Numpad1, "Numpad1"},
    {sf::Keyboard::Numpad2, "Numpad2"},
    {sf::Keyboard::Numpad3, "Numpad3"},
    {sf::Keyboard::Numpad4, "Numpad4"},
    {sf::Keyboard::Numpad5, "Numpad5"},
    {sf::Keyboard::Numpad6, "Numpad6"},
    {sf::Keyboard::Numpad7, "Numpad7"},
    {sf::Keyboard::Numpad8, "Numpad8"},
    {sf::Keyboard::Numpad9, "Numpad9"},
    {sf::Keyboard::F1, "F1"},
    {sf::Keyboard::F2, "F2"},
    {sf::Keyboard::F3, "F3"},
    {sf::Keyboard::F4, "F4"},
    {sf::Keyboard::F5, "F5"},
    {sf::Keyboard::F6, "F6"},
    {sf::Keyboard::F7, "F7"},
    {sf::Keyboard::F8, "F8"},
    {sf::Keyboard::F9, "F9"},
    {sf::Keyboard::F10, "F10"},
    {sf::Keyboard::F11, "F11"},
    {sf::Keyboard::F12, "F12"},
    {sf::Keyboard::F13, "F13"},
    {sf::Keyboard::F14, "F14"},
    {sf::Keyboard::F15, "F15"},
    {sf::Keyboard::Pause, "Pause"}
};

constexpr int MOUSE_BUTTON_NUM = 2;
std::string g_mouseMap[MOUSE_BUTTON_NUM] = { "Left Button", "Right Button" };

void Game::userInput()
{
    sf::Event event;
    while (m_window->pollEvent(event)) {
        if (event.type == sf::Event::EventType::Closed) {
            m_window->close();
        }
        if (event.type == sf::Event::EventType::KeyPressed) {
            // std::cout << "keyPressed: " << g_keycodeMap[event.key.code] << std::endl;
            procKeyPressed(event.key.code);
        }
        if (event.type == sf::Event::EventType::KeyReleased) {
            // std::cout << "keyReleased: " << g_keycodeMap[event.key.code] << std::endl;
            procKeyReleased(event.key.code);
        }
        if (event.type == sf::Event::EventType::MouseButtonPressed) {
            // std::cout << "mousePressed: " << g_mouseMap[event.mouseButton.button] << " [" << event.mouseButton.x << ", " << event.mouseButton.y << "]" << std::endl;
        }
        if (event.type == sf::Event::EventType::MouseButtonReleased) {
            // std::cout << "mouseReleased: " << g_mouseMap[event.mouseButton.button] << " [" << event.mouseButton.x << ", " << event.mouseButton.y << "]" << std::endl;
        }
    }
}

void Game::movement()
{
    procPlayerMovement();
    procEntityMovement();
}

void Game::render()
{
    m_window->clear();

    // render player
    m_player->shape->shape().setPosition(m_player->shape->shape().getPosition() + m_player->transform->currVelocity.vec2f());
    m_window->draw(m_player->shape->shape());

    // render enemies
    auto enemies = m_entities.getEntities("enemy");
    for (auto e = enemies.begin(); e < enemies.end(); ++e) {
        Vec2 pos((*e)->shape->shape().getPosition() + (*e)->transform->currVelocity.vec2f());
        (*e)->transform->pos = pos;
        (*e)->shape->shape().setPosition((*e)->transform->pos.vec2f());
        m_window->draw((*e)->shape->shape());
    }

    // render bullets
    auto bullets = m_entities.getEntities("bullets");
    for (auto bullet = bullets.begin(); bullet < bullets.end(); ++bullet) {
        m_window->draw((*bullet)->shape->shape());
    }

    m_window->display();
    m_currentFrame++;
}

void Game::collision()
{
    // proc player collision with window boundary
    procBoundaryPlayerCollision();
    procBoundaryEnemyCollision();
}

// normalized direction vector
const Vec2 UP_DIRECTION(0.0f, -1.0f);
const Vec2 LEFT_DIRECTION(-1.0f, 0.0f);
const Vec2 DOWN_DIRECTION(0.0f, 1.0f);
const Vec2 RIGHT_DIRECTION(1.0f, 0.0f);

void Game::procPlayerMovement()
{
    if (m_player == nullptr) {
        std::cerr << "player nullptr err" << std::endl;
        return;
    }

    // rotation transform
    m_player->shape->shape().rotate(m_player->transform->angle);

    // movement transform
    Vec2 speed = m_player->transform->velocity;
    Vec2 direction(0.0f, 0.0f);
    direction += m_player->input->up ? UP_DIRECTION : Vec2(0.0f, 0.0f);
    direction += m_player->input->left ? LEFT_DIRECTION : Vec2(0.0f, 0.0f);
    direction += m_player->input->down ? DOWN_DIRECTION : Vec2(0.0f, 0.0f);
    direction += m_player->input->right ? RIGHT_DIRECTION : Vec2(0.0f, 0.0f);
    direction.normalize();
    speed *= direction;

    m_player->transform->currVelocity = speed;
}

void Game::procEntityMovement()
{
    auto enemies = m_entities.getEntities("enemy");
    for (auto e = enemies.begin(); e < enemies.end(); ++e) {
        (*e)->shape->shape().rotate((*e)->transform->angle);
    }
}

void Game::procBoundaryPlayerCollision()
{
    int wTop = 0;
    int wLeft = 0;
    int wBottom = m_window->getSize().y;
    int wRight = m_window->getSize().x;

    float playerR = m_player->shape->shape().getRadius();
    sf::Vector2f playerP = m_player->shape->shape().getPosition();
    Vec2 &currV = m_player->transform->currVelocity;

    bool rCollision = playerP.x + playerR + currV.x > wRight;
    bool lCollision = playerP.x - playerR + currV.x < wLeft;
    bool bCollision = playerP.y + playerR + currV.y > wBottom;
    bool tCollision = playerP.y - playerR + currV.y < wTop;

    if (rCollision || lCollision) {
        currV.x = 0.0f;
    }
    if (bCollision || tCollision) {
        currV.y = 0.0f;
    }
}

void Game::procBoundaryEnemyCollision()
{
    int wTop = 0;
    int wLeft = 0;
    int wBottom = m_window->getSize().y;
    int wRight = m_window->getSize().x;

    auto enemies = m_entities.getEntities("enemy");
    for (auto e = enemies.begin(); e < enemies.end(); ++e) {
        float eR = (*e)->shape->shape().getRadius();
        sf::Vector2f eP = (*e)->shape->shape().getPosition();
        Vec2 &currV = (*e)->transform->currVelocity;

        bool rCollision = eP.x + eR + currV.x > wRight;
        bool lCollision = eP.x - eR + currV.x < wLeft;
        bool bCollision = eP.y + eR + currV.y > wBottom;
        bool tCollision = eP.y - eR + currV.y < wTop;

        if (rCollision || lCollision) {
            currV.x *= -1.0f;
        }
        if (bCollision || tCollision) {
            currV.y *= -1.0f;
        }
    }
}

void Game::procKeyPressed(sf::Keyboard::Key key)
{
    using sfKey = sf::Keyboard::Key;
    switch (key) {
        case sfKey::P:
            m_paused = !m_paused;
            break;
        case sfKey::Q:
            m_running = false;
            break;
        case sfKey::W:
            m_player->input->up = true;
            break;
        case sfKey::A:
            m_player->input->left = true;
            break;
        case sfKey::S:
            m_player->input->down = true;
            break;
        case sfKey::D:
            m_player->input->right = true;
            break;
        default:
            break;
    }
}

void Game::procKeyReleased(sf::Keyboard::Key key)
{
    using sfKey = sf::Keyboard::Key;
    switch (key) {
        case sfKey::W:
            m_player->input->up = false;
            break;
        case sfKey::A:
            m_player->input->left = false;
            break;
        case sfKey::S:
            m_player->input->down = false;
            break;
        case sfKey::D:
            m_player->input->right = false;
            break;
        default:
            break;
    }
}

void Game::playerSpawner()
{
    auto e = std::make_shared<Entity>("player", 1234);

    if (e == nullptr) {
        std::cerr << "create player nullptr err" << std::endl;
        return;
    }

    e->transform = std::make_shared<Transform>(
        Vec2(200.0f, 200.0f),
        Vec2(5.0f, 5.0f),
        1.0f
    );

    e->shape = std::make_shared<Shape>(
        m_playerConfig.SR,
        m_playerConfig.SV,
        sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB),
        sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB),
        m_playerConfig.OT
    );
    e->shape->shape().setPosition(e->transform->pos.vec2f());

    e->input = std::make_shared<Input>();

    m_player = e;
}

void Game::enemySpawner()
{
    int wWidth = m_windowConfig.WW;
    int wHeight = m_windowConfig.WH;
    int origin = 0;

    auto e = m_entities.addEntity("enemy");
    if (e == nullptr) {
        return;
    }
    // generate number in range [0, wWidth] and [0, hWidth]
    int randX = origin + (std::rand() % (wWidth + 1));
    int randY = origin + (std::rand() % (wHeight + 1));
    Vec2 ePos(randX, randY);

    int minSpeed = m_enemyConfig.SMIN;
    int speedDiff = m_enemyConfig.SMAX - minSpeed;
    int speedX = minSpeed + (std::rand() % (speedDiff+ 1));
    int speedY = minSpeed + (std::rand() % (speedDiff+ 1));
    Vec2 eSpeed(speedX, speedY);

    e->transform = std::make_shared<Transform>(
        ePos,
        eSpeed,
        1.0f
    );
    e->transform->currVelocity = e->transform->velocity;
    e->shape = std::make_shared<Shape>(
        m_enemyConfig.SR,
        m_enemyConfig.VMAX,
        sf::Color(m_enemyConfig.FR, m_enemyConfig.FG, m_enemyConfig.FB),
        sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB),
        m_enemyConfig.OT
    );
    e->shape->shape().setPosition(e->transform->pos.vec2f());
}

void Game::update()
{
    if (!m_player) {
        playerSpawner();
    }
    if (m_currentFrame % 600 == 0) {
        enemySpawner();
    }
}