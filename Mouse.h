#pragma once
#include <windows.h>

class Mouse
{
private:
	struct Position
	{
		long x;
		long y;
	}Position;
	bool haveChanged;
public:
	void updateMousePosition();
	bool isLeftClickDown() const;
	void move(const long& x, const long& y);
	void leftClickDown() const;
	void leftClickUp() const;
	void getPosition(long &x, long &y) const;
	Mouse();
	~Mouse();
};

