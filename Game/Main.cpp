#include "Game.h"
#include "GraphicsLib/Tools/Initializer.h"

int main()
{
    gfx2d::initializer::initializeGL();
    const Game game;
    game.run();
    return 0;
}
