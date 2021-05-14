#include "Player.h"
#include <chrono>
#include <thread>



Player::Player(): speed (1)
{
}


Player::~Player()
{
}

bool Player::openRecord(const std::string& fileName)
{
	std::ifstream fileObj;
	fileObj.open(fileName, std::ios::in | std::ios::binary);
	if (!fileObj.fail())
	{
		char x;
		while (!fileObj.eof())
		{
			fileObj.read((char*)&x, sizeof(char));
			buffer.push((char*)&x, sizeof(char));
		}

		fileObj.close();
		return true;
	}
	else return false;
}

void Player::playLine()
{
	Action action;
	char a;
	long x, y;
	long long time;

	buffer.read((char*)&a, sizeof(char));
	action = (Action)(int)a;

	if (action == Action::MOUSE_MOVE)
	{
		buffer.read((char*)&x, sizeof(long));
		buffer.read((char*)&y, sizeof(long));
		mouse.move(x, y);
	}
	else if (action == Action::MOUSEL_DOWN)
	{
		mouse.leftClickDown();
	}
	else if (action == Action::MOUSEL_UP)
	{
		mouse.leftClickUp();
	}
	else if (action == Action::DELAY)
	{
		buffer.read((char*)&time, sizeof(time));
		std::this_thread::sleep_for(std::chrono::nanoseconds(time) / speed);
		//Sleep((double)time / speed);
	}

}

bool Player::canPlay()
{
	if (!buffer.endOfBuffer())
		return true;
	else return false;
}


void Player::setSpeed(const double& s)
{
	speed = s;
}

void Player::stop()
{
	buffer.clear();
}


void Player::restRecord()
{
	buffer.markerReset();
}