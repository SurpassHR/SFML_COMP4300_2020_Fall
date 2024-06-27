#include <cstdlib>
#include <string>
#include <filesystem>
#include "game.h"

const std::string GAME_PROJ_CFG_PATH = "\\config\\assignment2";

int main()
{
    // get project root working directory
    std::filesystem::path currPath = std::filesystem::current_path();
    std::string fullPath = currPath.string() + GAME_PROJ_CFG_PATH;
    Game g(fullPath);
    if (!g.init()) {
        return 1;
    }
    return g.run();
}