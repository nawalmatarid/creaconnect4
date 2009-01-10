#ifndef CBOMBBONUS_H
#define CBOMBBONUS_H

#include "../include/IBonus.h"

//**************************
//Bonus that delete all pawns in the board around the square where this bonus is played
//**************************
class CBombBonus : public IBonus
{
    public:
        //**************************
		//Description : Constructor
		//Parameters : None
		//Note : None
		//**************************
        CBombBonus();

        //**************************
		//Description : Constructor
		//Parameters : The animation of the square and the Render Window
		//Note : None
		//**************************
        CBombBonus(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow);

        //**************************
		//Description : Destructor
		//Parameters : None
		//Note : None
		//**************************
        virtual ~CBombBonus();

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



