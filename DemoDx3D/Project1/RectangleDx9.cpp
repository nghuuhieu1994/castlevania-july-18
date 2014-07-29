#include "RectangleDx9.h"

RectangleDx9::RectangleDx9()
{
	this->m_Top = 0;
	this->m_Left = 0;
	this->m_Bot = 0;
	this->m_Right = 0;
	
	this->m_Rect.bottom = this->m_Bot;
	this->m_Rect.top = this->m_Top;
	this->m_Rect.left = this->m_Left;
	this->m_Rect.right = this->m_Right;
}

RectangleDx9::RectangleDx9(int top, int left, int bot, int right)
{
	this->m_Top			= top;
	this->m_Left		= left;
	this->m_Bot			= bot;
	this->m_Right		= right;
	
	this->m_Rect.bottom			= this->m_Bot;
	this->m_Rect.top			= this->m_Top;
	this->m_Rect.left			= this->m_Left;
	this->m_Rect.right			= this->m_Right;
}
RectangleDx9::RectangleDx9(const RECT &rect)
{
	RectangleDx9(rect.top, rect.left, rect.bottom, rect.right);
}
RectangleDx9::RectangleDx9(const RectangleDx9 &rectDx9)
{
	RectangleDx9(rectDx9.m_Top, rectDx9.m_Left, rectDx9.m_Bot, rectDx9.m_Right); 
}
RECT RectangleDx9::getRECT()
{
	return m_Rect;
}
RectangleDx9::~RectangleDx9()
{

}