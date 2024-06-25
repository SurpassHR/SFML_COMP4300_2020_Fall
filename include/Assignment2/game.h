#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "entity_manager.h"
#include "entity.h"

struct PlayerConfig {
    int
        SR, // Shape Radius
        CR, // Collision Radius
        FR, // Fillcolor Red
        FG, // Fillcolor Green
        FB, // Fillcolor Blue
        OR, // Outlinecolor Red
        OG, // Outlinecolor Green
        OB, // Outlinecolor Blue
        OT, // Outline Thickness
        SV  // Shape Verticies
    ;
    float
        S   // Speed
    ;
};

struct EnemyConfig {
    int
        SR,   // Shape Radius
        CR,   // Collision Radius
        OR,   // Outlinecolor Red
        OG,   // Outlinecolor Green
        OB,   // Outlinecolor Blue
        OT,   // Outline Thickness
        VMIN, // Min Verticies
        VMAX, // Max Verticies
        L     // (Small enemy)Lifespan
    ;
    float
        SMIN, // Min Speed
        SMAX  // Max Speed
    ;
};

struct BulletConfig {
    int
        SR, // Shape Radius
        CR, // Collision Radius
        FR, // Fillcolor Red
        FG, // Fillcolor Green
        FB, // Fillcolor Blue
        OR, // Outlinecolor Red
        OG, // Outlinecolor Green
        OB, // Outlinecolor Blue
        OT, // Outline Thickness
        SV, // Shape Verticies
        L   // (Bullet)Lifespan
    ;
    float
        S
    ;
};

class Game {
public:
    Game(const std::string &configPath) : m_configPath(configPath) {}
    ~Game() = default;
public:
    void update();
    // read config from file
    void init();
private:
    sf::VideoMode m_videoMode;
    unsigned m_frameLimit{ 60 };
    bool m_isFullScreen{ false };
    sf::RenderWindow m_window;
    EntityManager m_entities;
    Entity m_player;
    bool m_paused{ false };
    bool m_running{ true };

    const std::string &m_configPath;

    PlayerConfig m_playerConfig;
    EnemyConfig m_enemyConfig;
    BulletConfig m_bulletConfig;
};

#endif // GAME_H