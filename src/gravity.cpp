#include "game_typdef.h"
#include <vector>

class Object;

std::vector<Object *> g_itemList;

class Object : public sf::CircleShape
{
public:
    Object() = default;
    ~Object() = default;

public:
    void SetSpeed(sf::Vector2f speed) { m_speedX = speed.x; m_speedY = speed.y; }
    GAME_F32 GetSpeedX() { return m_speedX; }
    GAME_F32 GetSpeedY() { return m_speedY; }

private:
    // 运动状态
    GAME_F32 m_speedX{ 0 };
    GAME_F32 m_speedY{ 0 };
};

void InitItemPosition(sf::RenderWindow &root, Object &obj)
{
    sf::Vector2u windPos = root.getSize();
    obj.setPosition({ static_cast<GAME_F32>(windPos.x) / 2, static_cast<GAME_F32>(windPos.y) / 2 });
}

void InitItemSpeed(Object &obj)
{
    obj.SetSpeed({ 0, 0 });
}

void RefreshSpeed(sf::RenderWindow &window, Object &obj, GAME_F32 deltaTime)
{
    sf::Vector2u windSize = window.getSize();
    GAME_F32 objY = obj.getPosition().y;
    GAME_F32 objR = obj.getRadius();
    // 下边缘碰撞检测
    if (objY + objR + 5.0f >= static_cast<GAME_F32>(windSize.y)) {
        obj.SetSpeed({ obj.GetSpeedX(), -obj.GetSpeedY() });
        obj.SetSpeed({ static_cast<GAME_F32>(obj.GetSpeedX()), static_cast<GAME_F32>((obj.GetSpeedY())) * 0.5f });
    } else if (objY - objR <= 0) {
        obj.SetSpeed({ obj.GetSpeedX(), -obj.GetSpeedY() });
        obj.SetSpeed({ static_cast<GAME_F32>(obj.GetSpeedX()), static_cast<GAME_F32>((obj.GetSpeedY())) * 0.5f });
    }
    // 动能损耗
    // 重力加速度
    obj.SetSpeed({ obj.GetSpeedX(), obj.GetSpeedY() + static_cast<GAME_F32>(GAME_G * 10) * deltaTime });
}

GAME_U32 VideoLoop()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML Gravity");
    // 设置窗口帧率限制165Hz
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(165);
    // 创建计时器
    sf::Clock clock;
    // 初始化画面颜色
    window.clear(sf::Color::Black);
    // 初始化图形
    for (auto &iter : g_itemList) {
        if (iter == nullptr) {
            return GAME_ERR;
        }
        InitItemPosition(window, *iter);
        InitItemSpeed(*iter);
    }
    while (window.isOpen()) {
        // 事件管理
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        // 获取前后两帧时间间隔
        GAME_F32 deltaTime = clock.restart().asSeconds();
        // 更新画面
        window.clear(sf::Color::Black);
        // 创建图形
        for (auto &iter : g_itemList) {
            if (iter == nullptr) {
                return GAME_ERR;
            }
            iter->setPosition(iter->getPosition().x + iter->GetSpeedX() * deltaTime, iter->getPosition().y + iter->GetSpeedY() * deltaTime);
            RefreshSpeed(window, *iter, deltaTime);
            window.draw(*iter);
        }
        window.display();
    }
    return GAME_OK;
}

GAME_I32 main()
{
    Object o1;
    o1.setFillColor(sf::Color::Red);
    o1.setRadius(10);
    g_itemList.push_back(&o1);
    return VideoLoop();
}