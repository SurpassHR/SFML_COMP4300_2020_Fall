#include <cstdlib>
#include <string>
#include "game.h"

const std::string GAME_PROJ_CFG_PATH = "D:\\Codes\\Project\\external_git_repo\\COMP4300\\config\\assignment2";

int main()
{
    Game g(GAME_PROJ_CFG_PATH);
    g.init();
    return 0;
}