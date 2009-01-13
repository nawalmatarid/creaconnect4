#include "../include/CPlayer.h"
#include "../include/CBoard.h"

#include "../include/CSFMLManager.h"

#include <SFML/Graphics/String.hpp>

CPlayer * CPlayer::ms_Players[NUM_COLOR] = { NULL };        //static array wich contain all the players
int CPlayer::ms_iNbPlayer = 0;        //static number of players
CPlayer * CPlayer::ms_CurrentPlayer = NULL;        //static pointer toward the current player in game
int CPlayer::ms_iCurrentPlayer = 0;        //static number of the current player
bool CPlayer::ms_bNextPlayer = false;        //static boolean to know if we have to change player or not

//**************************
//Description : Constructor
//Parameters : None
//Note : None
//**************************
CPlayer::CPlayer()
    : IEventObserver(),
    m_iColor(RED),
    m_iCurrentColumn(0),
    m_iScore(0),
    m_ListBonus()
{
    m_Sprite = NULL;

    m_PawnAnimation = NULL;

    m_RenderWindow = NULL;

    //we add this player to the list
    if ( ms_iNbPlayer < NUM_COLOR )
    {
        ms_Players[ms_iNbPlayer] = this;
        ms_iNbPlayer++;
    }

    //if it's the irst player created, we set it to the current player
    if ( ms_CurrentPlayer == NULL )
        ms_CurrentPlayer = this;
}

//**************************
//Description : Constructor
//Parameters : The animation of a pawn, the RenderWindow
//              the color of the player
//Note : None
//**************************
CPlayer::CPlayer(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow, int _iColor)
    : IEventObserver(),
    m_iColor(_iColor),
    m_iCurrentColumn(0),
    m_iScore(0),
    m_ListBonus()
{
    m_Sprite = new CSprite(_Animation, _RenderWindow);

    m_Sprite->SetPosition(BOARD_X_ORIGIN, 0);

    m_PawnAnimation = _Animation;

    m_RenderWindow = _RenderWindow;

    //we add this player to the list
    if ( ms_iNbPlayer < NUM_COLOR )
    {
        ms_Players[ms_iNbPlayer] = this;
        ms_iNbPlayer++;
    }

    //if it's the first player created, we set it to the current player
    if ( ms_CurrentPlayer == NULL )
        ms_CurrentPlayer = this;
}

//**************************
//Description : Destructor
//Parameters : None
//Note : None
//**************************
CPlayer::~CPlayer()
{
    while ( !m_ListBonus.empty() )
    {
        delete m_ListBonus.back();

        m_ListBonus.pop_back();
    }

    if ( m_Sprite != NULL )
        delete m_Sprite;

	//we change the current player
	if ( ms_iNbPlayer != 1 )
	{
		if ( ms_CurrentPlayer == this )
			SetNextPlayer();
	}
	else
	{
		ms_CurrentPlayer = NULL;
		ms_iCurrentPlayer = 0;
	}

	//we pop this player from the list
    int i = 0;
    while ( i < NUM_COLOR && ms_Players[i] != this )
        i++;

    if ( i < NUM_COLOR )
    {
        ms_Players[i] = NULL;
        ms_iNbPlayer--;
    }

	ms_bNextPlayer = false;
}

//**************************
//Description : Display the player on the screen
//Parameters : None
//Return value : None
//Note : None
//**************************
void CPlayer::DisplayPlayer()
{
    m_Sprite->Draw();

    CSFMLManager * Manager = CSFMLManager::GetSingleton();

    sf::Font * Font = Manager->GetFont();

    //we display text
    char num[2];
    std::string str;
    sf::String NumPlayer, ScorePlayer;

    sprintf(num, "%d", (m_iColor-RED+1));

    str = "Player ";
    str += num;

    NumPlayer.SetText(str);
    NumPlayer.SetFont(*Font);
    NumPlayer.SetColor(sf::Color(255,0,0));
    NumPlayer.Move(0, 0);

    sprintf(num, "%d", m_iScore);

    str = "Score : ";
    str += num;

    ScorePlayer.SetText(str);
    ScorePlayer.SetFont(*Font);
    ScorePlayer.SetColor(sf::Color(255,0,0));
    ScorePlayer.Move(0, NumPlayer.GetSize());

    m_RenderWindow->Draw(NumPlayer);
    m_RenderWindow->Draw(ScorePlayer);

    //we display the bonus
    IBonus * Bonus;

    for (int i = 0; i < m_ListBonus.size(); i++)
    {
        Bonus = m_ListBonus[i];

        Bonus->DisplaySquare(0, 60 + i * Bonus->GetSprite()->GetHeight() );
    }
}

//**************************
//Description : The player gain a bonus
//Parameters : the bonus gained
//Return value : None
//Note : None
//**************************
void CPlayer::GainBonus(IBonus * _Bonus)
{
    //when a player gain a bonus, it become discovered
    _Bonus->SetDiscovered(true);

    m_ListBonus.push_back(_Bonus);
}

//**************************
//Description : The player lose all of this bonus
//Parameters : None
//Return value : None
//Note : This is usually due to an restart of the game, but maybe if we create a new bonus... ^^
//**************************
void CPlayer::LoseBonus()
{
    //we delete the bonus
    IBonus * Bonus;

    while ( !m_ListBonus.empty() )
    {
        Bonus = m_ListBonus.back();

        delete Bonus;

        m_ListBonus.pop_back();
    }
}

//**************************
//Description : Actions performed when the listener is notified because an event occurred
//Parameters : None
//Return Value : None
//Note : Virtual because depends on the entity notified
//**************************
void CPlayer::Notify(sf::Event & _Event)
{
    //we pay attention to the notification only if we don't have to change player and if we are the current player
    if ( ms_bNextPlayer )
    {
        //we set the next player
        ms_iCurrentPlayer = (ms_iCurrentPlayer + 1 >= ms_iNbPlayer) ? 0 : (ms_iCurrentPlayer+1);
        ms_CurrentPlayer = ms_Players[ms_iCurrentPlayer];

        ms_bNextPlayer = false;
    }
    else
    {
        if ( this == ms_CurrentPlayer )
        {
            if ( _Event.Type == sf::Event::KeyPressed )
            {
                if ( _Event.Key.Code == sf::Key::Left )
                {
                    m_iCurrentColumn = (m_iCurrentColumn - 1 < 0) ? 0 : (m_iCurrentColumn-1);
                    m_Sprite->SetPosition(BOARD_X_ORIGIN+(m_iCurrentColumn*m_Sprite->GetWidth()), 0);
                }
                if ( _Event.Key.Code == sf::Key::Right )
                {
                    m_iCurrentColumn = (m_iCurrentColumn + 1 >= DEFAULT_NUM_COLUMNS) ? (DEFAULT_NUM_COLUMNS-1) : (m_iCurrentColumn+1);
                    m_Sprite->SetPosition(BOARD_X_ORIGIN+(m_iCurrentColumn*m_Sprite->GetWidth()), 0);
                }
                if ( _Event.Key.Code == sf::Key::Space )
                {
                    CBoard * CurrentBoard = CBoard::GetCurrentBoard();

                    if ( CurrentBoard->AddPawn(m_iCurrentColumn, m_iColor, m_PawnAnimation, this) != -1 )
                        ms_bNextPlayer = true;
                }
                if ( _Event.Key.Code == sf::Key::U )
                {
                    CBoard * CurrentBoard = CBoard::GetCurrentBoard();

                    //if we have a bonus we play it
                    if ( !m_ListBonus.empty() )
                    {
                        int iRowAdd = CurrentBoard->AddPawn(m_iCurrentColumn, m_iColor, m_PawnAnimation, this);

                        if ( iRowAdd != -1 )
                        {
                            //we get the bonus
                            IBonus * Bonus = m_ListBonus.front();

                            //we use it
                            Bonus->UseBonus(iRowAdd, m_iCurrentColumn, this);

                            //we don't need it anymore
                            delete Bonus;

                            m_ListBonus.erase(m_ListBonus.begin());

                            ms_bNextPlayer = true;
                        }
                    }
                    else
                    {
                        //if we don't have any bonus we just add a pawn
                        if ( CurrentBoard->AddPawn(m_iCurrentColumn, m_iColor, m_PawnAnimation, this) != -1 )
                            ms_bNextPlayer = true;
                    }
                }
            }
        }
    }
}

/*
*   Setters and Getters
*/

//**************************
// Sprite
//**************************
void CPlayer::SetSpritePlayer(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow)
{
    if ( m_Sprite == NULL )
    {
        m_Sprite = new CSprite(_Animation, _RenderWindow);

        m_Sprite->SetPosition(BOARD_X_ORIGIN, 0);

        m_RenderWindow = _RenderWindow;
    }
}

CSprite * CPlayer::GetSpritePlayer() const
{
    return m_Sprite;
}

//**************************
// Animation of a pawn
//**************************
void CPlayer::SetPawnAnimation(CSpriteAnimation * _Animation)
{
    m_PawnAnimation = _Animation;
}

CSpriteAnimation * CPlayer::GetPawnAnimation() const
{
    return m_PawnAnimation;
}

//**************************
// Current Player
//**************************
void CPlayer::SetCurrentPlayer(CPlayer * _CurrentPlayer)
{
    int i = 0;
    while ( i < ms_iCurrentPlayer && ms_Players[i] != _CurrentPlayer )
        i++;

    if ( i < ms_iNbPlayer )
    {
        ms_CurrentPlayer = _CurrentPlayer;
        ms_iNbPlayer = i;

        ms_bNextPlayer = false;
    }
}

CPlayer * CPlayer::GetCurrentPlayer()
{
    return ms_CurrentPlayer;
}

//**************************
// Next Player
//**************************
void CPlayer::SetNextPlayer()
{
    //we set the next player
    ms_iCurrentPlayer = (ms_iCurrentPlayer + 1 >= ms_iNbPlayer) ? 0 : (ms_iCurrentPlayer+1);
    ms_CurrentPlayer = ms_Players[ms_iCurrentPlayer];

    ms_bNextPlayer = false;
}

bool CPlayer::NextPlayer()
{
    return ms_bNextPlayer;
}

//**************************
//A player
//**************************
CPlayer * CPlayer::GetPlayer( int _iColor )
{
    //we consider that there is only one player with one color
    int i = 0;
    CPlayer * Player = NULL;

    while ( i < ms_iNbPlayer && ms_Players[i]->GetColor() != _iColor )
        i++;

    if ( i < ms_iNbPlayer )
        Player = ms_Players[i];

    return Player;
}

//**************************
// The color of the player
//**************************
void CPlayer::SetColor(int _iColor)
{
    m_iColor = _iColor;
}

int CPlayer::GetColor() const
{
    return m_iColor;
}

//**************************
//The score of the player
//**************************
void CPlayer::WinGame(int _iValue)
{
    m_iScore += _iValue;
}

int CPlayer::GetScore() const
{
    return m_iScore;
}

