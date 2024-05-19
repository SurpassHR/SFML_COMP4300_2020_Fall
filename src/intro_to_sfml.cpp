#include <iostream>
#include "game_typdef.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void moveUp(sf::Shape *shape)
{
    shape->move(0, -1);
    if (shape->getPosition().y < 0) {
        shape->setPosition(shape->getPosition().x, 0);
    }
}

void moveDown(sf::Shape *shape)
{
    shape->move(0, 1);
    if (shape->getPosition().y > WINDOW_HEIGHT) {
        shape->setPosition(shape->getPosition().x, WINDOW_HEIGHT);
    }
}

void moveLeft(sf::Shape *shape)
{
    shape->move(-1, 0);
    if (shape->getPosition().x < 0) {
        shape->setPosition(0, shape->getPosition().y);
    }
}

void moveRight(sf::Shape *shape)
{
    shape->move(1, 0);
    if (shape->getPosition().x > WINDOW_WIDTH) {
        shape->setPosition(WINDOW_WIDTH, shape->getPosition().y);
    }
}

int main() {
    // sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Window");
    // window.setFramerateLimit(165);
    // window.setVerticalSyncEnabled(true);

    // sf::RectangleShape rectangle(sf::Vector2f(100, 100));
    // rectangle.setFillColor(sf::Color::Red);
    // rectangle.setPosition(sf::Vector2f(100, 100));
    // rectangle.setRotation(45);
    // // 游戏循环
    // while (window.isOpen()) {
    //     window.clear(sf::Color::Black);

    //     // 处理输入事件
    //     sf::Event event;
    //     while (window.pollEvent(event)) {
    //         if (event.type == sf::Event::Closed) {
    //             window.close();
    //         }

    //         // 更新游戏状态

    //         // 渲染游戏场景

    //         if (event.key.code == sf::Keyboard::Up) {
    //             moveUp(&rectangle);
    //         } else if (event.key.code == sf::Keyboard::Down) {
    //             moveDown(&rectangle);
    //         } else if (event.key.code == sf::Keyboard::Left) {
    //             moveLeft(&rectangle);
    //         } else if (event.key.code == sf::Keyboard::Right) {
    //             moveRight(&rectangle);
    //         }

    //         // 绘制游戏场景

    //         window.draw(rectangle);

    //         // 绘制游戏场景

    //         window.display();
    //     }
    // }

    // // 创建一个窗体
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Intro to sfml"); // sf::RenderWindow才有draw的能力
    window.setSize(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT));
    window.setFramerateLimit(165);
    // 创建一个圆
    sf::CircleShape circle;
    circle.setFillColor(sf::Color::Green);
    circle.setOutlineColor(sf::Color(200, 0, 164));
    circle.setRadius(30);
    circle.setPosition(sf::Vector2f(static_cast<float>(WINDOW_WIDTH) / 2, static_cast<float>(WINDOW_HEIGHT) / 2));
    // 创建一个文本
    sf::Text text;
    // 创建一个字体
    sf::Font sfMonoSC;
    if (!sfMonoSC.loadFromFile("../fonts/SFMonoSC-Regular.ttf")) {
        std::cout << "Load Failed!" << std::endl;
    }
    // 设置字体
    text.setFont(sfMonoSC);
    // 设置文本内容
    text.setString("Hello, SFML!");
    // 设置文本颜色
    text.setFillColor(sf::Color::Red);
    // 设置文本大小
    text.setCharacterSize(24);
    // 设置文本位置
    text.setPosition(0, WINDOW_HEIGHT - text.getLocalBounds().height - 3);
    // 设置圆形的初始速度
    GAME_F32 circleSpeedX = 1.5f;
    GAME_F32 circleSpeedY = 2.5f;
    // 窗口主题循环
    while (window.isOpen()) {
        window.clear(sf::Color::Black);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::X) {
                    circleSpeedX *= -1;
                }
                if (event.key.code == sf::Keyboard::Y) {
                    circleSpeedY *= -1;
                }
            }
        }
        // window.draw(circle);
        if (circle.getPosition().x < 0 || circle.getPosition().x + 2 * circle.getRadius() > window.getSize().x) {
            circleSpeedX *= -1;
        }
        if (circle.getPosition().y < 0 || circle.getPosition().y + 2 * circle.getRadius() > window.getSize().y) {
            circleSpeedY *= -1;
        }
        circle.setPosition(sf::Vector2f(circle.getPosition().x + circleSpeedX, circle.getPosition().y + circleSpeedY));

        window.clear();
        window.draw(text);
        window.draw(circle);
        window.display();
    }

    return 0;
}