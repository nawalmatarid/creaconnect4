#include "../include/constants.h"
#include "../include/CEventManager.h"

CEventManager * CEventManager::ms_Singleton = NULL;    //single instance of the managter

//**************************
//Description : Constructor
//Parameters : None
//Note : None
//**************************
CEventManager::CEventManager()
    : IEventNotifier(),
    m_CurrentEvent()
{
    m_RenderWindow = NULL;
}

//**************************
//Description : Private constructor because it's a singleton with a Observer
//Parameters : The render window
//Note : None
//**************************
CEventManager::CEventManager(sf::RenderWindow * _RenderWindow)
    : IEventNotifier(),
    m_CurrentEvent()
{
    m_RenderWindow = _RenderWindow;
}

//**************************
//Description : Destructor
//Parameters : None
//Note : None
//**************************
CEventManager::~CEventManager()
{
    delete ms_Singleton;
}

//**************************
//Description : Return the singleton of the manager
//Parameters : The render window
//Return Value : The singleton of the manager
//Note : None
//**************************
CEventManager* CEventManager::GetSingleton(sf::RenderWindow * _RenderWindow)
{
    if ( ms_Singleton == NULL )
        ms_Singleton = new CEventManager(_RenderWindow);

    return ms_Singleton;
}

//**************************
//Description : Function managing all input events
//Parameters : None
//Return Value : None
//Note : None
//**************************
void CEventManager::ManageEvents()
{
    while ( m_RenderWindow->GetEvent(m_CurrentEvent) )
    {
        if ( m_CurrentEvent.Type == sf::Event::Closed )
            m_RenderWindow->Close();

        NotifyObservers(m_CurrentEvent);
    }
}


