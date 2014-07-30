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
}
CAnimationDx9::CAnimationDx9(int widthFrame, int heightFrame, int totalFrame, int colFrame, int rowFrame)
{
	this->curFrame				= 0;
	this->startFrame			= 0;
	this->endFrame				= 0;
	this->m_Col					= colFrame;
	this->curFrame				= 0;
	this->m_FrameHeight			= heightFrame;
	this->m_FrameWidth			= widthFrame;

	this->m_Rect->top			= 0;
	this->m_Rect->left			= 0;
	this->m_Rect->bottom		= m_FrameHeight + m_Rect->top;
	this->m_Rect->right			= m_FrameWidth + m_Rect->left;
	
	this->m_TimeNextFrame		= 100;
	this->m_TotalFrame			= 1;
}
void CAnimationDx9::setStartFrame(int startframe)
{
	this->startFrame = startframe;
}
void CAnimationDx9::setEndFrame(int endframe)
{
	this->endFrame = endframe;
}
void CAnimationDx9::UpdateAnimation(int timeAnimation)
{
	this->curFrame++;
	if(this->curFrame > this->endFrame)
		this->curFrame = this->startFrame;

	m_Rect->top = (curFrame / m_Col) * m_FrameHeight;
	m_Rect->left = (curFrame % m_Col) * m_FrameWidth;
	this->m_Rect->bottom		= m_FrameHeight + m_Rect->top;
	this->m_Rect->right			= m_FrameWidth + m_Rect->left;
}