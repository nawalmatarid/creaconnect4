#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <string>

#define WINDOW_WIDTH 800		//width of the window
#define WINDOW_HEIGHT 600		//height of the window

#define DEFAULT_NUM_ROWS 6      //default number of rows
#define DEFAULT_NUM_COLUMNS 7   //default number of columns

#define BOARD_X_ORIGIN 155         // origin of the board (on x)
#define BOARD_Y_ORIGIN 180         // origin of the board (on y)

#define SCOREWIN 5      //score to win the game
#define NUM_COLOR 2             //number of color
#define NUM_BONUS 3             //number of bonus
#define NUM_REWARD 2             //number of rewards
#define BOARD_BONUS 3             //number of bonus on the board

//definition of constants for the surfaces
#define BACKGROUND 0
#define BOARD 1
#define BONUS 2
#define REWARD 3

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
const std::string szRewardDir( "data/reward/" );

const std::string szFont( "/usr/share/fonts/corefonts/arial.ttf" );

#endif
