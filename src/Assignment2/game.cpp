#include "game.h"
#include <iostream>
#include <fstream>

void Game::init()
{
    std::cout << m_configPath << std::endl;

    std::ifstream fin(m_configPath, std::ios::binary);

    if (!fin.is_open()) {
        std::cerr << "read config file failed" << std::endl;
        return;
    }

    std::string header;
    if (fin >> header >> m_videoMode.width >> m_videoMode.height >> m_frameLimit >> m_isFullScreen) {
    }
}

void Game::update()
{

}