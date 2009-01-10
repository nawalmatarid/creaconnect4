#include "../include/CSprite.h"
#include "../include/CSFMLManager.h"

#include <time.h>

//**************************
//Description : Constructor
//Parameters : None
//Note : None
//**************************
CSprite::CSprite()
    : Sprite(),
    m_fSpeed(1.0f)
{
    m_SpriteAnimation = NULL;
    m_bAnimating = false;
}

//**************************
//Description : Constructor
//Parameters : The animation for the sprite, and a pointer on the RenderWindow
//Note : None
//**************************
CSprite::CSprite(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow)
    : Sprite(),
    m_fSpeed(1.0f)
{
    m_SpriteAnimation = NULL;
    m_bAnimating = false;
    InitSprite(_Animation, _RenderWindow);
}

//**************************
//Description : Copy Constructor
//Parameters : A CSprite
//Note : None
//**************************
CSprite::CSprite(CSprite & _Sprite)
    : Sprite(),
    m_iDisplayedFrame(_Sprite.m_iDisplayedFrame),
    m_iRemainingLoops(_Sprite.m_iRemainingLoops),
    m_bAnimating(_Sprite.m_bAnimating),
    m_bReverseAnim(_Sprite.m_bReverseAnim),
    m_lLastUpdate(_Sprite.m_lLastUpdate),
    m_fSpeed(_Sprite.m_fSpeed)
{
    SetPosition(_Sprite.GetPosition());

    m_RenderWindow = _Sprite.m_RenderWindow;

    m_SpriteAnimation = _Sprite.m_SpriteAnimation;
}

//**************************
//Description : Destructor
//Parameters : None
//Note : None
//**************************
CSprite::~CSprite()
{
}

//**************************
//Description : Init the sprite
//Parameters : The animation for the sprite, and a pointer on the RenderWindow
//Return Value : None
//Note : None
//**************************
void CSprite::InitSprite(CSpriteAnimation * _Animation, sf::RenderWindow * _RenderWindow)
{
    if (m_SpriteAnimation == NULL)
    {
        m_SpriteAnimation = _Animation;

        //check if the animation is built (it has to be, but we check in case)
        if( m_SpriteAnimation->IsBuilt() )
        {
            m_lLastUpdate = 0;
            m_bReverseAnim = false;
            m_bDrawn = false;

            m_iDisplayedFrame = 0;

            SetImage(*m_SpriteAnimation->GetFrame(m_iDisplayedFrame)->image);

            //if there are more than one frame, we fave to animate the sprite
            if(m_SpriteAnimation->GetNumFrame() > 1)
                m_bAnimating = true;

            m_iRemainingLoops = m_SpriteAnimation->GetNumLoops();
        }

        m_RenderWindow = _RenderWindow;
    }
}

//**************************
//Description : Draw the sprite on the RenderWindow
//Parameters : The area of the sprite that we display
//Return Value : None
//Note : None
//**************************
void CSprite::Draw(sf::IntRect * _AreaDisplayed)
{
    //we draw
    Draw(NULL, _AreaDisplayed);
}

//**************************
//Description : Draw the sprite on the RenderWindow
//Parameters : the position in the RenderWindow where the sprite has to be drawn
//              and The area of the sprite that we display
//Return Value : None
//Note : None
//**************************
void CSprite::Draw(sf::IntRect * _Dest, sf::IntRect * _AreaDisplayed)
{
    CSFMLManager * SFMLManager = CSFMLManager::GetSingleton();

    //if the animation is built
    if ( m_SpriteAnimation->IsBuilt() )
    {
        //if nothing has been drawn the last update is now
        if (!m_bDrawn)
        {
            m_lLastUpdate = SFMLManager->GetElapsedTime() * 1000;
            m_bDrawn = true;
        }

        //if the sprite is animated
        if(m_bAnimating)
        {
            //we check if enough time passed to update the frame
            if( (m_lLastUpdate + m_SpriteAnimation->GetFrame(m_iDisplayedFrame)->pause * m_fSpeed) < (SFMLManager->GetElapsedTime() * 1000) )
            {
                int iNbFrame = m_SpriteAnimation->GetNumFrame();

                if (m_bReverseAnim)
                {
                    //next frame
                    m_iDisplayedFrame--;

                    //if the animation is at the end, we made the displayed frame to 0
                    if(m_iDisplayedFrame < 0)
                    {
                        //less loops to do
                        if (m_iRemainingLoops > 0)
                            m_iRemainingLoops--;

                        //if no more loops to do (loops == 0 ), we don't animate animore
                        if (m_iRemainingLoops == 0)
                        {
                            m_iDisplayedFrame++;
                            m_bAnimating = false;
                        }
                        //else we rewind the animation
                        else
                            m_iDisplayedFrame = iNbFrame-1;
                    }
                }
                else
                {
                    //next frame
                    m_iDisplayedFrame++;

                    //if the animation is at the end, we made the displayed frame to 0
                    if( m_iDisplayedFrame > iNbFrame-1)
                    {
                        //less loops to do
                        if (m_iRemainingLoops > 0)
                            m_iRemainingLoops--;
                        //if no more loops to do (loops == 0 ), we don't animate animore
                        if (m_iRemainingLoops == 0)
                        {
                            m_iDisplayedFrame--;
                            m_bAnimating = false;
                        }
                        //else we rewind the animation
                        else
                            m_iDisplayedFrame = 0;
                    }
                }

                //we change the image of the sprite
                SetImage(*m_SpriteAnimation->GetFrame(m_iDisplayedFrame)->image);

                //we take the time
                m_lLastUpdate = SFMLManager->GetElapsedTime() * 1000;
            }
        }

        if ( _Dest != NULL )
            SetPosition(_Dest->Left, _Dest->Top);

        if ( _AreaDisplayed != NULL )
            SetSubRect(*_AreaDisplayed);

        m_RenderWindow->Draw(*this);

        if ( _AreaDisplayed != NULL )
            SetSubRect( sf::IntRect(0, 0, GetWidth(), GetHeight() ) );
    }
}

//**************************
//Description : Return if the animation has been built or not
//Parameters : None
//Return Value : True if the animation is built, otherwise false
//Note : None
//**************************
bool CSprite::IsBuilt() const
{
    return m_SpriteAnimation->IsBuilt();
}

//**************************
//Description : Return if the animation is at the end or not
//Parameters : None
//Return Value : True if the animation is at the end, otherwise false
//Note : The animation is at the end if there is no more loops to do and if the animation is at its last frame
//      or, if the remaining loops are negetives (unlimited), if the animation is at its last frame
//**************************
bool CSprite::EndAnimation() const
{
    if ( m_iRemainingLoops < 0 )
    {
        if ( m_bReverseAnim )
            return ( m_iDisplayedFrame == 0 );
        else
            return ( m_iDisplayedFrame == ( m_SpriteAnimation->GetNumFrame() - 1 ) );
    }
    else
    {
        if ( m_bReverseAnim )
            return ( !m_bAnimating && m_iDisplayedFrame == 0 );
        else
            return ( !m_bAnimating && m_iDisplayedFrame == ( m_SpriteAnimation->GetNumFrame() - 1 ) );
    }
}

//**************************
//Description : Toggle the animation
//Parameters : None
//Return Value : None
//Note : None
//**************************
void CSprite::ToggleAnim()
{
    m_bAnimating = !m_bAnimating;
}

//**************************
//Description : Start the animation
//Parameters : None
//Return Value : None
//Note : None
//**************************
void CSprite::StartAnim()
{
    m_bAnimating = true;
}

//**************************
//Description : Stop the animation
//Parameters : None
//Return Value : None
//Note : None
//**************************
void CSprite::StopAnim()
{
    m_bAnimating = false;
}

//**************************
//Description : Rewind the animation
//Parameters : None
//Return Value : None
//Note : None
//**************************
void CSprite::RewindAnim()
{
    m_bDrawn = false;
    m_iRemainingLoops = m_SpriteAnimation->GetNumLoops();
    if(m_SpriteAnimation->GetNumFrame() > 1)
        m_bAnimating = true;

    if (m_bReverseAnim)
        m_iDisplayedFrame = m_SpriteAnimation->GetNumFrame() - 1;
    else
        m_iDisplayedFrame = 0;

    SetImage(*m_SpriteAnimation->GetFrame(m_iDisplayedFrame)->image);
}

//**************************
//Description : Set m_bReverseAnim
//Parameters : a boolean
//Return Value : None
//Note : None
//**************************
void CSprite::ReverseAnim(bool _vReverse)
{
    m_bReverseAnim = _vReverse;
}

/*
* Setters and Getters
*/

//**************************
// X
//**************************
void CSprite::XAdd(int _iValue)
{
    SetX(GetPosition().x + _iValue);
}

//**************************
// Y
//**************************
void CSprite::YAdd(int _iValue)
{
    SetY(GetPosition().y + _iValue);
}

//**************************
// Speed
//**************************
void CSprite::SetSpeed(float _fNewSpeed)
{
    m_fSpeed = _fNewSpeed;
}

float CSprite::GetSpeed() const
{
    return m_fSpeed;
}

//**************************
// Width
//**************************
int CSprite::GetWidth() const
{
    return m_SpriteAnimation->GetWidth();
}

//**************************
// Height
//**************************
int CSprite::GetHeight() const
{
    return m_SpriteAnimation->GetHeight();
}

//**************************
// Displayed Frame
//**************************
void CSprite::SetDisplayedFrame(int _iNewFrame)
{
    if ( _iNewFrame >= 0 && _iNewFrame < m_SpriteAnimation->GetNumFrame() )
        m_iDisplayedFrame = _iNewFrame;

    SetImage(*m_SpriteAnimation->GetFrame(m_iDisplayedFrame)->image);
}

int CSprite::GetDisplayedFrame() const
{
    return m_iDisplayedFrame;
}

//**************************
// Animation
//**************************
void CSprite::SetAnimation(CSpriteAnimation * _Animation)
{
    m_SpriteAnimation = _Animation;
}

CSpriteAnimation * CSprite::GetAnimation() const
{
    return m_SpriteAnimation;
}
