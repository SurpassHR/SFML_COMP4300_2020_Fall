#include "game.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <ctime>
#include <cmath>

#define DEBUG false

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
        spawner();
        userInput();
        if (!m_paused) {
            lifespan();
            update();
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

    m_font = std::make_shared<sf::Font>();
    if (!m_font->loadFromFile("fonts/SFMonoSC-Regular.ttf")) {
        std::cout << "Load Failed!" << std::endl;
    }

    m_scoreDisp = std::make_shared<sf::Text>();

    m_scoreDisp->setFont(*m_font);
    m_scoreDisp->setFillColor(sf::Color(m_fontConfig.FR, m_fontConfig.FG, m_fontConfig.FB));
    m_scoreDisp->setCharacterSize(m_fontConfig.FS);
    m_scoreDisp->setPosition(0, 0);

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
            bulletSpawner(Vec2(event.mouseButton.x, event.mouseButton.y));
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
    m_window->draw(m_player->shape->shape());

    // render enemies
    auto enemies = m_entities.getEntities("enemy");
    for (auto e = enemies.begin(); e < enemies.end(); ++e) {
        m_window->draw((*e)->shape->shape());
    }

    // render bullets
    auto bullets = m_entities.getEntities("bullet");
    for (auto bullet = bullets.begin(); bullet < bullets.end(); ++bullet) {
        m_window->draw((*bullet)->shape->shape());
    }

    m_window->draw(*m_scoreDisp);

    m_window->display();
    m_currentFrame++;
}

void Game::collision()
{
    // proc player collision with window boundary
    procBoundaryPlayerCollision();
    procBoundaryEnemyCollision();
    procEnemiesCollision();
    procBulletEnemyCollision();
}

void Game::lifespan()
{
    auto entities = m_entities.getEntities();
    for (auto e = entities.begin(); e < entities.end(); ++e) {
        // situation1: entity out of frame
        int eR = (*e)->shape->shape().getRadius();
        if (((*e)->transform->pos.x - eR > m_window->getSize().x) ||
            ((*e)->transform->pos.x + eR < 0) ||
            ((*e)->transform->pos.y - eR > m_window->getSize().y) ||
            ((*e)->transform->pos.y + eR < 0)) {
            (*e)->m_active = false;
        }
        // situation2: entity life at an end
        if (m_currentFrame - (*e)->lifespan->frameCreated > (*e)->lifespan->lifespan) {
            (*e)->m_active = false;
        }
    }
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

        // entity overstep window border
        bool rOverstep = (eP.x + eR > wRight) && (eP.x + eR + currV.x > wRight);
        bool lOverstep = (eP.x - eR < wLeft) && (eP.x - eR + currV.x < wLeft);
        bool bOverstep = (eP.y + eR > wBottom) && (eP.y + eR + currV.y > wBottom);
        bool tOverstep = (eP.y - eR < wTop) && (eP.y - eR + currV.y < wTop);

        if (rOverstep) {
            currV.x = -1.0f;
        }
        if (lOverstep) {
            currV.x = 1.0f;
        }
        if (bOverstep) {
            currV.y = -1.0f;
        }
        if (tOverstep) {
            currV.y = 1.0f;
        }
    }
}

void Game::procEnemiesCollision()
{
    auto enemies = m_entities.getEntities("enemy");
    for (int i = 0; i < enemies.size(); ++i) {
        for (int j = i + 1; j < enemies.size(); ++j) {
            auto e1 = enemies[i];
            auto e2 = enemies[j];

            Vec2 relativePos = e2->transform->pos - e1->transform->pos;
            double dist = relativePos.length();
            double radiusSum = e1->shape->shape().getRadius() + e2->shape->shape().getRadius();

            // collision happens
            Vec2 normal = relativePos.normalized();
            Vec2 relativeVelocity = e2->transform->currVelocity - e1->transform->currVelocity;

            double velocityAlongNormal = relativeVelocity.dot(normal);

            double nextDist = dist - velocityAlongNormal;

            if (nextDist * nextDist <= radiusSum * radiusSum) {

                // object detaching
                if (velocityAlongNormal > 0)
                    continue;

                // elastic coeff (perfectly)
                double restitution = 1.0f;

                double impulseMagnitude = -(1 + restitution) * velocityAlongNormal;
                impulseMagnitude /= 2;

                Vec2 impulse = normal * impulseMagnitude;
                e1->transform->currVelocity -= impulse / 1;
                e2->transform->currVelocity += impulse / 1;

                // process overlap
                double overlap = radiusSum - dist;
                Vec2 separation = normal * overlap * 0.5;
                e1->shape->shape().setPosition(e1->shape->shape().getPosition() - separation.vec2f());
                e2->shape->shape().setPosition(e2->shape->shape().getPosition() + separation.vec2f());
            }
        }
    }
}

void Game::procBulletEnemyCollision()
{
    auto bullets = m_entities.getEntities("bullet");
    auto enemies = m_entities.getEntities("enemy");
    for (auto b = bullets.begin(); b < bullets.end(); ++b) {
        if ((*b) == nullptr)  {
            continue;
        }
        for (auto e = enemies.begin(); e < enemies.end(); ++e) {
            if ((*e) == nullptr) {
                continue;
            }
            auto enemy = *e;
            auto bullet = *b;
            if (isCollision(enemy, bullet)) {
                bullet->m_active = false;
                enemy->m_active = false;
                m_player->score->score += enemy->shape->shape().getPointCount() * 100;
            }
        }
    }
}

bool Game::isCollision(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2)
{
    Vec2 e1Pos = e1->transform->pos;
    Vec2 e2Pos = e2->transform->pos;
    Vec2 dist = e2Pos - e1Pos;
    double radiusSum = e1->shape->shape().getRadius() + e2->shape->shape().getRadius();
    return dist.length2() <= radiusSum * radiusSum;
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

    e->score = std::make_shared<Score>();

    m_player = e;
}

void Game::enemySpawner()
{
    if (DEBUG) {
        auto e1 = debugSpawner();
        e1->transform->currVelocity = Vec2(1.0f, 0.0f);
        e1->shape->shape().setPosition({ 32.0f, 192.0f });
        auto e2 = debugSpawner();
        e2->transform->currVelocity = Vec2(-1.0f, 0.0f);
        e2->shape->shape().setPosition({ 688.0f, 192.0f });
        return;
    }

    // avoid spawning enemy on the border
    int wWidth = m_windowConfig.WW - m_enemyConfig.SR;
    int wHeight = m_windowConfig.WH - m_enemyConfig.SR;
    int origin = 0.0f + m_enemyConfig.SR;

    auto e = m_entities.addEntity("enemy", m_currentFrame);
    if (e == nullptr) {
        return;
    }
    // generate number in range [origin, wWidth] and [origin, hWidth]
    int randX = origin + (std::rand() % (wWidth - origin + 1));
    int randY = origin + (std::rand() % (wHeight - origin + 1));
    Vec2 ePos(randX, randY);

    int minSpeed = m_enemyConfig.SMIN;
    int speedDiff = m_enemyConfig.SMAX - minSpeed;
    int speedX = minSpeed + (std::rand() % (speedDiff + 1));
    int speedY = minSpeed + (std::rand() % (speedDiff + 1));
    Vec2 eSpeed(speedX, speedY);

    int minVert = m_enemyConfig.VMIN;
    int maxVert = m_enemyConfig.VMAX;
    int vertDiff = maxVert - minVert;
    int randVert = minVert + (std::rand() % (vertDiff + 1));

    e->transform = std::make_shared<Transform>(
        ePos,
        eSpeed,
        1.0f
    );
    e->transform->currVelocity = e->transform->velocity;
    e->shape = std::make_shared<Shape>(
        m_enemyConfig.SR,
        randVert,
        randColorGenerator(),
        randColorGenerator(),
        m_enemyConfig.OT
    );
    e->shape->shape().setPosition(e->transform->pos.vec2f());
}

void Game::bulletSpawner(const Vec2 &mPos)
{
    Vec2 pPos = m_player->transform->pos;
    Vec2 relaDire = (mPos - pPos).normalized();
    double length = m_player->shape->shape().getRadius();
    Vec2 bulletGenPos = pPos + relaDire * length;
    auto bullet = m_entities.addEntity("bullet", m_currentFrame);
    Vec2 pVelocity = m_player->transform->currVelocity;
    bullet->shape = std::make_shared<Shape>(
        m_bulletConfig.SR,
        30,
        sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB),
        sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB),
        m_bulletConfig.OT
    );
    bullet->transform = std::make_shared<Transform>(
        bulletGenPos,
        // bullet initial have the speed of player
        Vec2(10.0f, 10.0f) * relaDire + pVelocity,
        1.0f
    );
    bullet->transform->currVelocity = bullet->transform->velocity;
}

sf::Color Game::randColorGenerator()
{
    short randR = std::rand();
    short randG = std::rand();
    short randB = std::rand();

    short colorMin = 0;
    short colorMax = 255;

    randR = colorMin + (randR % (colorMax - colorMin + 1));
    randG = colorMin + (randG % (colorMax - colorMin + 1));
    randB = colorMin + (randB % (colorMax - colorMin + 1));

    return sf::Color(randR, randG, randB);
}

std::shared_ptr<Entity> Game::debugSpawner()
{
    auto e = m_entities.addEntity("enemy", m_currentFrame);
    int minVert = m_enemyConfig.VMIN;
    int maxVert = m_enemyConfig.VMAX;
    int vertDiff = maxVert - minVert;
    int randVert = minVert + (std::rand() % (vertDiff + 1));
    e->shape = std::make_shared<Shape>(
        m_enemyConfig.SR,
        randVert,
        randColorGenerator(),
        randColorGenerator(),
        m_enemyConfig.OT
    );
    e->transform = std::make_shared<Transform>(
        Vec2(m_enemyConfig.SR, m_enemyConfig.SR),
        Vec2(0.0f, 0.0f),
        1.0f
    );
    return e;
}

const std::string SCORE_DISP_PREFIX = "Score: ";
void Game::update()
{
    m_entities.update();

    m_player->update();

    auto entities = m_entities.getEntities();
    for (auto e = entities.begin(); e < entities.end(); ++e) {
        (*e)->update();
    }
    if (m_scoreDisp && m_player && m_player->score) {
        std::string scoreStr = SCORE_DISP_PREFIX + std::to_string(m_player->score->score);
        m_scoreDisp->setString(scoreStr);
    } else {
        std::cerr << "Error: Null pointer encountered when updating score display" << std::endl;
    }
}

const unsigned ENEMY_SPAWN_INTERVAL = 300; // frames
void Game::spawner()
{
    if (m_player == nullptr) {
        playerSpawner();
    }
    if (m_currentFrame % ENEMY_SPAWN_INTERVAL == 0) {
        enemySpawner();
    }
}