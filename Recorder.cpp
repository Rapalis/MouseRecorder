#include "Recorder.h"

Recorder::Recorder()
{
}


Recorder::~Recorder()
{
}

bool Recorder::saveData(const std::string  &fileName)
{
	std::ofstream fileObj;
	fileObj.open(fileName, std::ios::out | std::ios::binary);
	if (!fileObj.fail())
	{
		const char* data = buffer.getBuffer();
		fileObj.write(data, buffer.getSize());
		
		buffer.clear();
		fileObj.close();
		return true;
	}
	else return false;

}


void Recorder::recordLine()
{
	char temp;
	bool changed = false;
	long x = 0, y = 0;
	bool state = mouse.isLeftClickDown();
	mouse.updateMousePosition();
	mouse.getPosition(x, y);

	if (x != lastX || y != lastY)
	{
		temp = (char)Action::MOUSE_MOVE;
		buffer.push((char*)&temp, sizeof(char));
		buffer.push((char*)&x, sizeof(long));
		buffer.push((char*)&y, sizeof(long));
		changed = true;
	}
	if (lastState != state)
	{
		if (state == true)
		{
			temp = (char)Action::MOUSEL_DOWN;
		}
		else
		{
			temp = (char)Action::MOUSEL_UP;
		}
		buffer.push((char*)&temp, sizeof(char));
		changed = true;
	}
	if (changed)
	{
		temp = (int)Action::DELAY;

		if (clock.isTimerCounting())
		{
			long long rez = clock.stop();

			buffer.push((char*)&temp, sizeof(temp));
			buffer.push((char*)&rez, sizeof(rez));
		}

		clock.start();
		changed = false;
	}
	lastState = state;
	lastX = x;
	lastY = y;
}

void Recorder::stop()
{
	lastX = 0;
	lastY = 0;
	lastState = false;
	//begin = 0;
	//end = 0;
}

bool Recorder::continueRec(const std::string  &fileName)
{
	long x, y;
	char a;
	std::ofstream fileObj;
	std::ifstream laikinas(fileName, std::ios::in | std::ios::binary);
	if (!laikinas.fail())
	{
		while (laikinas.read((char*)&a, sizeof(char)))
			if ((Action)a == Action::MOUSE_MOVE)
			{
				laikinas.read((char*)&x, sizeof(long));
				laikinas.read((char*)&y, sizeof(long));
			}

			mouse.move(x, y);		
	}
	else return false;
	laikinas.close();


	fileObj.open(fileName, std::fstream::app | std::ios::binary);
	if (!fileObj.fail())
	{
		clock.start();
		//begin = clock();
		return true;
	}
	else return false;
}
