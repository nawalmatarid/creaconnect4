#include "../include/CSpriteAnimation.h"

#include <assert.h>
#include <string.h>

//**************************
//Description : Constructor
//Parameters : None
//Note : None
//**************************
CSpriteAnimation::CSpriteAnimation()
{
    m_iWidth = -1;
    m_iHeight = -1;
    m_Animation = NULL;
}

//**************************
//Description : Constructor
//Parameters : Path of the directory containing images of the animation
//Note : None
//**************************
CSpriteAnimation::CSpriteAnimation(const char* _szDir)
{
    m_iWidth = -1;
    m_iHeight = -1;

    InitAnimation(_szDir);
}

//**************************
//Description : Copy Constructor
//Parameters : A CSpriteAnimation
//Note : None
//**************************
CSpriteAnimation::CSpriteAnimation(CSpriteAnimation & _SpriteAnimation)
    : m_bBuilt(_SpriteAnimation.m_bBuilt),
    m_iNumFrames(_SpriteAnimation.m_iNumFrames),
    m_iNumLoops(_SpriteAnimation.m_iNumLoops),
    m_iWidth(_SpriteAnimation.m_iWidth),
    m_iHeight(_SpriteAnimation.m_iHeight)
{
    m_Animation = new SSpriteFrame[m_iNumFrames];

    for ( int i = 0; i < m_iNumFrames; i++ )
    {
        m_Animation[i].image = new sf::Image(*_SpriteAnimation.m_Animation[i].image);
        m_Animation[i].pause = _SpriteAnimation.m_Animation[i].pause;
    }
}

//**************************
//Description : Destructor
//Parameters : None
//Note : None
//**************************
CSpriteAnimation::~CSpriteAnimation()
{
    if ( m_Animation != NULL )
    {
        for (int i = 0; i < m_iNumFrames; i++)
        {
            //delete may be unnessecary because the Renderer destroy all video ressource at the end of the program
            //delete m_Animation[i].image;
            m_Animation[i].image = NULL;
        }

        delete[] m_Animation;
    }
}

//**************************
//Description : Load the animation
//Parameters : Path of the directory containing images of the animation
//Return Value : True if success, otherwise false
//Note : None
//**************************
bool CSpriteAnimation::InitAnimation(const char* _szDir)
{
  	char szBuffer[255];			//buffer of a line
  	char szFilename[255];		//name of the info file
  	char szName[255];			//name of the image file
  	int iPause = 0,             //pause before displaying another frame
        iRed = -1,				//red color for transparency
  		iGreen = -1,			//green color for transparency
  		iBlue = -1;				//blue color for transparency
  	FILE *fFile;				//pointer on the file

  	//opening of the info file
  	sprintf(szFilename, "%s/info", _szDir);

	fFile = fopen(szFilename, "r");
  	//test on the opening
  	assert ( fFile != NULL );

  	//get first line
  	fgets(szBuffer, 255, fFile);
  	//scan the number of frames
  	sscanf(szBuffer, "FILES: %d", &m_iNumFrames);
  	//get second line
  	fgets(szBuffer, 255, fFile);
  	//scan the number of loops
  	sscanf(szBuffer, "LOOPS: %d", &m_iNumLoops);
  	//create the array of frames
  	m_Animation = new SSpriteFrame[m_iNumFrames];

  	int iCount = 0;

  	//we loop for each frame info
  	while(!feof(fFile) && iCount < m_iNumFrames)
  	{
  		//get a line
  		fgets(szBuffer, 255, fFile);

  		//check wether it's useful or not (comment line, blank, or nothing)
  		if(szBuffer[0] != '#' && szBuffer[0] != '\r' && szBuffer[0] != '\0'
  					   && szBuffer[0] != '\n' && strlen(szBuffer) != 0)
  		{
  			//get info of the frame
  			sscanf(szBuffer, "%s %d %d %d %d", szName, &iRed, &iGreen, &iBlue, &iPause);
  			sprintf(szFilename, "%s/%s", _szDir, szName);

  			//load the surface
  			m_Animation[iCount].image = new sf::Image();
  			assert( m_Animation[iCount].image->LoadFromFile(szFilename) );

  			//check if there is transparency or not (if there isn't transparency iRed = iBlue = iGreen = -1)
  			if(iRed >= 0)
  				m_Animation[iCount].image->CreateMaskFromColor(sf::Color(iRed, iGreen, iBlue));

  			//we set the pause
  			m_Animation[iCount].pause = iPause;

  			//we set the width and the height of the animation if it is not done
  			if (m_iWidth < 0)
  				m_iWidth = m_Animation[iCount].image->GetWidth();

  			if (m_iHeight < 0)
  				m_iHeight = m_Animation[iCount].image->GetHeight();

  			//next frame
  			iCount++;
  		}
  	}

  	m_bBuilt = true;

  	//we close the file
  	fclose(fFile);

  	return true;

}

//**************************
//Description : Return if the animation has been built or not
//Parameters : None
//Return Value : True if the animation is built, otherwise false
//Note : None
//**************************
bool CSpriteAnimation::IsBuilt() const
{
  return m_bBuilt;

}

/*
*   Setters and Getters
*/

//**************************
// Width
//**************************
int CSpriteAnimation::GetWidth() const
{
  return m_iWidth;
}

//**************************
// Height
//**************************
int CSpriteAnimation::GetHeight() const
{
  return m_iHeight;
}

//**************************
// Frame
//**************************
SSpriteFrame * CSpriteAnimation::GetFrame(int _iNumFrame) const
{
  if ( m_Animation != NULL && _iNumFrame >= 0 && _iNumFrame < m_iNumFrames )
  	return (&m_Animation[_iNumFrame]);
  else
  	return NULL;
}


int CSpriteAnimation::GetNumFrame() const
{
  return m_iNumFrames;
}

//**************************
// Loops
//**************************
int CSpriteAnimation::GetNumLoops() const
{
  return m_iNumLoops;
}

