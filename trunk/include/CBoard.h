#ifndef CBOARD_H
#define CBOARD_H

#include "../include/constants.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "../include/CSprite.h"
#include "../include/ISquare.h"
#include "../include/CPlayer.h"

//**************************
//Manage the board of the game
//**************************
class CBoard
{
    private:
        ISquare * m_Board[DEFAULT_NUM_COLUMNS][DEFAULT_NUM_ROWS];      //the board

        bool m_bLine;   //boolean to know if there is lines or not

        CSprite * m_Sprite;       //sprite to display a square of the board

        sf::RenderWindow * m_RenderWindow;        //the render window

        static CBoard * ms_CurrentBoard;        //static pointer toward the current board in game

    public:
        //**************************
		//Description : Constructor
		//Parameters : None
		//Note : None
		//**************************
        CBoard();

        //**************************
		//Description : Constructor
		//Parameters : The animation of a square of the board and the RenderWindow
		//Note : None
		//**************************
        CBoard(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow);

        //**************************
		//Description : Destructor
		//Parameters : None
		//Note : None
		//**************************
        virtual ~CBoard();

        //**************************
		//Description : Create the board
		//Parameters : None
		//Return value : None
		//Note : None
		//**************************
        void CreateBoard();

        //**************************
		//Description : Display the board on the screen
		//Parameters : None
		//Return value : None
		//Note : None
		//**************************
        void DisplayBoard();

        //**************************
		//Description : Check if there is a line done with the square at (_iX, _iY)
		//Parameters : the coordinates of the pawn (_iRow, _iColumn)
		//Return value : true if a line is done, otherwise false
		//Note : This function will be called with the last move done
		//**************************
        bool CheckWinner(int _iRow, int _iColumn) const;

        //**************************
		//Description : Check if there is a line done horizontaly
		//Parameters : the coordinates of the pawn (_iRow, _iColumn), and its color
		//Return value : true if a line is done, otherwise false
		//Note : None
		//**************************
        bool CheckHorizontal(int _iRow, int _iColumn, int _iColowPawn) const;

        //**************************
		//Description : Check if there is a line done verticaly
		//Parameters : the coordinates of the pawn (_iRow, _iColumn), and its color
		//Return value : true if a line is done, otherwise false
		//Note : None
		//**************************
        bool CheckVertical(int _iRow, int _iColumn, int _iColowPawn) const;

        //**************************
		//Description : Check if there is a line done in diagonal from NW to SE
		//Parameters : the coordinates of the pawn (_iRow, _iColumn), and its color
		//Return value : true if a line is done, otherwise false
		//Note : None
		//**************************
        bool CheckDiagonal_NW_SE(int _iRow, int _iColumn, int _iColowPawn) const;

        //**************************
		//Description : Check if there is a line done in diagonal from NE to SW
		//Parameters : the coordinates of the pawn (_iRow, _iColumn), and its color
		//Return value : true if a line is done, otherwise false
		//Note : None
		//**************************
        bool CheckDiagonal_NE_SW(int _iRow, int _iColumn, int _iColowPawn) const;

        //**************************
		//Description : Add (if possible), a pawn of the given color in the given column
		//Parameters : The column where we want the pawn
		//              the color of the pawn
		//              the animation for the pawn
		//              the player who play
		//Return value : The number of the row where the pawn is, -1 if we can't add a pawn
		//Note : None
		//**************************
        int AddPawn(int _iColumn, int _iColorPawn, CSpriteAnimation * _PawnAnimation, CPlayer * _Player);

        //**************************
		//Description : Put all pawn to the far end of the board (happen when a bomb make holes)
		//Parameters : None
		//Return value : None
		//Note : None
		//**************************
        void DownPawn();

        /*
        *   Setters and Getters
        */

		//**************************
		// Sprite
		//**************************
		void SetSpriteBoard(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow);

		CSprite * GetSpriteBoard() const;

		//**************************
		// Current Board
		//**************************
		static CBoard * GetCurrentBoard();

		//**************************
		// Square
		//**************************
		void SetSquare(int _iRow, int _iColumn, ISquare * _Square);

		ISquare * GetSquare(int _iRow, int _iColumn) const;

		//**************************
		// Existing lines
		//**************************
		void SetLine(bool _bLine);

		bool ExistLine() const;
};

#endif




