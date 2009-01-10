#ifndef SSPRITEFRAME_H
#define SSPRITEFRAME_H

#include <SFML/Graphics/Image.hpp>

//**************************
//Structure containing a frame of an animation
//**************************
struct SSpriteFrame
{
    int pause;	//Pause between two frames

    sf::Image * image;	//The frame
};
#endif
