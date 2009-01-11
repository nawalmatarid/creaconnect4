
#ifndef CMENU_H
#define CMENU_H

#include "../include/constants.h"

#include "../include/IEventObserver.h"

#include "../include/CSFMLManager.h"
#include "../include/CEventManager.h"
#include "../include/CGame.h"

//**************************
//Manage Rendering of the Menu
//**************************
class CMenu : public IEventObserver
{
    private:
        static CMenu * ms_Singleton;     //single instance of the menu renderer

        CSFMLManager * m_SFMLManager;         //instance of the SFML Manager
        sf::RenderWindow * m_RenderWindow;

        CEventManager * m_EventManager;

        CGame * m_Game;   //instance of the game

        sf::String m_Title;             //string for the title

        int m_iOptionSelected;              //Selected option in the menu
        sf::String m_Menu[NUMBER_OPTION_MENU];  //string for the options

        CSprite * m_SpriteBackground;       //sprite for the background

        bool m_bInMenu;         //boolean to know if we ara in the menu or not

        //**************************
        //Description : Constructor
        //Parameters : None
        //Note : Private because a single instance is needed
        //**************************
        CMenu();

    public:
        //**************************
        //Description : Destructor
        //Parameters : None
        //Note : None
        //**************************
        virtual ~CMenu();


        //**************************
        //Description : Create the instance of CMenu if it doesn't exist
        //Parameters : None
        //Return Value : the single instance of the CMenu
        //Note : None
        //**************************
        static CMenu* GetSingleton();

        //**************************
        //Description : Start the game and launch the menu
        //Parameters : None
        //Return Value : None
        //Note : None
        //**************************
        void StartMenu();

        //**************************
        //Description : Draw the menu
        //Parameters : None
        //Return Value : None
        //Note : None
        //**************************
        void DrawMenu();

        //**************************
        //Description : Manage the menu
        //Parameters : None
        //Return Value : None
        //Note : None
        //**************************
        void Menu();

        //**************************
        //Description : Actions performed when the listener is notified because an event occurred
        //Parameters : None
        //Return Value : None
        //Note : Virtual because depends on the entity notified
        //**************************
        virtual void Notify(sf::Event & _Event);
};

#endif // CMenu_H
