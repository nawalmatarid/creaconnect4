#include "../include/CDoubleBonus.h"

#include "../include/CPawn.h"
#include "../include/CBoard.h"

//**************************
//Description : Constructor
//Parameters : None
//Note : None
//**************************
CDoubleBonus::CDoubleBonus()
    : IBonus()
{
}

//**************************
//Description : Constructor
//Parameters : The animation of the square and the Render Window
//Note : None
//**************************
CDoubleBonus::CDoubleBonus(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow)
    : IBonus(_Animation, _RenderWindow)
{
}

//**************************
//Description : Destructor
//Parameters : None
//Note : None
//**************************
CDoubleBonus::~CDoubleBonus()
{
}

//**************************
//Description : Activate the bonus
//Parameters : The row and the column where the pawn has been played
//              the player who played the bonus
//Return value : None
//Note : None
//**************************
void CDoubleBonus::UseBonus(int _iRow, int _iColumn, CPlayer * _Player)
{
    CBoard * CurrentBoard = CBoard::GetCurrentBoard();

    //we take the Pawn where the player play (we are sure that it's a Pawn because the player just put it)
    CPawn * Pawn = (CPawn *)CurrentBoard->GetSquare(_iRow, _iColumn);

    //we add a pawn at the previous row
    CurrentBoard->AddPawn(_iColumn, Pawn->GetColor(), Pawn->GetSprite()->GetAnimation(), _Player);
}

