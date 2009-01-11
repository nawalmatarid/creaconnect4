#include "../include/CMenu.h"

#include <math.h>

CMenu * CMenu::ms_Singleton = NULL;     //single instance of the menu renderer

//**************************
//Description : Constructor
//Parameters : None
//Note : Private because a single instance is needed
//**************************
CMenu::CMenu()
    : m_iOptionSelected(0),
    m_bInMenu(false)
{
    m_SFMLManager = CSFMLManager::GetSingleton();
    m_RenderWindow = m_SFMLManager->GetRenderWindow();

    m_EventManager = CEventManager::GetSingleton(m_RenderWindow);
    m_EventManager->PushBackEventObserver(*this);

    m_Game = CGame::GetSingleton();

    sf::Font * Font = m_SFMLManager->GetFont();

    m_Title.SetText("CreaConnect4");
    m_Title.SetColor(sf::Color(255,0,0));
    m_Title.Move(10, 10);
    m_Title.SetSize(50);

    m_Menu[0].SetText("Start Game");
    m_Menu[1].SetText("Quit");

    for (int i = 0; i < NUMBER_OPTION_MENU; i++)
    {
        m_Menu[i].SetFont(*Font);
        m_Menu[i].SetColor(sf::Color(255,0,0));
        m_Menu[i].Move(20, 300 + i * 40);
    }

    m_SpriteBackground = new CSprite(m_SFMLManager->GetAnimation(BACKGROUND), m_RenderWindow );
    m_SpriteBackground->SetPosition(0,0);
}

//**************************
//Description : Destructor
//Parameters : None
//Note : None
//**************************
CMenu::~CMenu()
{
    if ( m_SpriteBackground != NULL )
        delete m_SpriteBackground;

    if ( ms_Singleton != NULL )
        delete ms_Singleton;
}

//**************************
//Description : Create the instance of CMenu if it doesn't exist
//Parameters : None
//Return Value : the single instance of the CMenu
//Note : None
//**************************
CMenu* CMenu::GetSingleton()
{
    if ( ms_Singleton == NULL )
        ms_Singleton = new CMenu();

    return ms_Singleton;
}

//**************************
//Description : Start the game with the animation (TODO) and launch the menu
//Parameters : None
//Return Value : None
//Note : None
//**************************
void CMenu::StartMenu()
{
    Menu();
}

//**************************
//Description : Draw the menu
//Parameters : None
//Return Value : None
//Note : None
//**************************
void CMenu::DrawMenu()
{
    // We first fill the entire screen with black
    m_RenderWindow->SetBackgroundColor(sf::Color(0,0,0));

    //we draw the background
    m_SpriteBackground->Draw();

    //we draw the title at the top of the screen an to the center
    m_RenderWindow->Draw(m_Title);

    //we draw the options
    for (int i = 0; i < NUMBER_OPTION_MENU; i++)
    {
        if ( i == m_iOptionSelected )
        {
            sf::String star("*");
            star.SetFont(*(m_SFMLManager->GetFont()));
            star.SetColor(sf::Color(255,0,0));
            star.Move(10, 300 + i * 40);

            m_RenderWindow->Draw(star);
        }

        m_RenderWindow->Draw(m_Menu[i]);
    }

    //We display the screen
    m_RenderWindow->Display();
}

//**************************
//Description : Manage the menu
//Parameters : None
//Return Value : None
//Note : None
//**************************
void CMenu::Menu()
{
    m_bInMenu = true;

    //we stay in the menu while the application is opened
    while ( m_RenderWindow->IsOpened() )
    {
        m_EventManager->ManageEvents();

        //if we leave the menu, it means we have selected an option
        if ( !m_bInMenu )
        {
            switch (m_iOptionSelected)
            {
                //we launch the game
                case 0:
                {
                    m_Game->StartGame();
                    m_bInMenu = true;

                    break;
                }
                //we quit the game
                case 1:
                {
                    m_RenderWindow->Close();

                    break;
                }
            }
        }
        else
            //we draw the menu
            DrawMenu();
    }
}

//**************************
//Description : Actions performed when the listener is notified because an _Event occurred
//Parameters : None
//Return Value : None
//Note : Virtual because depends on the entity notified
//**************************
void CMenu::Notify(sf::Event & _Event)
{
    //if we are not in the menu, we don't car about incoming _Events
    if ( m_bInMenu )
    {
        if ( _Event.Type == sf::Event::KeyPressed )
        {
            if ( _Event.Key.Code == sf::Key::Escape )
                m_RenderWindow->Close();

            if ( _Event.Key.Code == sf::Key::Up )
                m_iOptionSelected = ((m_iOptionSelected - 1 + NUMBER_OPTION_MENU) % NUMBER_OPTION_MENU);

            if ( _Event.Key.Code == sf::Key::Down )
                m_iOptionSelected = (m_iOptionSelected + 1) % NUMBER_OPTION_MENU;

            if ( _Event.Key.Code == sf::Key::Return )
                //we leave the menu
                m_bInMenu = false;
        }
    }
}

