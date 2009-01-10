#ifndef CGAME_H
#define CGAME_H

#include "../include/IEventObserver.h"
#include "../include/CSFMLManager.h"
#include "../include/CEventManager.h"

#include "../include/CBoard.h"
#include "../include/CPlayer.h"

#include <SFML/Graphics/RenderWindow.hpp>

//**************************
//Manage input events and notify Event Observers
//**************************
class CGame : public IEventObserver
{
    private:
        static CGame * ms_Singleton;    //single instance of the managter
        bool m_bInGame;                 //boolean to know if we are in the game or not
        bool m_bEndGame;                 //boolean to know if the game has ended (we have a winner) or not

        CSFMLManager * m_SFMLManager;
        sf::RenderWindow * m_RenderWindow;

        CEventManager * m_EventManager;

        CBoard * m_Board;

        CPlayer * m_Players[NUM_COLOR];

        //**************************
		//Description : Private constructor because it's a singleton
		//Parameters : None
		//Note : None
		//**************************
		CGame();

	public:
		//**************************
		//Description : Destructor
		//Parameters : None
		//Note : None
		//**************************
		~CGame();

		//**************************
		//Description : Return the singleton of the manager
		//Parameters : None
		//Return Value : The singleton of the manager
		//Note : None
		//**************************
		static CGame* GetSingleton();

		//**************************
        //Description : Draw the scene on the screen
        //Parameters : None
        //Return Value : None
        //Note : None
        //**************************
		void DrawScene();

		//**************************
        //Description : Start the game
        //Parameters : None
        //Return Value : None
        //Note : None
        //**************************
		void StartGame();

		//**************************
        //Description : Called when a game is done and display a winning message
        //Parameters : None
        //Return Value : None
        //Note : None
        //**************************
		void EndGame();

		//**************************
        //Description : Show the reward
        //Parameters : None
        //Return Value : None
        //Note : None
        //**************************
		void ShowReward();

		//**************************
        //Description : Game Loop
        //Parameters : None
        //Return Value : None
        //Note : None
        //**************************
		void Game();

		//**************************
        //Description : Actions performed when the listener is notified because an event occurred
        //Parameters : None
        //Return Value : None
        //Note : Virtual because depends on the entity notified
        //**************************
        virtual void Notify(sf::Event & _Event);

};

#endif

