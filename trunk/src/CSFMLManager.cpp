#include "../include/CSFMLManager.h"

CSFMLManager * CSFMLManager::ms_Singleton = NULL; //single instance of the SDL_Manager

//**************************
//Description : Constructor
//Parameters : None
//Note : Private because a single instance is needed
//**************************
CSFMLManager::CSFMLManager()
    : m_RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), ""),
    m_Clock()
{
    LoadSurfaces();
}

//**************************
//Description : Constructor
//Parameters : Title of the window
//Note : Private because a single instance is needed
//**************************
CSFMLManager::CSFMLManager(char * _szTitleWindow)
    : m_RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), _szTitleWindow),
    m_Clock()
{
    LoadSurfaces();
}

//**************************
//Description : Destructor
//Parameters : None
//Note : None
//**************************
CSFMLManager::~CSFMLManager()
{
    std::map<int, CSpriteAnimation *>::iterator it = m_ListAnimation.begin();

    while ( !m_ListAnimation.empty() )
    {
        delete it->second;

        m_ListAnimation.erase(it);

        it = m_ListAnimation.begin();
    }

    if ( ms_Singleton != NULL )
        delete ms_Singleton;
}

//**************************
//Description : Create the instance of CSFMLManager if it doesn't exist
//Parameters : Title of the window
//Return Value : the single instance of the CSFMLManager
//Note : None
//**************************
CSFMLManager* CSFMLManager::GetSingleton(char * _szTitleWindow)
{
    if( ms_Singleton == NULL )
        ms_Singleton = new CSFMLManager(_szTitleWindow);

    return ms_Singleton;
}

//**************************
//Description : Load the Surfaces needed by the game (player, enemies, shots, font, ...)
//Parameters : None
//Return Value : None
//Note : None
//**************************
void CSFMLManager::LoadSurfaces()
{
    CSpriteAnimation * Anim;
    std::string Dir;

    //we load the font
    m_Font.LoadFromFile(szFont.c_str());

    //We load the background
    Anim = new CSpriteAnimation(szBgDir.c_str());

    m_ListAnimation.insert( std::pair<int, CSpriteAnimation *>(BACKGROUND, Anim) );

    //We load the board
    Anim = new CSpriteAnimation(szBoardDir.c_str());

    m_ListAnimation.insert( std::pair<int, CSpriteAnimation *>(BOARD, Anim) );

    //we load the reward
    Anim = new CSpriteAnimation(szRewardDir.c_str());

    m_ListAnimation.insert( std::pair<int, CSpriteAnimation *>(REWARD, Anim) );

    //We load the pawn colors
    for (int i = RED; i < (RED + NUM_COLOR); i++)
    {
        Dir.clear();
        Dir = szPawnDir;
        Dir += szPawnColorDir[i - RED];

        Anim = new CSpriteAnimation(Dir.c_str());

        m_ListAnimation.insert( std::pair<int, CSpriteAnimation *>(i, Anim) );
    }

    //We load the Bonus
    for (int i = DOUBLE; i < (DOUBLE + NUM_BONUS); i++)
    {
        Dir.clear();
        Dir = szBonusDir;
        Dir += szTypeBonusDir[i - DOUBLE];

        Anim = new CSpriteAnimation(Dir.c_str());

        m_ListAnimation.insert( std::pair<int, CSpriteAnimation *>(i, Anim) );
    }

    Anim = NULL;
}

//**************************
//Description : Display what is on the window
//Parameters : None
//Return Value : None
//Note : None
//**************************
void CSFMLManager::Display()
{
    m_RenderWindow.Display();
}

/*
*   Setters and Getters
*/

//**************************
// The Render Window
//**************************
sf::RenderWindow* CSFMLManager::GetRenderWindow()
{
    return &m_RenderWindow;
}

//**************************
// The time elapsed
//**************************
float CSFMLManager::GetElapsedTime()
{
    return m_Clock.GetElapsedTime();
}

//**************************
// Animation
//**************************
CSpriteAnimation * CSFMLManager::GetAnimation(int _NumAnimation)
{
    return m_ListAnimation[_NumAnimation];
}
//**************************
// Font
//**************************
sf::Font * CSFMLManager::GetFont()
{
    return &m_Font;
}
