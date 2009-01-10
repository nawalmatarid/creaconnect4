#ifndef CSPRITEANIMATION_H
#define CSPRITEANIMATION_H

#include "../include/SSpriteFrame.h"

//**************************
//Load all image of an animation
//**************************
class CSpriteAnimation
{
    private:
        SSpriteFrame * m_Animation;

        bool m_bBuilt;	//True if the animation is loaded, otherwise false

        int m_iNumFrames;	//Number of frames in the animation

        int m_iNumLoops;	    //Number of loop to do (-1 to loop all the time)

        int m_iWidth;	//Width of the animation

        int m_iHeight;	//Height of the animation


    public:
        //**************************
        //Description : Constructor
        //Parameters : None
        //Note : None
        //**************************
        CSpriteAnimation();

        //**************************
        //Description : Constructor
        //Parameters : Path of the directory containing images of the animation
        //Note : None
        //**************************
        CSpriteAnimation(const char* _szDir);

        //**************************
        //Description : Copy Constructor
        //Parameters : A CSpriteAnimation
        //Note : None
        //**************************
        CSpriteAnimation(CSpriteAnimation & _SpriteAnimation);

        //**************************
        //Description : Destructor
        //Parameters : None
        //Note : None
        //**************************
        ~CSpriteAnimation();

        //**************************
        //Description : Load the animation
        //Parameters : Path of the directory containing images of the animation
        //Return Value : True if success, otherwise false
        //Note : None
        //**************************
        bool InitAnimation(const char* _szDir);

        //**************************
        //Description : Return if the animation has been built or not
        //Parameters : None
        //Return Value : True if the animation is built, otherwise false
        //Note : None
        //**************************
        bool IsBuilt() const;

        /*
        *   Setters and Getters
        */

        //**************************
        // Width
        //**************************
        int GetWidth() const;

        //**************************
        // Height
        //**************************
        int GetHeight() const;

        //**************************
        // Frame
        //**************************
        SSpriteFrame * GetFrame(int _iNumFrame) const;

        int GetNumFrame() const;

        //**************************
        // Loops
        //**************************
        int GetNumLoops() const;
};
#endif
