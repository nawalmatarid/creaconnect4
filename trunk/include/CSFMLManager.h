#ifndef CSFMLMANAGER_H
#define CSFMLMANAGER_H

#include <map>

#include "../include/constants.h"
#include "../include/CSpriteAnimation.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

//**************************
//Manage Initialisation and shutdown of SDL functions
//**************************
class CSFMLManager
{
    private:
        static CSFMLManager* ms_Singleton;  //Single instance of the SDL Manager
        sf::RenderWindow m_RenderWindow;      //Winfow of the application
        sf::Clock m_Clock;          //clock to know when we are since the beginning of the program
        sf::Font m_Font;            //font for the game

        std::map<int, CSpriteAnimation *> m_ListAnimation;      //map with all animation, (the key is an int defined in constants.h

        //**************************
        //Description : Constructor
        //Parameters : None
        //Note : Private because a single instance is needed
        //**************************
        CSFMLManager();

        //**************************
        //Description : Constructor
        //Parameters : The title of the window
        //Note : Private because a single instance is needed
        //**************************
        CSFMLManager(char * _szTitleWindow);

        //**************************
        //Description : Destructor
        //Parameters : None
        //Note : None
        //**************************
        ~CSFMLManager();

        //**************************
        //Description : Load the Surfaces needed by the game
        //Parameters : None
        //Return Value : None
        //Note : None
        //**************************
        void LoadSurfaces();

    public:
        //**************************
        //Description : Create the instance of CSFMLManager if it doesn't exist
        //Parameters : the title of the window
        //Return Value : the single instance of the CSFMLManager
        //Note : None
        //**************************
        static CSFMLManager* GetSingleton(char * _szTitleWindow = NULL);

        //**************************
        //Description : Display what is on the window
        //Parameters : None
        //Return Value : None
        //Note : None
        //**************************
        void Display();

        /*
        *   Setters and Getters
        */

        //**************************
        // The Render Window
        //**************************
        sf::RenderWindow* GetRenderWindow();

        //**************************
        // The time elapsed
        //**************************
        float GetElapsedTime();

        //**************************
        // Animation
        //**************************
        CSpriteAnimation * GetAnimation(int _NumAnimation);

        //**************************
        // Font
        //**************************
        sf::Font * GetFont();
};

#endif // CSFMLManager_H
