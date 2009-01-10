#include "../include/CPawn.h"

//**************************
//Description : Constructor
//Parameters : None
//Note : None
//**************************
CPawn::CPawn()
    : ISquare(),
    m_iColor(RED)
{
}

//**************************
//Description : Constructor
//Parameters : The animation of the square, the Render Window and the color of the pawn
//Note : None
//**************************
CPawn::CPawn(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow, int _iColor)
    : ISquare(_Animation, _RenderWindow),
    m_iColor(_iColor)
{
}

//**************************
//Description : Destructor
//Parameters : None
//Note : None
//**************************
CPawn::~CPawn()
{
}

//**************************
//Description : Return if the square can collide with another entity or not
//Parameters : None
//Return value : true if the square can collide, otherwise false
//Note : A pawn can't collide with other entities
//**************************
bool CPawn::CanCollide()
{
    return false;
}

/*
*   Setters and Getters
*/

//**************************
// The color of the pawn
//**************************
void CPawn::SetColor(int _iColor)
{
    m_iColor = _iColor;
}

int CPawn::GetColor() const
{
    return m_iColor;
}
