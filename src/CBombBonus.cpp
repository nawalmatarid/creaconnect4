#include "../include/CBombBonus.h"

#include "../include/CBoard.h"
#include "../include/ISquare.h"
#include "../include/CPawn.h"

//**************************
//Description : Constructor
//Parameters : None
//Note : None
//**************************
CBombBonus::CBombBonus()
    : IBonus()
{
}

//**************************
//Description : Constructor
//Parameters : The animation of the square and the Render Window
//Note : None
//**************************
CBombBonus::CBombBonus(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow)
    : IBonus(_Animation, _RenderWindow)
{
}

//**************************
//Description : Destructor
//Parameters : None
//Note : None
//**************************
CBombBonus::~CBombBonus()
{
}

//**************************
//Description : Activate the bonus
//Parameters : The row and the column where the pawn has been played
//              the player who played the bonus
//Return value : None
//Note : None
//**************************
void CBombBonus::UseBonus(int _iRow, int _iColumn, CPlayer * _Player)
{
    CBoard * CurrentBoard = CBoard::GetCurrentBoard();
    ISquare * Square = NULL;

    //if the player win with this move, we  undo this victory because this move will destroy it
    if ( CurrentBoard->ExistLine() )
    {
        CurrentBoard->SetLine(false);
        _Player->WinGame(-1);
    }

    for (int i = (_iColumn - 1); i <= (_iColumn + 1); i++)
    {
        for (int j = (_iRow - 1); j <= (_iRow + 1); j++)
        {
            Square = CurrentBoard->GetSquare(j, i);

            if ( Square != NULL )
            {
                delete Square;
                CurrentBoard->SetSquare(j, i, NULL);
            }
        }
    }

    CurrentBoard->DownPawn();

    /*int MaxRow = (_iRow >= DEFAULT_NUM_ROWS-1) ? DEFAULT_NUM_ROWS : (_iRow+2);

    //we check if we don't make win a player
    for (int i = (_iColumn - 1); i < (_iColumn + 1); i++)
    {
        for (int j = 0; j < MaxRow; j++)
        {
            ISquare * Square = CurrentBoard->GetSquare(j, i);

            if ( Square != NULL && !Square->CanCollide() )
            {
                CPawn * Pawn = (CPawn *)CurrentBoard->GetSquare(j, i);

                if ( CurrentBoard->CheckWinner(j, i) )
                {
                    CurrentBoard->SetLine(true);
                    CPlayer::GetPlayer(Pawn->GetColor())->WinGame();
                }
            }
        }
    }*/
}


