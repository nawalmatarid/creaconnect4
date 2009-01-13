#include "include/CSFMLManager.h"
#include "include/CMenu.h"

int main(int argc, char **argv)
{
    //we create the window
    CSFMLManager::GetSingleton("CreaConnect4");

	//we create the menu and launch it
    CMenu * Menu = CMenu::GetSingleton();

    Menu->StartMenu();

    return EXIT_SUCCESS;
}
