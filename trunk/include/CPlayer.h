#ifndef CPLAYER_H
#define CPLAYER_H

#include "../include/constants.h"

#include <vector>
#include <list>

#include "../include/IEventObserver.h"
#include "../include/IBonus.h"

//**************************
//Manage a player
//**************************
class CPlayer : public IEventObserver
{
    private:
        int m_iColor;           //color of the player

        int m_iCurrentColumn;   //current column where the player is

        int m_iScore;           //score of the player

        std::vector<IBonus *> m_ListBonus;     //list of the bonus the player have

        CSprite * m_Sprite;       //sprite to display a square of the board

        CSpriteAnimation * m_PawnAnimation;     //animation of the pawn corresponding to this player

        sf::RenderWindow * m_RenderWindow;        //the render window

        static CPlayer * ms_Players[NUM_COLOR];        //static array wich contain all the players (there are as many players as colors)
        static int ms_iNbPlayer;        //static number of players
        static CPlayer * ms_CurrentPlayer;        //static pointer toward the current player in game
        static int ms_iCurrentPlayer;        //static number of the current player
        static bool ms_bNextPlayer;        //static boolean to know if we have to change player or not

    public:
        //**************************
		//Description : Constructor
		//Parameters : None
		//Note : None
		//**************************
        CPlayer();

        //**************************
		//Description : Constructor
		//Parameters : The animation of a pawn, the RenderWindow
        //              the color of the player
		//Note : None
		//**************************
        CPlayer(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow, int _iColor);

        //**************************
		//Description : Destructor
		//Parameters : None
		//Note : None
		//**************************
        virtual ~CPlayer();

        //**************************
		//Description : Display the player on the screen
		//Parameters : None
		//Return value : None
		//Note : None
		//**************************
        void DisplayPlayer();

        //**************************
		//Description : The player gain a bonus
		//Parameters : the bonus gained
		//Return value : None
		//Note : None
		//**************************
        void GainBonus(IBonus * _Bonus);

        //**************************
		//Description : The player lose all of this bonus
		//Parameters : None
		//Return value : None
		//Note : This is usually due to an restart of the game, but maybe if we create a new bonus... ^^
		//**************************
        void LoseBonus();

        //**************************
        //Description : Actions performed when the listener is notified because an event occurred
        //Parameters : None
        //Return Value : None
        //Note : Virtual because depends on the entity notified
        //**************************
        virtual void Notify(sf::Event & _Event);

        /*
        *   Setters and Getters
        */

		//**************************
		// Sprite
		//**************************
		void SetSpritePlayer(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow);

		CSprite * GetSpritePlayer() const;

		//**************************
		// Animation of a pawn
		//**************************
		void SetPawnAnimation(CSpriteAnimation * _Animation);

		CSpriteAnimation * GetPawnAnimation() const;

		//**************************
		// Current Player
		//**************************
		static void SetCurrentPlayer(CPlayer * _CurrentPlayer);

		static CPlayer * GetCurrentPlayer();

		//**************************
		// Next Player
		//**************************
		static void SetNextPlayer();

		static bool NextPlayer();

		//**************************
		//A player
		//**************************
		static CPlayer * GetPlayer( int _iColor );

        //**************************
		//The color of the player
		//**************************
        void SetColor(int _iColor);

        int GetColor() const;

        //**************************
		//The score of the player
		//**************************
		void WinGame(int _iValue = 1);

		int GetScore() const;
};

#endif





