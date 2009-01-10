#ifndef CBONUSFACTORY_H
#define CBONUSFACTORY_H

#include "../include/IBonus.h"

//**************************
//Factory to create bonus
//**************************
class CBonusFactory
{
    public:
        //**************************
		//Description : Create a bonus
		//Parameters : The type of bonus
		//Return value : The bonus newly created
		//Note : None
		//**************************
        static IBonus * CreateBonus(int _iTypeBonus);
};

#endif





