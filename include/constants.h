#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <string>

#define WINDOW_WIDTH 800		//width of the window
#define WINDOW_HEIGHT 600		//height of the window

#define DEFAULT_NUM_ROWS 6      //default number of rows
#define DEFAULT_NUM_COLUMNS 7   //default number of columns

#define BOARD_X_ORIGIN 155         // origin of the board (on x)
#define BOARD_Y_ORIGIN 180         // origin of the board (on y)

#define NUM_COLOR 2             //number of color
#define NUM_BONUS 3             //number of bonus
#define BOARD_BONUS 3             //number of bonus on the board

//definition of constants for the surfaces
#define BACKGROUND 1
#define BOARD 2

    enum PAWN_COLOR { RED = 10, ORANGE };
    enum TYPE_BONUS { DOUBLE = 20, BOMB, SWAP };


const std::string szPawnColorDir[NUM_COLOR] = { "RED",
                                            "ORANGE" };
const std::string szTypeBonusDir[NUM_BONUS] = { "DOUBLE",
                                            "BOMB",
                                            "SWAP" };

const std::string szBgDir( "data/bg/" );
const std::string szBoardDir( "data/board/" );
const std::string szPawnDir( "data/pawn/" );
const std::string szBonusDir( "data/bonus/" );

#endif
