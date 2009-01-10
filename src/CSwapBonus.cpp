#include "../include/CSwapBonus.h"

#include "../include/ISquare.h"
#include "../include/CPawn.h"
#include "../include/CBoard.h"

//**************************
//Description : Constructor
//Parameters : None
//Note : None
//**************************
CSwapBonus::CSwapBonus()
    : IBonus()
{
}

//**************************
//Description : Constructor
//Parameters : The animation of the square and the Render Window
//Note : None
//**************************
CSwapBonus::CSwapBonus(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow)
    : IBonus(_Animation, _RenderWindow)
{
}

//**************************
//Description : Destructor
//Parameters : None
//Note : None
//**************************
CSwapBonus::~CSwapBonus()
{
}

//**************************
//Description : Activate the bonus
//Parameters : The row and the column where the pawn has been played
//              the player who played the bonus
//Return value : None
//Note : None
//**************************
void CSwapBonus::UseBonus(int _iRow, int _iColumn, CPlayer * _Player)
{
    CBoard * CurrentBoard = CBoard::GetCurrentBoard();

    //we change if we are not already to the end of the board
    if ( _iRow < (DEFAULT_NUM_ROWS-1) )
    {
        //we take the pawn
        ISquare * TempUp = CurrentBoard->GetSquare(_iRow, _iColumn);
        ISquare * TempDown = CurrentBoard->GetSquare(_iRow+1, _iColumn);

        //we change the pawn
        CurrentBoard->SetSquare(_iRow, _iColumn, TempDown);
        CurrentBoard->SetSquare(_iRow+1, _iColumn, TempUp);

        //we check if the player win with this move
        if ( CurrentBoard->CheckWinner(_iRow+1, _iColumn) )
        {
            CurrentBoard->SetLine( true );
            _Player->WinGame();
        }

        //we check if the other player win with this move
        if ( CurrentBoard->CheckWinner(_iRow, _iColumn) )
        {
            CurrentBoard->SetLine( true );
            CPlayer::GetPlayer(((CPawn *)CurrentBoard->GetSquare(_iRow, _iColumn))->GetColor())->WinGame();
        }
    }
}


