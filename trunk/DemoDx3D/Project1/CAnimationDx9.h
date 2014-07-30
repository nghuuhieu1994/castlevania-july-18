#ifndef __ANIMATION_H__
#define __ANIMATION_H__
#include "CSpriteDx9.h"
#include "RectangleDx9.h"

class CAnimationDx9
{
private:
	// Width of a Frame in sheet image
	int			m_FrameWidth;
	// Height of a Frame in sheer image
	int			m_FrameHeight;

		// Num Row frame in sheet image
		//int			m_Row;
	
	// Num Colum frame in sheet image
	int			m_Col;
	// Total frame in sheet
	int			m_TotalFrame;
	// Time to render next frame
	int			m_TimeNextFrame;
	// Rect using for render an frame
	RECT*		m_Rect;
	// index current frame u wanna render
	int			curFrame;
	// index start frame
	int			startFrame;

	// index end Frame
	int			endFrame;
public:
	CAnimationDx9();
	CAnimationDx9(int widthFrame, int heightFrame, int totalFrame, int colFrame, int rowFrame);
	void setStartFrame(int startframe);
	void setEndFrame(int endFrame);
	void UpdateAnimation(int timeAnimation);
	~CAnimationDx9();
};


#endif