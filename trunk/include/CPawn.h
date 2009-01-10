#ifndef CPAWN_H
#define CPAWN_H

#include "../include/ISquare.h"

//**************************
//Describe a pawn
//**************************
class CPawn : public ISquare
{
    private:
        int m_iColor;        //color of the pawn

    public:
        //**************************
		//Description : Constructor
		//Parameters : None
		//Note : None
		//**************************
        CPawn();

        //**************************
		//Description : Constructor
		//Parameters : The animation of the square, the Render Window and the color of the pawn
		//Note : None
		//**************************
        CPawn(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow, int _iColor);

        //**************************
		//Description : Destructor
		//Parameters : None
		//Note : None
		//**************************
        virtual ~CPawn();

        //**************************
		//Description : Return if the square can collide with another entity or not
		//Parameters : None
		//Return value : true if the square can collide, otherwise false
		//Note : A pawn can't collide with other entities
		//**************************
        virtual bool CanCollide();

        /*
        *   Setters and Getters
        */

        //**************************
		//The color of the pawn
		//**************************
        void SetColor(int _iColor);

        int GetColor() const;
};

#endif

