#ifndef CSPRITE_H
#define CSPRITE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "../include/CSpriteAnimation.h"

//**************************
//Manage interactions between the animation and the RenderWindow
//**************************
class CSprite : public sf::Sprite
{
    private:
        int m_iDisplayedFrame;	//Number of the displayed frame

        int m_iRemainingLoops;  //Number of loops to do

        bool m_bAnimating;	//True if the sprite is currently animating, otherwise false

        bool m_bDrawn;	//True if the sprite has been drawn once on the RenderWindow, otherwise false

        bool m_bReverseAnim; //True if the animation has to be drawn in reverse order

        float m_lLastUpdate;	//Time when the sprite has been last updated

        float m_fSpeed;	//Speed of the animation

        sf::RenderWindow * m_RenderWindow;	//RenderWindow surface

        CSpriteAnimation * m_SpriteAnimation;	//A pointer toward the animations


    public:
        //**************************
        //Description : Constructor
        //Parameters : None
        //Note : None
        //**************************
        CSprite();

        //**************************
        //Description : Constructor
        //Parameters : The animation for the sprite, and a pointer on the RenderWindow
        //Note : None
        //**************************
        CSprite(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow);

        //**************************
        //Description : Copy Constructor
        //Parameters : A CSprite
        //Note : None
        //**************************
        CSprite(CSprite & _Sprite);

        //**************************
        //Description : Destructor
        //Parameters : None
        //Note : None
        //**************************
        ~CSprite();

        //**************************
        //Description : Init the sprite
        //Parameters : The animation for the sprite, and a pointer on the RenderWindow
        //Return Value : None
        //Note : None
        //**************************
        void InitSprite(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow);

        //**************************
        //Description : Return if the animation has been built or not
        //Parameters : None
        //Return Value : True if the animation is built, otherwise false
        //Note : None
        //**************************
        bool IsBuilt() const;

        //**************************
        //Description : Return if the animation is at the end or not
        //Parameters : None
        //Return Value : True if the animation is at the end, otherwise false
        //Note : The animation is at the end if there is no more loops to do and if the animation is at its last frame
        //      or, if the remaining loops are negetives (unlimited), if the animation is at its last frame
        //**************************
        bool EndAnimation() const;

        //**************************
        //Description : Draw the sprite on the RenderWindow
        //Parameters : The area of the sprite that we display
        //Return Value : None
        //Note : None
        //**************************
        void Draw(sf::IntRect * _AreaDisplayed = NULL);

        //**************************
        //Description : Draw the sprite on the RenderWindow
        //Parameters : the position in the RenderWindow where the sprite has to be drawn
        //              and The area of the sprite that we display
        //Return Value : None
        //Note : None
        //**************************
        void Draw(sf::IntRect * _Dest, sf::IntRect * _AreaDisplayed);

        //**************************
        //Description : Toggle the animation
        //Parameters : None
        //Return Value : None
        //Note : None
        //**************************
        void ToggleAnim();

        //**************************
        //Description : Start the animation
        //Parameters : None
        //Return Value : None
        //Note : None
        //**************************
        void StartAnim();

        //**************************
        //Description : Stop the animation
        //Parameters : None
        //Return Value : None
        //Note : None
        //**************************
        void StopAnim();

        //**************************
        //Description : Rewind the animation
        //Parameters : None
        //Return Value : None
        //Note : None
        //**************************
        void RewindAnim();

        //**************************
        //Description : Set m_bReverseAnim
        //Parameters : a boolean
        //Return Value : None
        //Note : None
        //**************************
        void ReverseAnim(bool _vReverse);

        /*
        * Setters and Getters
        */

        //**************************
        // X
        //**************************
        void XAdd(int _iValue);

        //**************************
        // Y
        //**************************
        void YAdd(int _iValue);

        //**************************
        // Speed
        //**************************
        void SetSpeed(float _fNewSpeed);

        float GetSpeed() const;

        //**************************
        // Width
        //**************************
        int GetWidth() const;

        //**************************
        // Height
        //**************************
        int GetHeight() const;

        //**************************
        // Displayed Frame
        //**************************
        void SetDisplayedFrame(int _iNewFrame);

        int GetDisplayedFrame() const;

        //**************************
        // Animation
        //**************************
        void SetAnimation(CSpriteAnimation * _Animation);

        CSpriteAnimation * GetAnimation() const;
};
#endif
