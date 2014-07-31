#include "CAnimationDx9.h"

CAnimationDx9::CAnimationDx9()
{
	this->curFrame				= 0;
	this->endFrame				= 0;
	this->m_Col					= 0;
	this->m_FrameHeight			= 0;
	this->m_FrameWidth			= 0;
	this->m_Rect				= NULL;
	this->m_TimeNextFrame		= 0;
	this->m_TotalFrame			= 0;
	this->startFrame			= 0;
	this->m_LocalTime			= 0;
}
CAnimationDx9::CAnimationDx9(int widthFrame, int heightFrame, int totalFrame, int colFrame, int rowFrame)
{
	this->curFrame				= 0;
	this->startFrame			= 0;
	this->endFrame				= 0;
	this->m_Col					= colFrame;
	this->m_Row					= rowFrame;
	this->m_FrameHeight			= heightFrame;
	this->m_FrameWidth			= widthFrame;

	this->m_Rect				= new RECT();

	this->m_Rect->top			= 0;
	this->m_Rect->left			= 0;
	this->m_Rect->bottom		= m_FrameHeight + m_Rect->top;
	this->m_Rect->right			= m_FrameWidth + m_Rect->left;
	
	this->m_TimeNextFrame		= 100;
	this->m_TotalFrame			= 1;
	this->m_LocalTime			= 0;
}
CAnimationDx9::CAnimationDx9(const CAnimationDx9* otherAnimation)
{
	this->curFrame			= otherAnimation->curFrame;
	this->endFrame			= otherAnimation->endFrame;
	this->m_Col				= otherAnimation->m_Col;
	this->m_Row				= otherAnimation->m_Row;
	this->m_FrameHeight		= otherAnimation->m_FrameHeight;
	this->m_FrameWidth		= otherAnimation->m_FrameWidth;
	this->m_LocalTime		= otherAnimation->m_LocalTime;
	this->m_Rect			= new RECT(*otherAnimation->m_Rect);
	this->m_TimeNextFrame	= otherAnimation->m_TimeNextFrame;
	this->m_TotalFrame		= otherAnimation->m_TotalFrame;
	this->startFrame		= otherAnimation->startFrame;
}
void CAnimationDx9::setStartFrame(int startframe)
{
	this->startFrame = startframe;
}
void CAnimationDx9::setEndFrame(int endframe)
{
	this->endFrame = endframe;
}
void CAnimationDx9::nextFrame()
{
	this->curFrame++;
	if(this->curFrame > this->endFrame)
		this->curFrame = this->startFrame;
}

RECT* CAnimationDx9::getRect()
{
	return this->m_Rect;
}

void CAnimationDx9::UpdateAnimation(CGameTimeDx9* gameTime, int timeAnimation)
{
	m_LocalTime += gameTime->getElapsedGameTime().getMilliseconds();
	if(m_LocalTime > m_TimeNextFrame)
	{
		this->nextFrame();
		m_LocalTime = 0;
	}
	m_Rect->top = (curFrame / m_Col) * m_FrameHeight;
	m_Rect->left = (curFrame % m_Col) * m_FrameWidth;
	this->m_Rect->bottom		= m_FrameHeight + m_Rect->top;
	this->m_Rect->right			= m_FrameWidth + m_Rect->left;
}