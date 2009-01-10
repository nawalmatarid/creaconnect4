#ifndef CDOUBLEBONUS_H
#define CDOUBLEBONUS_H

#include "../include/IBonus.h"


//**************************
//Play two pawn at the same column
//**************************
class CDoubleBonus : public IBonus
{
    public:
        //**************************
		//Description : Constructor
		//Parameters : None
		//Note : None
		//**************************
        CDoubleBonus();

        //**************************
		//Description : Constructor
		//Parameters : The animation of the square and the Render Window
		//Note : None
		//**************************
        CDoubleBonus(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow);

        //**************************
		//Description : Destructor
		//Parameters : None
		//Note : None
		//**************************
        virtual ~CDoubleBonus();

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


