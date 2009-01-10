#include "../include/constantes.h"
#include "../include/IEventNotifier.h"

//**************************
//Description : Constructor
//Parameters : None
//Note : None
//**************************
IEventNotifier::IEventNotifier()
{
	m_vEventObservers = new std::vector<IEventObserver *>();
}

//**************************
//Description : Constructor with a vector of Observers
//Parameters : None
//Note : None
//**************************
IEventNotifier::IEventNotifier(std::vector<IEventObserver*> _vObservers)
{
	m_vEventObservers = new std::vector<IEventObserver *>(_vObservers);
}

//**************************
//Description : Constructor with a Observer
//Parameters : None
//Note : None
//**************************
IEventNotifier::IEventNotifier(IEventObserver & _EventObserver)
{
	m_vEventObservers = new std::vector<IEventObserver *>();
	m_vEventObservers->push_back(&_EventObserver);
}

//**************************
//Description : Destructor
//Parameters : None
//Note : None
//**************************
IEventNotifier::~IEventNotifier()
{
	delete m_vEventObservers;
}

//**************************
//Description : Add an Event Observer to the vector
//Parameters : A pointer to the event Observer
//Return Value : None
//Note : None
//**************************
void IEventNotifier::PushBackEventObserver(IEventObserver & _EventObserver)
{
    if (m_vEventObservers != NULL)
        m_vEventObservers->push_back(&_EventObserver);
};

//**************************
//Description : Delete an Event Observer from the vector
//Parameters : None
//Return Value : None
//Note : None
//**************************
void IEventNotifier::PopEventObserver()
{
    if (m_vEventObservers != NULL)
    {
        std::vector<IEventObserver*>::iterator it = m_vEventObservers->end();
        it--;

        m_vEventObservers->erase(it);
    }
};

//**************************
//Description : Delete _Observer from the vector
//Parameters : None
//Return Value : None
//Note : None
//**************************
void IEventNotifier::PopEventObserver(std::vector<IEventObserver*>::iterator _Observer)
{
    if (m_vEventObservers != NULL)
        m_vEventObservers->erase(_Observer);
};

//**************************
//Description : Notify all the observers with the event
//Parameters : The new event
//Return Value : None
//Note : None
//**************************
void IEventNotifier::NotifyObservers(sf::Event & _Event)
{
    for(std::vector<IEventObserver*>::iterator it = m_vEventObservers->begin();
                it != m_vEventObservers->end();
                it++)
                (*it)->Notify(_Event);
}

//**************************
//Description : Return the vector of Observers
//Parameters : None
//Return Value : Vector of Observers
//Note : None
//**************************
std::vector<IEventObserver*>* IEventNotifier::GetObservers()
{
    return m_vEventObservers;
};
