#include "Mouse.h"
#include <Windows.h>

Mouse::Mouse()
{

}

Mouse::Mouse(int _x, int _y,  HWND _hWnd)
{
	this->m_hWnd = _hWnd;
	SetCursorPos(_x, _y);
	
	this->m_lButtonIsDown = false;
	this->m_rButtonIsDown = false;
	this->m_lButtonIsPressed = false;
	this->m_rButtonIsPressed = false;
}

Mouse::~Mouse()
{

}

INT2 Mouse::getPos()const
{
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(this->m_hWnd, &pos);

	return INT2(pos.x, pos.y);
}

void Mouse::lButtonDown()
{
	if(!this->m_lButtonIsDown)
		this->m_lButtonIsPressed = true;
	this->m_lButtonIsDown = true;
}

void Mouse::rButtonDown()
{
	if(!this->m_rButtonIsDown)
		this->m_rButtonIsPressed = true;
	this->m_rButtonIsDown = true;
}

void Mouse::lButtonUp()
{
	this->m_lButtonIsDown = false;
}

void Mouse::rButtonUp()
{
	this->m_rButtonIsDown = false;
}

void Mouse::setMousePosition(int _x, int _y)
{
	SetCursorPos(_x, _y);
}

void Mouse::setMouseVisibility(bool _visible)const
{
	if(_visible)
		while(ShowCursor(TRUE) < 0);
	else
		while(ShowCursor(FALSE) >= 0);
}

void Mouse::update()
{
	RECT rc;
	GetWindowRect(this->m_hWnd, &rc);
	ClipCursor(&rc);

	this->m_lButtonIsPressed = false;
	this->m_rButtonIsPressed = false;
}