#include "../include/ISquare.h"

//**************************
//Description : Constructor
//Parameters : None
//Note : None
//**************************
ISquare::ISquare()
{
    m_Sprite = NULL;
}

//**************************
//Description : Constructor
//Parameters : The animation of the square and the Render Window
//Note : None
//**************************
ISquare::ISquare(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow)
{
    m_Sprite = new CSprite(_Animation, _RenderWindow);
}

//**************************
//Description : Destructor
//Parameters : None
//Note : None
//**************************
ISquare::~ISquare()
{
    if ( m_Sprite != NULL )
        delete m_Sprite;
}

//**************************
//Description : Display the square on the screen
//Parameters : the X and Y value for the display
//Return value : None
//Note : None
//**************************
void ISquare::DisplaySquare(int _iX, int _iY)
{
    m_Sprite->SetPosition(_iX, _iY);
    m_Sprite->Draw();
}

/*
*   Setters and Getters
*/

//**************************
// The Sprite
//**************************
void ISquare::SetSprite(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow)
{
    if ( m_Sprite == NULL )
        m_Sprite = new CSprite(_Animation, _RenderWindow);
}


CSprite * ISquare::GetSprite() const
{
    return m_Sprite;
}

