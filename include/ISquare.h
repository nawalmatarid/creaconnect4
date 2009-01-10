#ifndef ISQUARE_H
#define ISQUARE_H

#include "../include/constants.h"

#include "../include/CSprite.h"

//**************************
//Interface to describe a square in a board
//**************************
class ISquare
{
    protected:
        CSprite * m_Sprite;     //Sprite of the square

    public:
        //**************************
		//Description : Constructor
		//Parameters : None
		//Note : None
		//**************************
        ISquare();

        //**************************
		//Description : Constructor
		//Parameters : The animation of the square and the Render Window
		//Note : None
		//**************************
        ISquare(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow);

        //**************************
		//Description : Destructor
		//Parameters : None
		//Note : None
		//**************************
        virtual ~ISquare();

        //**************************
		//Description : Display the square on the screen
		//Parameters : the X and Y value for the display
		//Return value : None
		//Note : None
		//**************************
        void DisplaySquare(int _iX, int _iY);

        //**************************
		//Description : Return if the square can collide with another entity or not
		//Parameters : None
		//Return value : true if the square can collide, otherwise false
		//Note : None
		//**************************
        virtual bool CanCollide() = 0;

        /*
        *   Setters and Getters
        */

        //**************************
		// The Sprite
		//**************************
        virtual void SetSprite(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow);

        CSprite * GetSprite() const;
};

#endif
