#ifndef CEVENTMANAGER_H
#define CEVENTMANAGER_H

#include "../include/IEventNotifier.h"

class IEventObserver;

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

//**************************
//Manage input events and notify Event Observers
//**************************
class CEventManager : public IEventNotifier
{
    private:
        static CEventManager * ms_Singleton;    //single instance of the managter

        sf::Event m_CurrentEvent;
        sf::RenderWindow * m_RenderWindow;

        //**************************
		//Description : Private constructor because it's a singleton
		//Parameters : None
		//Note : None
		//**************************
		CEventManager();

		//**************************
		//Description : Private constructor because it's a singleton with a Observer
		//Parameters : The render window
		//Note : None
		//**************************
		CEventManager(sf::RenderWindow * _RenderWindow);

	public:
		//**************************
		//Description : Destructor
		//Parameters : None
		//Note : None
		//**************************
		~CEventManager();

		//**************************
		//Description : Return the singleton of the manager
		//Parameters : The render window
		//Return Value : The singleton of the manager
		//Note : None
		//**************************
		static CEventManager* GetSingleton(sf::RenderWindow * _RenderWindow);

		//**************************
        //Description : Function managing all input events
        //Parameters : None
        //Return Value : None
        //Note : None
        //**************************
		void ManageEvents();



};

#endif

