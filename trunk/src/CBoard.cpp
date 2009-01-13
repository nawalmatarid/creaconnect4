#include "../include/CBoard.h"
#include "../include/CBonusFactory.h"
#include "../include/CPawn.h"

#include <SFML/System/Randomizer.hpp>

CBoard * CBoard::ms_CurrentBoard = NULL;        //static pointer toward the current board in game

//**************************
//Description : Constructor
//Parameters : None
//Note : None
//**************************
CBoard::CBoard()
    : m_bLine(false)
{
    m_Sprite = NULL;
    m_RenderWindow = NULL;

    ms_CurrentBoard = this;

    for (int i = 0; i < DEFAULT_NUM_COLUMNS; i ++)
    {
        for (int j = 0; j < DEFAULT_NUM_ROWS; j++)
        {
            m_Board[i][j] = NULL;
        }
    }

    CreateBoard();
}

//**************************
//Description : Constructor
//Parameters : The animation of a square of the board and the Render Window
//Note : None
//**************************
CBoard::CBoard(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow)
    : m_bLine(false)
{
    m_Sprite = new CSprite(_Animation, _RenderWindow);

    m_RenderWindow = _RenderWindow;

    ms_CurrentBoard = this;

    for (int i = 0; i < DEFAULT_NUM_COLUMNS; i ++)
    {
        for (int j = 0; j < DEFAULT_NUM_ROWS; j++)
        {
            m_Board[i][j] = NULL;
        }
    }

    CreateBoard();
}


//**************************
//Description : Destructor
//Parameters : None
//Note : None
//**************************
CBoard::~CBoard()
{
    if ( m_Sprite != NULL )
        delete m_Sprite;

    for (int i = 0; i < DEFAULT_NUM_COLUMNS; i ++)
    {
        for (int j = 0; j < DEFAULT_NUM_ROWS; j++)
        {
            if ( m_Board[i][j] != NULL )
                delete m_Board[i][j];
        }
    }

    ms_CurrentBoard = NULL;
}

//**************************
//Description : Create the board
//Parameters : None
//Return value : None
//Note : None
//**************************
void CBoard::CreateBoard()
{
    m_bLine = false;

    for (int i = 0; i < DEFAULT_NUM_COLUMNS; i ++)
    {
        for (int j = 0; j < DEFAULT_NUM_ROWS; j++)
        {
            if ( m_Board[i][j] != NULL )
            {
                delete m_Board[i][j];
                m_Board[i][j] = NULL;
            }
        }
    }

    int iColumn, iRow, iTypeBonus;

    for (int i = 0; i < BOARD_BONUS; i++)
    {
        iColumn = sf::Randomizer::Random(0, DEFAULT_NUM_COLUMNS-1);
        iRow = sf::Randomizer::Random(0, DEFAULT_NUM_ROWS-1);

        iTypeBonus = sf::Randomizer::Random(DOUBLE, DOUBLE+NUM_BONUS-1);

        if ( m_Board[iColumn][iRow] == NULL )
            m_Board[iColumn][iRow] = CBonusFactory::CreateBonus(iTypeBonus);
        else
            i--;
    }
}

//**************************
//Description : Return whether the board is full or not
//Parameters : None
//Return value : True if the board is full, otherwise false
//Note : None
//**************************
bool CBoard::BoardFull()
{
	bool bFull = true;
	int i = 0;

	while ( i < DEFAULT_NUM_COLUMNS && bFull )
	{
		bFull = (m_Board[i][0] != NULL && !m_Board[i][0]->CanCollide() );

		i++;
	}

	return bFull;
}

//**************************
//Description : Display the board on the screen
//Parameters : None
//Return value : None
//Note : None
//**************************
void CBoard::DisplayBoard()
{
    int w = m_Sprite->GetWidth();
    int h = m_Sprite->GetHeight();

    for (int i = 0; i < DEFAULT_NUM_COLUMNS; i++)
    {
        for (int j = 0; j < DEFAULT_NUM_ROWS; j++)
        {
            if ( m_Board[i][j] != NULL )
                m_Board[i][j]->DisplaySquare( (BOARD_X_ORIGIN + i * w), (BOARD_Y_ORIGIN + j * h) );

            m_Sprite->SetPosition( (BOARD_X_ORIGIN + i * w), (BOARD_Y_ORIGIN + j * h) );
            m_Sprite->Draw();
        }
    }
}

//**************************
//Description : Check if there is a line done with the square at (_iX, _iY)
//Parameters : the coordinates of the pawn (_iX, _iY)
//Return value : true if a line is done, otherwise false
//Note : This function will be called with the last move done
//**************************
bool CBoard::CheckWinner(int _iRow, int _iColumn) const
{
    if ( _iRow >= 0 && _iRow < DEFAULT_NUM_ROWS
        && _iColumn >= 0 && _iColumn < DEFAULT_NUM_COLUMNS
        && m_Board[_iColumn][_iRow] != NULL && !m_Board[_iColumn][_iRow]->CanCollide() )
    {
        int iColorPawn = ((CPawn *)m_Board[_iColumn][_iRow])->GetColor();

        //there is a winner if there is a line diagonally, horizontaly or verticaly
        if ( CheckHorizontal(_iRow, _iColumn, iColorPawn) )
            return true;
        else if ( CheckVertical(_iRow, _iColumn, iColorPawn) )
            return true;
        else if ( CheckDiagonal_NE_SW(_iRow, _iColumn, iColorPawn) )
            return true;
        else if ( CheckDiagonal_NW_SE(_iRow, _iColumn, iColorPawn) )
            return true;
        else
            return false;
    }
    else
        return false;
}

//**************************
//Description : Check if there is a line done horizontaly
//Parameters : the coordinates of the pawn (_iX, _iY), and its color
//Return value : true if a line is done, otherwise false
//Note : None
//**************************
bool CBoard::CheckHorizontal(int _iRow, int _iColumn, int _iColowPawn) const
{
    int iScore = 1;  //we begin with 1 becaus of the pawn we are on
    int iCount = 1;

    while( _iColumn + iCount < DEFAULT_NUM_COLUMNS )
    {
        //we can continue if the square is not NULL, if we can't collide (it's a pawn) and if the color is the same
        if (m_Board[_iColumn+iCount][_iRow] != NULL
            && !m_Board[_iColumn+iCount][_iRow]->CanCollide()
            && ((CPawn *)m_Board[_iColumn+iCount][_iRow])->GetColor() == _iColowPawn)  //Check from the pawn to right
        {
            iScore++;
            iCount++;
        }
        else
            break;  //If no combo is detected break from the loop
    }

    iCount = 1;
    while( _iColumn - iCount >= 0 )
    {
        //we can continue if the square is not NULL, if we can't collide (it's a pawn) and if the color is the same
        if (m_Board[_iColumn-iCount][_iRow] != NULL
            && !m_Board[_iColumn-iCount][_iRow]->CanCollide()
            && ((CPawn *)m_Board[_iColumn-iCount][_iRow])->GetColor() == _iColowPawn)  //Check from the pawn to left
        {
            iScore++;
            iCount++;
        }
        else
            break;  //If no combo is detected break from the loop
    }

    if (iScore >= 4)
        return true;
    else
        return false;
}

//**************************
//Description : Check if there is a line done verticaly
//Parameters : the coordinates of the pawn (_iX, _iY), and its color
//Return value : true if a line is done, otherwise false
//Note : None
//**************************
bool CBoard::CheckVertical(int _iRow, int _iColumn, int _iColowPawn) const
{
    int iScore = 1;  //we begin with 1 becaus of the pawn we are on
    int iCount = 1;

    while( _iRow + iCount < DEFAULT_NUM_ROWS )
    {
        //we can continue if the square is not NULL, if we can't collide (it's a pawn) and if the color is the same
        if (m_Board[_iColumn][_iRow+iCount] != NULL
            && !m_Board[_iColumn][_iRow+iCount]->CanCollide()
            && ((CPawn *)m_Board[_iColumn][_iRow+iCount])->GetColor() == _iColowPawn)  //Check from the pawn to Down
        {
            iScore++;
            iCount++;
        }
        else
            break;  //If no combo is detected break from the loop
    }

    iCount = 1;
    while( _iRow - iCount >= 0 )
    {
        //we can continue if the square is not NULL, if we can't collide (it's a pawn) and if the color is the same
        if (m_Board[_iColumn][_iRow-iCount] != NULL
            && !m_Board[_iColumn][_iRow-iCount]->CanCollide()
            && ((CPawn *)m_Board[_iColumn][_iRow-iCount])->GetColor() == _iColowPawn)  //Check from the pawn to Up
        {
            iScore++;
            iCount++;
        }
        else
            break;  //If no combo is detected break from the loop
    }

    if (iScore >= 4)
        return true;
    else
        return false;
}

//**************************
//Description : Check if there is a line done in diagonal from NW to SE
//Parameters : the coordinates of the pawn (_iX, _iY), and its color
//Return value : true if a line is done, otherwise false
//Note : None
//**************************
bool CBoard::CheckDiagonal_NW_SE(int _iRow, int _iColumn, int _iColowPawn) const
{
    int iScore = 1;  //we begin with 1 becaus of the pawn we are on
    int iCount = 1;

    while( (_iColumn + iCount < DEFAULT_NUM_COLUMNS) && (_iRow + iCount < DEFAULT_NUM_ROWS))
    {
        //we can continue if the square is not NULL, if we can't collide (it's a pawn) and if the color is the same
        if (m_Board[_iColumn+iCount][_iRow+iCount] != NULL
            && !m_Board[_iColumn+iCount][_iRow+iCount]->CanCollide()
            && ((CPawn *)m_Board[_iColumn+iCount][_iRow+iCount])->GetColor() == _iColowPawn)  //Check from the pawn to SE
        {
            iScore++;
            iCount++;
        }
        else
            break;  //If no combo is detected break from the loop
    }

    iCount = 1;
    while( (_iColumn - iCount >= 0) && (_iRow - iCount >= 0))
    {
        //we can continue if the square is not NULL, if we can't collide (it's a pawn) and if the color is the same
        if (m_Board[_iColumn-iCount][_iRow-iCount] != NULL
            && !m_Board[_iColumn-iCount][_iRow-iCount]->CanCollide()
            && ((CPawn *)m_Board[_iColumn-iCount][_iRow-iCount])->GetColor() == _iColowPawn)  //Check from the pawn to NW
        {
            iScore++;
            iCount++;
        }
        else
            break;  //If no combo is detected break from the loop
    }

    if (iScore >= 4)
        return true;
    else
        return false;
}

//**************************
//Description : Check if there is a line done in diagonal from NE to SW
//Parameters : the coordinates of the pawn (_iX, _iY), and its color
//Return value : true if a line is done, otherwise false
//Note : None
//**************************
bool CBoard::CheckDiagonal_NE_SW(int _iRow, int _iColumn, int _iColowPawn) const
{
        int iScore = 1;  //we begin with 1 becaus of the pawn we are on
    int iCount = 1;

    while( (_iColumn - iCount >= 0) && (_iRow + iCount < DEFAULT_NUM_ROWS))
    {
        //we can continue if the square is not NULL, if we can't collide (it's a pawn) and if the color is the same
        if (m_Board[_iColumn-iCount][_iRow+iCount] != NULL
            && !m_Board[_iColumn-iCount][_iRow+iCount]->CanCollide()
            && ((CPawn *)m_Board[_iColumn-iCount][_iRow+iCount])->GetColor() == _iColowPawn)  //Check from the pawn to NE
        {
            iScore++;
            iCount++;
        }
        else
            break;  //If no combo is detected break from the loop
    }

    iCount = 1;
    while( (_iColumn + iCount < DEFAULT_NUM_COLUMNS) && (_iRow - iCount >= 0))
    {
        //we can continue if the square is not NULL, if we can't collide (it's a pawn) and if the color is the same
        if (m_Board[_iColumn+iCount][_iRow-iCount] != NULL
            && !m_Board[_iColumn+iCount][_iRow-iCount]->CanCollide()
            && ((CPawn *)m_Board[_iColumn+iCount][_iRow-iCount])->GetColor() == _iColowPawn)  //Check from the pawn to SW
        {
            iScore++;
            iCount++;
        }
        else
            break;  //If no combo is detected break from the loop
    }

    if (iScore >= 4)
        return true;
    else
        return false;
}

//**************************
//Description : Add (if possible), a pawn of the given color in the given column
//Parameters : The column where we want the pawn
//              the color of the pawn
//              the animation for the pawn
//              the player who play
//Return value : The number of the row where the pawn is, -1 if we can't add a pawn
//Note : None
//**************************
int CBoard::AddPawn(int _iColumn, int _iColorPawn, CSpriteAnimation * _PawnAnimation, CPlayer * _Player)
{
     int iFinalRow = -1;

    //we can't add pawn if there is a line
    if ( !m_bLine )
    {
        bool bStop = false;

        //we stop when we pass the last row or when we find a suitable row (NULL or with a bonus)
        while ( iFinalRow < (DEFAULT_NUM_ROWS - 1) && !bStop )
        {
            //if the next case is not empty or is not a bonus, we stop
            if ( m_Board[_iColumn][iFinalRow+1] != NULL && !m_Board[_iColumn][iFinalRow+1]->CanCollide() )
                bStop = true;
            else
                iFinalRow++;
        }

        //if we pass all the row, this column doesn't have any pawn or bonus
        if (iFinalRow >= 0)
        {
            //if the square we are on is not null, it means that it's a bonus
            if ( m_Board[_iColumn][iFinalRow] != NULL  )
            {
                _Player->GainBonus((IBonus *)m_Board[_iColumn][iFinalRow]);

                m_Board[_iColumn][iFinalRow] = NULL;
            }

            m_Board[_iColumn][iFinalRow] = new CPawn(_PawnAnimation, m_RenderWindow, _iColorPawn);

            //we test if there is a winner
            m_bLine = CheckWinner(iFinalRow, _iColumn);
        }
        //else we are out of the board
        else
            iFinalRow = -1;

        if ( m_bLine )
            _Player->WinGame();
    }

    return iFinalRow;
}

//**************************
//Description : Put all pawn to the far end of the board (happen when a bomb make holes)
//Parameters : None
//Return value : None
//Note : None
//**************************
void CBoard::DownPawn()
{
    int j;

    for (int i = 0; i < DEFAULT_NUM_COLUMNS; i++)
    {
        j = DEFAULT_NUM_ROWS-1;

        //we look for the first square NULL
        while (j >= 0 && m_Board[i][j] != NULL)
            j--;

        //then we search the non NULL square and put them down
        for (int k = j-1; k >= 0; k--)
        {
            if ( m_Board[i][k] != NULL && !m_Board[i][k]->CanCollide() )
            {
                m_Board[i][j] = m_Board[i][k];
                m_Board[i][k] = NULL;

                j--;
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
void CBoard::SetSpriteBoard(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow)
{
    if ( m_Sprite == NULL )
    {
        m_Sprite = new CSprite(_Animation, _RenderWindow);

        m_RenderWindow = _RenderWindow;
    }
}

CSprite * CBoard::GetSpriteBoard() const
{
    return m_Sprite;
}

//**************************
// Current Board
//**************************
CBoard * CBoard::GetCurrentBoard()
{
    return ms_CurrentBoard;
}

//**************************
// Square
//**************************
void CBoard::SetSquare(int _iRow, int _iColumn, ISquare * _Square)
{
    if ( _iRow >= 0 && _iRow < DEFAULT_NUM_ROWS
        && _iColumn >= 0 && _iColumn < DEFAULT_NUM_COLUMNS )
        m_Board[_iColumn][_iRow] = _Square;
}

ISquare * CBoard::GetSquare(int _iRow, int _iColumn) const
{
    if ( _iRow >= 0 && _iRow < DEFAULT_NUM_ROWS
        && _iColumn >= 0 && _iColumn < DEFAULT_NUM_COLUMNS )
        return m_Board[_iColumn][_iRow];
    else
        return NULL;
}

//**************************
// Existing lines
//**************************
void CBoard::SetLine(bool _bLine)
{
    m_bLine = _bLine;
}

bool CBoard::ExistLine() const
{
    return m_bLine;
}
