#ifndef IEVENTNOTIFIER_H
#define IEVENTNOTIFIER_H

#include <vector>
#include <SFML/Window/Event.hpp>

#include "../include/IEventObserver.h"

//**************************
//Notify all the Observers
//**************************
class IEventNotifier
{
    private:
		std::vector<IEventObserver *> * m_vEventObservers;	//Contains all the event Observers

    public:

		//**************************
		//Description : Constructor
		//Parameters : None
		//Note : None
		//**************************
		IEventNotifier();

		//**************************
		//Description : Constructor with a Observer
		//Parameters : None
		//Note : None
		//**************************
		IEventNotifier(IEventObserver & _EventObserver);

		//**************************
		//Description : Constructor with a vector of Observer
		//Parameters : None
		//Note : None
		//**************************
		IEventNotifier(std::vector<IEventObserver*> _vObservers);

		//**************************
		//Description : Destructor
		//Parameters : None
		//Note : None
		//**************************
		~IEventNotifier();

		//**************************
		//Description : Add an Event Observer to the vector
		//Parameters : A pointer to the event Observer
		//Return Value : None
		//Note : None
		//**************************
		void PushBackEventObserver(IEventObserver & _EventObserver);

		//**************************
		//Description : Delete an Event Observer from the vector
		//Parameters : None
		//Return Value : None
		//Note : None
		//**************************
		void PopEventObserver();

		//**************************
		//Description : Delete _Observer from the vector
		//Parameters : None
		//Return Value : None
		//Note : None
		//**************************
		void PopEventObserver(std::vector<IEventObserver*>::iterator _Observer);

		//**************************
		//Description : Notify all the observers with the event
		//Parameters : The new event
		//Return Value : None
		//Note : None
		//**************************
		void NotifyObservers(sf::Event & _Event);

		//**************************
		//Description : Return the vector of Observers
		//Parameters : None
		//Return Value : Vector of Observers
		//Note : None
		//**************************
		std::vector<IEventObserver*>* GetObservers();
};

#endif // IEVENTNOTIFIER_H
