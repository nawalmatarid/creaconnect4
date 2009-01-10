#include "include/CGame.h"

int main(int argc, char **argv)
{
    CGame * Game = CGame::GetSingleton();

    Game->StartGame();

    return EXIT_SUCCESS;
}
