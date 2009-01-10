#ifndef IBonus_H
#define IBonus_H

#include "../include/ISquare.h"

class CPlayer;

//**************************
//Interface to describe a bonus
//**************************
class IBonus : public ISquare
{
    private:
        bool m_bDiscovered;             //true if the bonus has been discovered (taken) by a player, otherwise false

    public:
        //**************************
		//Description : Constructor
		//Parameters : None
		//Note : None
		//**************************
        IBonus();

        //**************************
		//Description : Constructor
		//Parameters : The animation of the square and the Render Window
		//Note : None
		//**************************
        IBonus(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow);

        //**************************
		//Description : Destructor
		//Parameters : None
		//Note : None
		//**************************
        virtual ~IBonus();

        //**************************
		//Description : Return if the square can collide with another entity or not
		//Parameters : None
		//Return value : true if the square can collide, otherwise false
		//Note : A bonus can collide with other entities
		//**************************
        virtual bool CanCollide();

        //**************************
		//Description : Activate the bonus
		//Parameters : The row and the column where the pawn has been played
		//              the player who played the bonus
		//Return value : None
		//Note : None
		//**************************
        virtual void UseBonus(int _iRow, int _iColumn, CPlayer * _Player) = 0;

        /*
        *   Setters and Getters
        */

        //**************************
		// The sprite
		//**************************
        virtual void SetSprite(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow);

		//**************************
		// The boolean of the discovery
		//**************************
		void SetDiscovered(bool _bDiscovered);

		bool GetDiscovered() const;
};

#endif


