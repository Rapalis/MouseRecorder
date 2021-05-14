#include "Mouse.h"
#include <iostream>


Mouse::Mouse()
{
}


Mouse::~Mouse()
{
}

void Mouse::getPosition(long &x, long &y) const
{
	x = Position.x;
	y = Position.y;
}

void Mouse::updateMousePosition()
{
	POINT pos;
	GetCursorPos(&pos);
	Position.x = pos.x;
	Position.y = pos.y;
}

void Mouse::move(const long& x, const long& y)
{
	SetCursorPos(x, y);
	Position.x = x;
	Position.y = y;
}

bool Mouse::isLeftClickDown() const
{
	short result = GetAsyncKeyState(VK_LBUTTON);
	if(result & 1<<16)// && result & 1)
		return true;
	else return false;
}

void Mouse::leftClickUp() const
{
	mouse_event(MOUSEEVENTF_LEFTUP, Position.x, Position.y, 0, 0);
}


void Mouse::leftClickDown() const
{
	mouse_event(MOUSEEVENTF_LEFTDOWN, Position.x, Position.y, 0, 0);
}
