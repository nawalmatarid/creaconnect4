#include "../include/IBonus.h"

//**************************
//Description : Constructor
//Parameters : None
//Note : None
//**************************
IBonus::IBonus()
    : ISquare(),
    m_bDiscovered(false)
{
}

//**************************
//Description : Constructor
//Parameters : The animation of the square and the Render Window
//Note : None
//**************************
IBonus::IBonus(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow)
    : ISquare(_Animation, _RenderWindow),
    m_bDiscovered(false)
{
    //we stop the animation of the sprite because at the beginning, the gift is undiscoverd
    m_Sprite->StopAnim();
}

//**************************
//Description : Destructor
//Parameters : None
//Note : None
//**************************
IBonus::~IBonus()
{
}

//**************************
//Description : Return if the square can collide with another entity or not
//Parameters : None
//Return value : true if the square can collide, otherwise false
//Note : A bonus can collide with other entities
//**************************
bool IBonus::CanCollide()
{
    return true;
}

/*
*   Setters and Getters
*/

//**************************
// The sprite
//**************************
void IBonus::SetSprite(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow)
{
    if ( m_Sprite == NULL )
        m_Sprite = new CSprite(_Animation, _RenderWindow);

    //the sprite of a bonus has 2 frame, but we don't animate it
    //we display the frame 0 when the bonus is not discovered
    //and we display the frame 1 when it is
    m_Sprite->StopAnim();
}

//**************************
// The boolean of the discovery
//**************************
void IBonus::SetDiscovered(bool _bDiscovered)
{
    m_bDiscovered = _bDiscovered;

    if ( m_bDiscovered )
        m_Sprite->SetDisplayedFrame(1);
    else
        m_Sprite->SetDisplayedFrame(0);
}

bool IBonus::GetDiscovered() const
{
    return m_bDiscovered;
}

