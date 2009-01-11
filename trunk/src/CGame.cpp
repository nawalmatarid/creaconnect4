#include "../include/constants.h"
#include "../include/CGame.h"

CGame * CGame::ms_Singleton = NULL;    //single instance of the managter

//**************************
//Description : Constructor
//Parameters : None
//Note : None
//**************************
CGame::CGame()
    : IEventObserver(),
    m_bInGame(false),
    m_bEndGame(false)
{
    m_SFMLManager = CSFMLManager::GetSingleton();
    m_RenderWindow = m_SFMLManager->GetRenderWindow();

    m_EventManager = CEventManager::GetSingleton(m_RenderWindow);

    m_EventManager->PushBackEventObserver(*this);

    m_Board = NULL;

    for (int i = 0; i < NUM_COLOR; i++)
        m_Players[i] = NULL;
}

//**************************
//Description : Destructor
//Parameters : None
//Note : None
//**************************
CGame::~CGame()
{
    if ( m_Board != NULL )
        delete m_Board;

    for (int i = 0; i < NUM_COLOR; i++)
    {
        if ( m_Players[i] != NULL )
            delete m_Players[i];
    }

    delete ms_Singleton;
}

//**************************
//Description : Return the singleton of the manager
//Parameters : None
//Return Value : The singleton of the manager
//Note : None
//**************************
CGame* CGame::GetSingleton()
{
    if ( ms_Singleton == NULL )
        ms_Singleton = new CGame();

    return ms_Singleton;
}

//**************************
//Description : Draw the scene on the screen
//Parameters : None
//Return Value : None
//Note : None
//**************************
void CGame::DrawScene()
{
    //we clear the screen in white
    m_RenderWindow->SetBackgroundColor(sf::Color(220, 220, 220));

    //we draw the current player
    CPlayer::GetCurrentPlayer()->DisplayPlayer();

    //we draw the board
    m_Board->DisplayBoard();
}

//**************************
//Description : Start the game
//Parameters : None
//Return Value : None
//Note : None
//**************************
void CGame::StartGame()
{
    //we create the board
    m_Board = new CBoard(m_SFMLManager->GetAnimation(BOARD), m_RenderWindow);

    m_Board->CreateBoard();

    //we create two players
    for (int i = 0; i < NUM_COLOR; i++)
    {
        m_Players[i] = new CPlayer(m_SFMLManager->GetAnimation(RED+i), m_RenderWindow, (RED+i) );
        m_EventManager->PushBackEventObserver(*(m_Players[i]));
    }

    Game();
}

//**************************
//Description : Called when a game is done and display a winning message
//Parameters : None
//Return Value : None
//Note : None
//**************************
void CGame::EndGame()
{
    //we look for the previous player
    CPlayer * Player = CPlayer::GetCurrentPlayer();
    int i = 0;
    while ( i < NUM_COLOR && m_Players[i] != Player )
        i++;

    i = ( i-1 < 0 ) ? (NUM_COLOR-1) : (i-1);

    sf::Font * Font = m_SFMLManager->GetFont();
    sf::String StrFont;
    char num[2];
    std::string str;

    if ( m_Players[i]->GetScore() < SCOREWIN )
    {
        sprintf(num, "%d", (i+1));

        str = "You won Player ";
        str += num;
        str += "!!!";

        StrFont.SetText(str);
        StrFont.SetFont(*Font);
        StrFont.SetColor(sf::Color(255,0,0));
        StrFont.Move(280, 80);

        m_RenderWindow->Draw(StrFont);
    }
    else
    {
        sprintf(num, "%d", (i+1));

        str = "Player ";
        str += num;
        str += " won the game!!!";

        StrFont.SetText(str);
        StrFont.SetFont(*Font);
        StrFont.SetColor(sf::Color(255,0,0));
        StrFont.Move(250, 80);

        m_RenderWindow->Draw(StrFont);

        m_bEndGame = true;
    }
}

//**************************
//Description : Show the reward
//Parameters : None
//Return Value : None
//Note : None
//**************************
void CGame::ShowReward()
{
    //we announce the reward
    sf::Font * Font = m_SFMLManager->GetFont();
    sf::String StrFont;

    StrFont.SetText("Here is your reward !!!");
    StrFont.SetFont(*Font);
    StrFont.SetColor(sf::Color(255,0,0));
    StrFont.Move(250, 300);

    m_RenderWindow->SetBackgroundColor(sf::Color(220, 220, 220));
    m_RenderWindow->Draw(StrFont);
    m_RenderWindow->Display();

    //we show the text for 3 second
    float fNow = m_SFMLManager->GetElapsedTime();

    while ( m_SFMLManager->GetElapsedTime() < (fNow + 3.0f) );

    //we get the reward animation
    CSpriteAnimation * RewardAnimation = m_SFMLManager->GetAnimation(REWARD);

    //we randomise the reward
    int iNumReward = sf::Randomizer::Random(0, NUM_REWARD-1);

    //we create the reward
    CSprite RewardSprite(RewardAnimation, m_RenderWindow);

    RewardSprite.SetDisplayedFrame(iNumReward);
    RewardSprite.StopAnim();
    RewardSprite.SetPosition(0, 0);

    //we draw and display it
    m_RenderWindow->SetBackgroundColor(sf::Color(220, 220, 220));
    RewardSprite.Draw();
    m_RenderWindow->Display();

    //we show the reward for 5 second
    fNow = m_SFMLManager->GetElapsedTime();

    while ( m_SFMLManager->GetElapsedTime() < (fNow + 5.0f) );
}

//**************************
//Description : GameLoop
//Parameters : None
//Return Value : None
//Note : None
//**************************
void CGame::Game()
{
    //we are know in the game
    m_bInGame = true;

    while (m_bInGame && !m_bEndGame)
    {
        m_EventManager->ManageEvents();

        //we draw the scene
        DrawScene();

        //we drawn the end of a game is the is a winner
        if ( m_Board->ExistLine() )
        {
            EndGame();

            //we display the scene 3 seconds
            m_RenderWindow->Display();

            float fNow = m_SFMLManager->GetElapsedTime();

            while ( m_SFMLManager->GetElapsedTime() < (fNow + 3.0f) );

            //we restart the board and make the players loses their bonus
            m_Board->CreateBoard();

            for (int i = 0; i < NUM_COLOR; i++)
                m_Players[i]->LoseBonus();
        }
        else
            //we display the scene
            m_RenderWindow->Display();
    }

    //if it's the end of the game, we show the reward
    if ( m_bEndGame )
        ShowReward();

    //we pop the two players
    for (int i = 0; i < NUM_COLOR; i++)
    {
        m_EventManager->PopEventObserver();
        delete m_Players[i];
        m_Players[i] = NULL;
    }
}

//**************************
//Description : Actions performed when the listener is notified because an event occurred
//Parameters : None
//Return Value : None
//Note : Virtual because depends on the entity notified
//**************************
void CGame::Notify(sf::Event & _Event)
{
    //if we are not in the game, we don't car about incoming events
    if ( m_bInGame )
    {
        if ( _Event.Type == sf::Event::Closed )
            m_bInGame = false;

        if ( _Event.Type == sf::Event::KeyPressed )
        {
            if ( _Event.Key.Code == sf::Key::Escape )
                m_bInGame = false;
        }
    }
}
