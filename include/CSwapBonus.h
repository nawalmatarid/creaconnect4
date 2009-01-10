#ifndef CSWAPBONUS_H
#define CSWAPBONUS_H

#include "../include/IBonus.h"


//**************************
//Swap the pawn played and the pawn below
//**************************
class CSwapBonus : public IBonus
{
    public:
        //**************************
		//Description : Constructor
		//Parameters : None
		//Note : None
		//**************************
        CSwapBonus();

        //**************************
		//Description : Constructor
		//Parameters : The animation of the square and the Render Window
		//Note : None
		//**************************
        CSwapBonus(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow);

        //**************************
		//Description : Destructor
		//Parameters : None
		//Note : None
		//**************************
        virtual ~CSwapBonus();

        //**************************
		//Description : Activate the bonus
		//Parameters : The row and the column where the pawn has been played
		//              the player who played the bonus
		//Return value : None
		//Note : None
		//**************************
        virtual void UseBonus(int _iRow, int _iColumn, CPlayer * _Player);
};

#endif



