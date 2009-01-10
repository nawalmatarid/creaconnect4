#ifndef IEVENTOBSERVER_H
#define IEVENTOBSERVER_H

#include <SFML/Window/Event.hpp>

//**************************
//Interface to observe events
//**************************
class IEventObserver
{
    public:
        //**************************
        //Description : Constructor
        //Parameters : None
        //Note : None
        //**************************
        IEventObserver() {};

        //**************************
        //Description : Destructor
        //Parameters : None
        //Note : None
        //**************************
        virtual ~IEventObserver() {};

        //**************************
        //Description : Actions performed when the listener is notified because an event occurred
        //Parameters : None
        //Return Value : None
        //Note : Virtual because depends on the entity notified
        //**************************
        virtual void Notify(sf::Event & _Event) = 0;

};
#endif
