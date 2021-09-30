#include "game.hpp"


    /* ///////////////////////////////////////////////////////////////////////
    *       Author : Pawel Mlynarz
    *       License : MIT
    */////////////////////////////////////////////////////////////////////////


static void hideConsole(void)
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, 0);
}

int main(void)
{
    hideConsole();
    Game game;
    game.run();

    return 0;
}
